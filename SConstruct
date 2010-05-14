import distutils.sysconfig
import numpy.distutils.misc_util
import re
import os

def ApplyFlags(env, flags):
    flags = env.ParseFlags(flags)
    flags["CCFLAGS"] = [opt for opt in flags["CCFLAGS"] if not opt.startswith("-O")]
    flags["CFLAGS"] = [opt for opt in flags["CFLAGS"] if not opt.startswith("-O")]
    debug = ARGUMENTS.get('debug', 0)
    if int(debug):
        try:
            flags["CPPDEFINES"].remove("NDEBUG")
        except: pass
    env.MergeFlags(flags)

def ConfigurePython(env):
    cflags = " ".join(v for v in distutils.sysconfig.get_config_vars("BASECFLAGS","OPT")
                      if v is not None).split()
    libs = " ".join(v for v in distutils.sysconfig.get_config_vars("BLDLIBRARY","LIBS")
                    if v is not None).split()
    try: # not valid for C++
        cflags.remove("-Wstrict-prototypes")
    except ValueError: pass
    cflags = [f for f in cflags if not f.startswith("-O")]
    try:
        libs.remove("-L.")
    except ValueError: pass
    cflags.append("-I%s" % distutils.sysconfig.get_python_inc())
    ApplyFlags(env, cflags + libs)

def ConfigureNumpy(env):
    folders = numpy.distutils.misc_util.get_numpy_include_dirs()
    env.Append(CPPPATH=folders)

env = Environment()
ConfigurePython(env)
ConfigureNumpy(env)
env.Append(LIBS = "boost_python")
env.Append(CPPPATH = "#")

Export("env")
lib = SConscript("libs/python/numpy/src/SConscript")
libpath = os.path.abspath("libs/python/numpy/src")
if os.environ.has_key("LD_LIBRARY_PATH"):
    env["ENV"]["LD_LIBRARY_PATH"] = "%s:%s" % (libpath, os.environ["LD_LIBRARY_PATH"])
else:
    env["ENV"]["LD_LIBRARY_PATH"] = libpath
env.Append(LIBPATH=libpath)
Export("lib")
SConscript("libs/python/numpy/test/SConscript")
