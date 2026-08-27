# Copyright Fady Essam 2019. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
from __future__ import print_function
"""
>>> import set_ext
>>> set_ext.new_set()
set()
>>> set_ext.data_set()
{2, 'value1'}
>>> set_ext.set_from_sequence([1,2,3,3])
{1, 2, 3}
>>> s = set_ext.new_set()
>>> set_ext.test_templates(print)
{'a test string'}
False
True
{'a test string', 13}
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
