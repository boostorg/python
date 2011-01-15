import SCons.Script as scons
import re
import distutils.sysconfig
import sys
import os

database = {}

_environment = None

scons.AddOption("--prefix", dest="install_prefix", type="string", nargs=1, action="store", metavar="DIR",
                help="installation prefix")
scons.AddOption("--home", dest="install_home", type="string", nargs=1, action="store", metavar="DIR",
                help="home directory to install under")
scons.AddOption("--install-lib", dest="install_lib", type="string", nargs=1, action="store", metavar="DIR",
                help="installation directory for libraries")
scons.AddOption("--install-headers", dest="install_headers", type="string", nargs=1, 
                action="store", metavar="DIR", help="installation directory for C++ header files")
scons.AddOption("--install-python", dest="install_python", type="string", nargs=1, 
                action="store", metavar="DIR", help="installation directory for Python modules")

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

    def require(self):        
        if not all(database[pkg].check() for pkg in self.dependencies):
            print "Missing dependencies for required package '%s'." % self.name
            scons.Exit(1)


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
        env = GetEnvironment().Clone()
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
        context = scons.Configure(env)
        if not context.CheckHeader(["Python.h"]):
            context.Finish()
            return False
        context.Finish()
        return True

PythonConfiguration()

class NumPyConfiguration(VariableConfiguration):

    name = "numpy"
    dependencies = ("python",)

    def _check(self):
        env = GetEnvironment().Clone()
        self._apply_dependencies(env)
        try:
            import numpy.distutils.misc_util
            self._variables = {"CPPPATH": numpy.distutils.misc_util.get_numpy_include_dirs()}
        except ImportError:
            print "numpy.distutils.misc_util not found"
            return False
        self._apply(env)
        context = scons.Configure(env)
        if not context.CheckHeader(["Python.h", "numpy/arrayobject.h"]):
            context.Finish()
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
        env = GetEnvironment().Clone()
        self._apply_dependencies(env)
        self._apply(env)
        context = scons.Configure(env)
        if self._headers:
            if not context.CheckHeader(self._headers, language="C++"):
                context.Finish()
                return False
        if self._libraries:
            if not context.CheckLib(self._libraries, language="C++"):
                context.Finish()
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
    path, filename = os.path.split(target[0].abspath)
    env["ENV"]["TESTPATH"] = path
    env["ENV"]["PYTHONPATH"] = ":".join([path] + env["ENV"]["PYTHONPATH"].split(":"))
    if not env.Execute('%s %s' % (sys.executable, source[0].abspath)):
        env.Execute(scons.Touch(target))
    env["ENV"]["PYTHONPATH"] = ":".join(env["ENV"]["PYTHONPATH"].split(":")[1:])

def BoostUnitTest(env, name, source):
    try:
        libs = env["LIBS"] + ["boost_unit_test_framework"]
    except KeyError:
        libs = "boost_unit_test_framework"
    bin = env.Program(name, source, LIBS=libs)
    run = env.Command(".%s.succeeded" % str(name), name, RunProgramUnitTest)
    env.Depends(run, bin)
    return run

def PythonUnitTest(env, script, dependencies):
    run = env.Command(".%s.succeeded" % str(script), script, RunPythonUnitTest)
    env.Depends(run, dependencies)
    return run

def SetupPackages(env, packages):
    for package in packages:
        database[package].apply(env)

