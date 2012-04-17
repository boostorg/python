# -*- python -*-
setupOptions, makeEnvironment, setupTargets, checks = SConscript("SConscript")

variables = setupOptions()

env = makeEnvironment(variables)
env.AppendUnique(CPPPATH="#.")

if not GetOption("help") and not GetOption("clean"):
    config = env.Configure(custom_tests=checks)
    if not (config.CheckPython() and config.CheckNumPy() and config.CheckBoostPython()):
       Exit(1)
    env = config.Finish()

setupTargets(env)
