import scons_tools
import os

bp_numpy_env = scons_tools.MakeEnvironment()
bp_numpy_env.SetupPackages(["boost.python","numpy"])
bp_numpy_env.Append(CPPPATH = "#")

Export("bp_numpy_env")
lib = SConscript("libs/python/numpy/src/SConscript")
libpath = os.path.abspath("libs/python/numpy/src")
if os.environ.has_key("LD_LIBRARY_PATH"):
    bp_numpy_env["ENV"]["LD_LIBRARY_PATH"] = "%s:%s" % (libpath, os.environ["LD_LIBRARY_PATH"])
else:
    bp_numpy_env["ENV"]["LD_LIBRARY_PATH"] = libpath
bp_numpy_env.Append(LIBPATH="#libs/python/numpy/src")

SConscript("libs/python/numpy/test/SConscript")