def MakeAliases(targets):
    env = GetEnvironment()
    all_all = []
    build_all = []
    install_all = []
    test_all = []
    scons.Help("""
To specify additional directories to add to the include or library paths, specify them
with colon-separated lists on the command line.  For example:

scons CPPPATH="/home/me/include:/opt/include" LIBPATH="/home/me/lib"

Supported variables are CPPPATH, LIBPATH and RPATH.

Global targets:   'all'     (builds everything)
                  'build'   (builds headers, libraries, and python wrappers)
                  'install' (copies files to global bin, include and lib directories)
                  'test'    (runs unit tests; requires install)

These targets can be built for individual packages with the syntax
'[package]-[target]'.  Some packages support additional targets, given below.

Packages:

"""
               )
    for pkg_name in sorted(targets.keys()):
        pkg_targets = targets[pkg_name]
        extra_targets = tuple(k for k in pkg_targets.keys() if k not in
                              ("all","build","install","test"))
        if extra_targets:
            scons.Help("%-25s   %s\n" % (pkg_name, ", ".join("'%s'" % k for k in extra_targets)))
        else:
            scons.Help("%-25s   (none)\n" % pkg_name)
        pkg_all = pkg_targets.values()
        pkg_build = [pkg_targets[k] for k in ("headers", "lib", "python") if k in pkg_targets]
        env.Alias(pkg_name, pkg_all)
        env.Alias("%s-all" % pkg_name, pkg_all)
        env.Alias("%s-build" % pkg_name, pkg_build)
        for target_name in pkg_targets:
            env.Alias("%s-%s" % (pkg_name, target_name), pkg_targets[target_name])
        all_all.extend(pkg_all)
        build_all.extend(pkg_build)
        install_all.extend(pkg_targets.get("install", pkg_build))
        test_all.extend(pkg_targets.get("test", pkg_targets.get("install", pkg_build)))
    env.Alias("all", all_all)
    env.Alias("build", build_all)
    env.Alias("install", install_all)
    env.Alias("test", test_all)
    env.Default("build")


def MakeEnvironment(default_prefix="/usr/local", prefix_is_home=False):
    global _environment
    _environment = scons.Environment(tools = ["default", "doxygen"])
    if scons.ARGUMENTS.has_key('LIBPATH'):
        _environment.Append(LIBPATH=[os.path.abspath(s) for s in scons.ARGUMENTS['LIBPATH'].split(":")])
    if scons.ARGUMENTS.has_key('RPATH'):
        _environment.Append(RPATH=[os.path.abspath(s) for s in scons.ARGUMENTS['RPATH'].split(":")])
    if scons.ARGUMENTS.has_key('CPPPATH'):
        _environment.Append(CPPPATH=[os.path.abspath(s) for s in scons.ARGUMENTS['CPPPATH'].split(":")])
    prefix = scons.GetOption("install_prefix")
    if prefix is None:
        prefix = scons.GetOption("install_home")
        if prefix is None:
            prefix = default_prefix
        else:
            preefix_is_home = True
    install_lib = scons.GetOption("install_lib")
    if install_lib is None:
        install_lib = os.path.join(prefix, "lib")
    install_headers = scons.GetOption("install_headers")
    if install_headers is None:
        install_headers = os.path.join(prefix, "include")
    install_python = scons.GetOption("install_python")
    if install_python is None:
        if prefix_is_home:
            install_python = os.path.join(install_lib, "python")
        else:
            python_lib = distutils.sysconfig.get_python_lib()
            if python_lib.startswith(distutils.sysconfig.PREFIX):
                install_python = os.path.join(prefix, python_lib[len(distutils.sysconfig.PREFIX)+1:])
            else:
                print "Cannot determine default Python install directory."
                print "Please specify --install-python on the command line."
                scons.Exit(1)
    _environment["INSTALL_LIB"] = install_lib
    _environment["INSTALL_HEADERS"] = install_headers
    _environment["INSTALL_PYTHON"] = install_python
    _environment.AddMethod(RecursiveInstall, "RecursiveInstall")
    _environment.AddMethod(SetupPackages, "SetupPackages")
    _environment.AddMethod(BoostUnitTest, "BoostUnitTest")
    _environment.AddMethod(PythonUnitTest, "PythonUnitTest")
    for var in ("PATH", "LD_LIBRARY_PATH", "PYTHONPATH", "PKG_CONFIG_PATH"):
        if os.environ.has_key(var):
            _environment["ENV"][var] = os.environ[var]
        else:
            _environment["ENV"][var] = ""
    debug = scons.ARGUMENTS.get('debug', 0)
    if int(debug):
        _environment.Replace(CCFLAGS=["-Wall","-g","-O0"])
    else:
        _environment.Replace(CCFLAGS=["-Wall","-O2"])
        _environment.Append(CPPDEFINES=["NDEBUG"])
    return _environment

def GetEnvironment():
    if _environment is None:
        raise LogicErrorException("scons_tools error: root environment not initialized")
    return _environment

def GetBuildDir():
    if scons.ARGUMENTS.get("debug", 0):
        return "build.debug"
    else:
        return "build"

