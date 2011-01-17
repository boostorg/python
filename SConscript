import scons_tools
import os

targets = {"boost.python.numpy":{}}

scons_tools.LocalConfiguration(
    name="boost.python.numpy",
    libraries=["boost_python_numpy"],
    dependencies=("boost.python", "numpy")
    )
bp_numpy_env = scons_tools.GetEnvironment().Clone()
bp_numpy_env.Append(CPPPATH=[os.path.abspath(os.curdir)])
libpath = os.path.abspath("%s/python/numpy/src" % scons_tools.GetBuildDir())
if os.environ.has_key("LD_LIBRARY_PATH"):
    bp_numpy_env["ENV"]["LD_LIBRARY_PATH"] = "%s:%s" % (libpath, os.environ["LD_LIBRARY_PATH"])
else:
    bp_numpy_env["ENV"]["LD_LIBRARY_PATH"] = libpath
bp_numpy_env.Append(LIBPATH=[libpath])
bp_numpy_env.SetupPackages(["boost.python", "numpy"])
Export("bp_numpy_env")

targets["boost.python.numpy"]["lib"] = SConscript("libs/python/numpy/src/SConscript")
targets["boost.python.numpy"]["install"] = (
    bp_numpy_env.RecursiveInstall(
        os.path.join(bp_numpy_env["INSTALL_HEADERS"], "boost"), 
        "boost", 
        regex="(.*\.hpp)")
    + bp_numpy_env.Install(bp_numpy_env["INSTALL_LIB"], targets["boost.python.numpy"]["lib"])
    )
targets["boost.python.numpy"]["test"] = SConscript("libs/python/numpy/test/SConscript")


Return("targets")
