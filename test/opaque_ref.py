# -*- coding: utf-8 -*-
# Copyright Gottfried Ganßauge 2003..2006.  Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


"""
>>> from opaque_ref_ext import *


    Check for correct conversion
    
>>> use(get())

>>> useany(get())
1

>>> failuse(get())
Traceback (most recent call last):
        ...
RuntimeError: success

   Check that there is no conversion from integers ...
   
>>> try: use(0)
... except TypeError: pass
... else: print('expected a TypeError')

   ... and from strings to opaque objects
   
>>> try: use("")
... except TypeError: pass
... else: print('expected a TypeError')
"""
def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))
    
if __name__ == '__main__':
    print("running...")
    import sys
    status = run()[0]
    if (status == 0): print("Done.")
    sys.exit(status)
