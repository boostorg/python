# Copyright David Abrahams 2004. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
'''
>>> from docstring_ext import *

>>> def selected_doc(obj, *args):
...   doc = obj.__doc__.splitlines()
...   return [doc[i] for i in args]

>>> selected_doc(X.__init__, 0, 1, 2)
['this is the __init__ function', 'its documentation has two lines.', 'C++ signature:']

>>> selected_doc(X.value, 0, 1, 3, 4, 5)
['gets the value of the object', 'C++ signature:', '', 'also gets the value of the object', 'C++ signature:']

>>> selected_doc(create, 0, 1)
['creates a new X object', 'C++ signature:']

>>> selected_doc(fact, 0, 1)
['compute the factorial', 'C++ signature:']

'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
        
    import docstring_ext
    
    result = doctest.testmod(sys.modules.get(__name__))
    
    import pydoc
    import re
    docmodule = lambda m: re.sub(".\10", "", pydoc.text.docmodule(m))
    try:
        print 'printing module help:'
        print docmodule(docstring_ext)
    except object, x:
        print '********* failed **********'
        print x
        result = list(result)
        result[0] += 1
        return tuple(result)
        
    return result
    
if __name__ == '__main__':
    print "running..."
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
