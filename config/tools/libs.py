#
# Copyright (c) 2016 Stefan Seefeld
# All rights reserved.
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

import distutils.sysconfig
from SCons.Script import AddOption, COMMAND_LINE_TARGETS, BUILD_TARGETS


def BoostLibrary(env, lib, sources, make_aliases = True, **kw):
    if env["LINK_DYNAMIC"]:
        lib_node = env.SharedLibrary("boost_" + lib + env["BOOST_SUFFIX"], sources, **kw)
    else:
        lib_node = env.StaticLibrary("boost_" + lib + env["BOOST_SUFFIX"], sources, **kw)

    if make_aliases:
        if env.GetOption("stage"):
            env.Alias(lib, env.Install(env.Dir("$stagedir", "#"), lib_node))
        env.Default(env.Alias(lib, lib_node))

        if env.GetOption("install"):
            env.Alias(lib, env.Install("$prefix/lib", lib_node))
    return lib_node


def BoostUseLib(env, lib):
    env.AppendUnique(
        LIBPATH = [env.Dir("$BOOST_CURRENT_VARIANT_DIR/src")],
        LIBS = ["boost_" + lib + env["BOOST_SUFFIX"]]
    )
    if env.get("BOOST_TEST"):
        env.AppendUnique(RPATH = [env.Dir("$BOOST_CURRENT_VARIANT_DIR/src")])


def PythonExtension(env, lib, sources, **kw):
    if env["LINK_DYNAMIC"]:
        #env.AppendUnique(CPPDEFINES = ['BOOST_PYTHON_DYN_LINK=1'])
        ext = env.SharedLibrary(lib, sources, SHLIBPREFIX='', SHLIBSUFFIX=distutils.sysconfig.get_config_var("SO"), **kw)
        #env.Alias(lib, ext)
        return ext


def boost_copy_func(dest, source, env):
    import os, stat, shutil

    if os.path.isdir(source):
        if os.path.exists(dest):
            if not os.path.isdir(dest):
                raise SCons.Errors.UserError, "cannot overwrite non-directory `%s' with a directory `%s'" % (str(dest), str(source))
        else:
            os.makedirs(dest)
        for file in os.listdir(source):
            if file == ".svn": continue
            boost_copy_func(os.path.join(dest, file), os.path.join(source, file), env)
    else:
        shutil.copy2(source, dest)
        st = os.stat(source)
        os.chmod(dest, stat.S_IMODE(st[stat.ST_MODE]) | stat.S_IWRITE)

    return 0


def exists(env):
    return True


def generate(env):
    env.AddMethod(BoostLibrary)
    env.AddMethod(BoostUseLib)
    env.AddMethod(PythonExtension)

    env.Replace(
        INSTALL = boost_copy_func,
        BOOST_CURRENT_VARIANT_DIR = "$BOOST_BUILD_DIR/$current_variant/$linking/threading-$current_threading"
    )

    AddOption('--stage', dest='stage', action="store_true")
    AddOption('--install', dest='install', action="store_true")

    #if env.GetOption("install"):
    #    BUILD_TARGETS.extend(env.Alias("install-headers"))
