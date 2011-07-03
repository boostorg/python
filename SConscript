import scons_tools
import os

targets = {"boost.numpy":{}}

scons_tools.LocalConfiguration(
    name="boost.numpy",
    libraries=["boost_numpy"],
    dependencies=("boost.python", "numpy")
    )
boost_numpy_env = scons_tools.GetEnvironment().Clone()
boost_numpy_env.Append(CPPPATH=[os.path.abspath(os.curdir)])
libpath = os.path.abspath("%s/numpy/src" % scons_tools.GetBuildDir())
if os.environ.has_key("LD_LIBRARY_PATH"):
    boost_numpy_env["ENV"]["LD_LIBRARY_PATH"] = "%s:%s" % (libpath, os.environ["LD_LIBRARY_PATH"])
else:
    boost_numpy_env["ENV"]["LD_LIBRARY_PATH"] = libpath
boost_numpy_env.Append(LIBPATH=[libpath])
boost_numpy_env.SetupPackages(["boost.python", "numpy"])
Export("boost_numpy_env")

targets["boost.numpy"]["lib"] = SConscript("libs/numpy/src/SConscript")
targets["boost.numpy"]["install"] = (
    boost_numpy_env.RecursiveInstall(
        os.path.join(boost_numpy_env["INSTALL_HEADERS"], "boost"), 
        "boost", 
        regex="(.*\.hpp)")
    + boost_numpy_env.Install(boost_numpy_env["INSTALL_LIB"], targets["boost.numpy"]["lib"])
    )
targets["boost.numpy"]["test"] = SConscript("libs/numpy/test/SConscript")


Return("targets")
