# Example by Ullrich Koethe
r'''>>> from abstract import *
    >>> class A(Abstract):
    ...     def __init__(self, text):
    ...             Abstract.__init__(self)  # call the base class constructor
    ...             self.text = text
    ...     def test(self):                  # implement abstract function
    ...             return self.text
    ...
    >>> a = A("Hello")
    >>> a.test()
    'Hello'
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_abstract
    return doctest.testmod(test_abstract)

if __name__ == '__main__':
    import sys
    sys.exit(run()[0])
