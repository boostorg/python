import scons_tools
import os

bp_numpy_env = scons_tools.MakeEnvironment()
bp_numpy_env.SetupPackages(["boost.python","numpy"])
bp_numpy_env.Append(CPPPATH = "#")

if ARGUMENTS.get("debug", 0):
    build_dir = "build.debug"
else:
    build_dir = "build"
Export("build_dir")

Export("bp_numpy_env")
lib = SConscript("libs/python/numpy/src/SConscript", 
                 variant_dir="%s/python/numpy/src" % build_dir, duplicate=False)
libpath = os.path.abspath("%s/python/numpy/src" % build_dir)
if os.environ.has_key("LD_LIBRARY_PATH"):
    bp_numpy_env["ENV"]["LD_LIBRARY_PATH"] = "%s:%s" % (libpath, os.environ["LD_LIBRARY_PATH"])
else:
    bp_numpy_env["ENV"]["LD_LIBRARY_PATH"] = libpath
bp_numpy_env.Append(LIBPATH=libpath)

SConscript("libs/python/numpy/test/SConscript", variant_dir="%s/python/numpy/test" % build_dir)
