# A stand-in for the real extension module. We're just using this one to
# simulate it while we have all the parts linked together into cpp.dll

# using "import*-safe" imports
import sys
_sys = sys
del sys

import os
_os = os
del os

_savecwd = _os.getcwd()

if len(_sys.argv) > 1:
    _os.chdir(_sys.argv[1])

try:
    from cpp import *
finally:
    if len(_sys.argv) > 1:
        _os.chdir(_savecwd)

