# -*- python -*-

# Copyright Jim Bosch 2010-2012.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

# Big thanks to Mike Jarvis for help with the configuration prescriptions below.
# Integration of SConsChecks for platform independent building
# by Christoph Lassner.

from __future__ import print_function
import os
import sys
import subprocess
import sysconfig
from SCons.SConf import CheckContext
from SConsChecks import AddLibOptions, GetLibChecks

_libs = ['boost.python',
         'python',
         'numpy']
_checks = GetLibChecks(_libs)

# Setup command-line options
def setupOptions():
    AddOption("--prefix", dest="prefix", type="string", nargs=1, action="store",
              metavar="DIR", default="/usr/local", help="installation prefix")
    AddOption("--install-headers", dest="install_headers", type="string", nargs=1, action="store",
              metavar="DIR", help="location to install header files (overrides --prefix for headers)")
    AddOption("--install-lib", dest="install_lib", type="string", nargs=1, action="store",
              metavar="DIR", help="location to install libraries (overrides --prefix for libraries)")
    AddOption("--with-boost", dest="boost_prefix", type="string", nargs=1, action="store",
              metavar="DIR", default=os.environ.get("BOOST_DIR"),
              help="prefix for Boost libraries; should have 'include' and 'lib' subdirectories, 'boost' and 'stage\\lib' subdirectories on Windows")
    AddOption("--with-boost-include", dest="boost_include", type="string", nargs=1, action="store",
              metavar="DIR", help="location of Boost header files")
    AddOption("--with-boost-lib", dest="boost_lib", type="string", nargs=1, action="store",
              metavar="DIR", help="location of Boost libraries")
    AddOption("--rpath", dest="custom_rpath", type="string", action="append",
              help="runtime link paths to add to libraries and executables; may be passed more than once")
    AddOption("--boost-python-lib", dest="boost_python_lib", type="string", action="store",
              help="name of boost_python_lib", default='boost_python')
    variables = Variables()
    defaultflags = "-O2 -g"
    if os.name == 'nt':
        defaultflags = "/O2"
    variables.Add("CCFLAGS", default=os.environ.get("CCFLAGS", defaultflags), help="compiler flags")
    return variables

def makeEnvironment(variables):
    shellEnv = {}
    for key in ("PATH", "LD_LIBRARY_PATH", "DYLD_LIBRARY_PATH", "PYTHONPATH"):
        if key in os.environ:
            shellEnv[key] = os.environ[key]
    env = Environment(variables=variables, ENV=shellEnv)
    if "CCFLAGS" in os.environ:
        env.AppendUnique(CCFLAGS = os.environ["CCFLAGS"])
    custom_rpath = GetOption("custom_rpath")
    if custom_rpath is not None:
        env.AppendUnique(RPATH=custom_rpath)
    if env['CC'] == 'cl':
        # C++ exception handling,
        # multithread-supporting, dynamically linked system libraries,
        # generate debug information.
        env.AppendUnique(CPPFLAGS=['/EHsc', '/MD', '/Zi'])
    return env

def setupTargets(env, root="."):
    # Determine file extensions.
    VERSION = sys.version_info.major
    if os.name == 'nt':
        EXT_SUFFIX = '.dll'
        LIB_SUFFIX = '.lib'
        PY_SUFFIX = '.pyd'
    else:
        EXT_SUFFIX = sysconfig.get_config_var("EXT_SUFFIX")
        if VERSION == 2 and EXT_SUFFIX == 'None' or EXT_SUFFIX==None:
            EXT_SUFFIX = '.so'
        elif VERSION == 3 and EXT_SUFFIX == b'None' or EXT_SUFFIX==None:
            EXT_SUFFIX = '.so'
        LIB_SUFFIX = EXT_SUFFIX
        PY_SUFFIX = EXT_SUFFIX
    OBJ_SUFFIX = EXT_SUFFIX.replace ('.so', '.os')

    lib = SConscript(os.path.join(root, "libs", "numpy", "src", "SConscript"),
                     exports=['env', 'EXT_SUFFIX', 'LIB_SUFFIX', 'OBJ_SUFFIX'])
    example = SConscript(os.path.join(root, "libs", "numpy", "example", "SConscript"),
                         exports='env')
    test = SConscript(os.path.join(root, "libs", "numpy", "test", "SConscript"),
                      exports=['env', 'lib', 'EXT_SUFFIX', 'LIB_SUFFIX', 'OBJ_SUFFIX', 'PY_SUFFIX'])
    prefix = Dir(GetOption("prefix")).abspath
    install_headers = GetOption('install_headers')
    install_lib = GetOption('install_lib')
    if not install_headers:
        install_headers = os.path.join(prefix, "include")
    if not install_lib:
        install_lib = os.path.join(prefix, "lib")
    env.Alias("install", env.Install(install_lib, lib))
    for header in ("dtype.hpp", "invoke_matching.hpp", "matrix.hpp",
                   "ndarray.hpp", "numpy_object_mgr_traits.hpp",
                   "scalars.hpp", "ufunc.hpp",):
        env.Alias("install", env.Install(os.path.join(install_headers, "boost", "numpy"),
                                           os.path.join(root, "boost", "numpy", header)))
    env.Alias("install", env.Install(os.path.join(install_headers, "boost"),
                                     os.path.join(root, "boost", "numpy.hpp")))

Return("setupOptions", "makeEnvironment", "setupTargets", "_checks", "_libs")
