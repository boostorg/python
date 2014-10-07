# -*- python -*-

# Copyright Jim Bosch 2010-2012.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

from SConsChecks import GetLibChecks

setupOptions, makeEnvironment, setupTargets, checks, libnames = SConscript("SConscript")

variables = setupOptions()

env = makeEnvironment(variables)
env.AppendUnique(CPPPATH="#.")

if not GetOption("help") and not GetOption("clean"):
    config = env.Configure(custom_tests=checks)
    checknames = GetLibChecks(libnames).keys()
    if False in (config.__dict__[checkname]() for checkname in checknames):
        Exit(1)
    env = config.Finish()

setupTargets(env)
