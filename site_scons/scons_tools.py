import SCons.Script as scons
import re
import os

database = {}

def ApplyFlags(env, flags):
    flags = env.ParseFlags(flags)
    flags["CCFLAGS"] = [opt for opt in flags["CCFLAGS"] if not opt.startswith("-O")]
    flags["CFLAGS"] = [opt for opt in flags["CFLAGS"] if not opt.startswith("-O")]
    debug = scons.ARGUMENTS.get('debug', 0)
    if int(debug):
        try:
            flags["CPPDEFINES"].remove("NDEBUG")
        except: pass
    env.MergeFlags(flags)

class Configuration(object):

    def __new__(cls, name=None, dependencies=None):
        if name is None:
            name = cls.name
        if dependencies is None:
            dependencies = cls.dependencies
        if database.has_key(name):
            return database[name]
        else:
            self = object.__new__(cls)
            self._checked = False
            if not hasattr(cls, "dependencies"):
                self.dependencies = dependencies
            if not hasattr(cls, "name"):
                self.name = name
            database[name] = self
            return self

    def check(self):
        if scons.GetOption("help") or scons.GetOption("clean"):
            return True
        if not self._checked:
            self._available = self._check_dependencies() and self._check()
            self._checked = True
        return self._available

    def _check(self):
        return True

    def _check_dependencies(self):
        for dependency in self.dependencies:
            if not database[dependency].check():
                return False
        return True

    def apply(self, environment):
        if scons.GetOption("help") or scons.GetOption("clean"):
            return
        if self.check():
            self._apply_dependencies(environment)
            self._apply(environment)

    def _apply(self, environment):
        pass

    def _apply_dependencies(self, environment):
        for dependency in self.dependencies:
            database[dependency].apply(environment)

class FlagConfiguration(Configuration):

    def _apply(self, environment):
        ApplyFlags(environment, self._flags)

class VariableConfiguration(Configuration):

    def _apply(self, environment):
        environment.Append(**self._variables)

class PythonConfiguration(FlagConfiguration):

    name = "python"
    dependencies = ()

    def _check(self):
        env = MakeEnvironment()
        context = scons.Configure(env)
        try:
            from distutils.sysconfig import get_config_vars, get_python_inc
        except ImportError:
            return False
        self._flags = " ".join(v for v in get_config_vars("BASECFLAGS", "OPT", "BLDLIBRARY", "LIBS")
                               if v is not None).split()
        try: # not valid for C++
            self._flags.remove("-Wstrict-prototypes")
        except ValueError: pass
        try:
            self._flags.remove("-L.")
        except ValueError: pass
        self._flags = [f for f in self._flags if not f.startswith("-O")]
        self._flags.append("-I%s" % get_python_inc())
        self._apply(env)
        if not context.CheckHeader(["Python.h"]):
            return False
        context.Finish()
        return True

PythonConfiguration()

class NumPyConfiguration(VariableConfiguration):

    name = "numpy"
    dependencies = ("python",)

    def _check(self):
        env = MakeEnvironment()
        context = scons.Configure(env)
        self._apply_dependencies(context.env)
        try:
            import numpy.distutils.misc_util
            self._variables = {"CPPPATH": numpy.distutils.misc_util.get_numpy_include_dirs()}
        except ImportError:
            context.Result(False)
            return False
        self._apply(context.env)
        if not context.CheckHeader(["Python.h", "numpy/arrayobject.h"]):
            return False
        context.Finish()
        return True

NumPyConfiguration()

class LibraryConfiguration(VariableConfiguration):

    def __new__(cls, name, headers=None, libraries=None, dependencies=()):
        self = VariableConfiguration.__new__(cls, name, dependencies)
        self._headers = headers
        self._libraries = libraries
        self._variables = {}
        return self

    def _check(self):
        env = MakeEnvironment()
        context = scons.Configure(env)
        self._apply_dependencies(context.env)
        self._apply(context.env)
        if self._headers:
            if not context.CheckHeader(self._headers, language="C++"):
                return False
        if self._libraries:
            if not context.CheckLib(self._libraries, language="C++"):
                return False
            self._variables = {"LIBS": self._libraries}
        context.Finish()
        return True

LibraryConfiguration(name="boost.python",
                     headers=["boost/python.hpp"], 
                     libraries=["boost_python"],
                     dependencies=("python",)
                     )

class LocalConfiguration(VariableConfiguration):

    def __new__(cls, name, libraries=None, dependencies=()):
        self = VariableConfiguration.__new__(cls, name, dependencies)
        self._libraries = libraries
        self._variables = {}
        return self

    def _check(self):
        if self._libraries:
            self._variables["LIBS"] = self._libraries
        return True

def RecursiveInstall(env, target, source, regex):
    regex = re.compile(regex)
    source = scons.Dir(source)
    target = scons.Dir(target)
    result = []
    for dirpath, dirnames, filenames in os.walk(source.abspath):
        try:
            dirnames.remove(".svn")
        except ValueError:
            pass
        relpath = dirpath[len(source.abspath)+1:]
        for filename in filenames:
            m = regex.match(filename)
            if m:
                result.extend(env.InstallAs(os.path.join(target.abspath, relpath, m.group(1)), 
                                            os.path.join(dirpath, m.group(1))))
    return result

def RunProgramUnitTest(target, source, env):
    path, filename = os.path.split(source[0].abspath)
    if not env.Execute("cd %s; ./%s" % (path, filename)):
        env.Execute(scons.Touch(target))

def RunPythonUnitTest(target, source, env):
    path, filename = os.path.split(source[0].abspath)
    if not env.Execute("cd %s; python %s" % (path, filename)):
        env.Execute(scons.Touch(target))

def BoostUnitTest(env, name, source):
    try:
        libs = env["LIBS"] + ["boost_unit_test_framework"]
    except KeyError:
        libs = "boost_unit_test_framework"
    bin = env.Program(name, source, LIBS=libs)
    run = env.Command(".%s.succeeded" % name, name, RunProgramUnitTest)
    env.Depends(run, bin)
    return run

def PythonUnitTest(env, script, dependencies):
    run = env.Command(".%s.succeeded" % script, script, RunPythonUnitTest)
    env.Depends(run, dependencies)
    return run

def SetupPackages(env, packages):
    for package in packages:
        database[package].apply(env)

def MakeEnvironment():
    env = scons.Environment()
    env.AddMethod(RecursiveInstall, "RecursiveInstall")
    env.AddMethod(SetupPackages, "SetupPackages")
    env.AddMethod(BoostUnitTest, "BoostUnitTest")
    env.AddMethod(PythonUnitTest, "PythonUnitTest")
    for var in ("PATH", "LD_LIBRARY_PATH", "PYTHONPATH", "PKG_CONFIG_PATH"):
        if os.environ.has_key(var):
            env["ENV"][var] = os.environ[var]
    debug = scons.ARGUMENTS.get('debug', 0)
    if int(debug):
        env.Replace(CCFLAGS=["-Wall","-g","-O0"])
    else:
        env.Replace(CCFLAGS=["-Wall","-O2"])
        env.Append(CPPDEFINES="NDEBUG")
    return env
