r'''
//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

Automatic checking of the number and type of arguments. Foo's constructor takes
a single long parameter. 

    >>> ext = Foo()
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    TypeError: function requires exactly 1 argument; 0 given

    >>> try: ext = Foo('foo')
    ... except TypeError, err:
    ...     assert re.match(
    ... '(illegal argument type for built-in operation)|(an integer is required)', str(err))
    ... else: print 'no exception'

    >>> ext = Foo(1)

Call a virtual function. This call takes a trip into C++ where
FooCallback::add_len() looks up the Python "add_len" attribute and finds the
wrapper for FooCallback::default_add_len(), which in turn calls Foo::add_len(). 

    >>> ext.add_len('hello')
    6
    >>> ext.set(3)
    >>> ext.add_len('hello')
    8

Call a pure virtual function which should have been overridden, but was not.

    >>> ext.call_pure()
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: pure

We can subclass Foo.

    >>> class Subclass(Foo):
    ...     def __init__(self, seq):
    ...         Foo.__init__(self, len(seq))
    ...         
    ...     def pure(self):
    ...         return 'not pure anymore!'
    ...     
    ...     def get(self):
    ...         return Foo.add_len(self, '')
    ...     
    ...     def add_len(self, s):
    ...         print 'called add_len()'
    ...         return self.get() + len(s)
    ... 
    >>> b = Subclass('yippee')
    >>> b.get()
    6
    >>> b.mumble()
    'mumble'
    >>> b.call_pure()
    'not pure anymore!'

If no __init__ function is defined, the one from the base class takes effect, just
like in a Python class.

    >>> class DemonstrateInitPassthru(Foo): pass
    ... 
    >>> q = DemonstrateInitPassthru(1)
    >>> q.add_len("x")
    2

If we don't initialize the base class, we'll get a RuntimeError when we try to
use its methods. The test illustrates the kind of error to expect.

    >>> class BadSubclass(Foo):
    ...     def __init__(self): pass
    ...
    >>> barf = BadSubclass()
    >>> barf.set(4)
    Traceback (innermost last):
       ...
    RuntimeError: __init__ function for extension class 'Foo' was never called.

Here we are tesing that the simple definition procedure used in the C++ demo
file for classes without any virtual functions actually worked.

    >>> bar = Bar(3, 4)
    >>> bar.first()
    3
    >>> bar.second()
    4
    >>> baz = Baz()

We can actually return the wrapped classes by value

    >>> baz.pass_bar(bar).first()
    3
    >>> bar.pass_baz(baz) is baz # A copy of the return value is made.
    0
    >>> type(bar.pass_baz(baz)) is type(baz)
    1

And, yes, we can multiply inherit from these classes.

    >>> class MISubclass(Subclass, Bar):
    ...     def __init__(self, s):
    ...         Subclass.__init__(self, s)
    ...         Bar.__init__(self, 0, len(s))
    ...
    >>> mi = MISubclass('xx')
    >>> mi.first()
    0
    >>> mi.second()
    2
    >>> mi.mumble()
    'mumble'

Any object whose class is derived from Bar can be passed to a function expecting
a Bar parameter:

    >>> baz.pass_bar(mi).first()
    0

But objects not derived from Bar cannot:

    >>> baz.pass_bar(baz)
    Traceback (innermost last):
        ...
    TypeError: extension class 'Baz' is not convertible into 'Bar'.

The clone function on Baz returns a smart pointer; we wrap it into an
ExtensionInstance and  make it look just like any other Baz instance.

    >>> baz_clone = baz.clone()
    >>> baz_clone.pass_bar(mi).first()
    0

Functions expecting an std::auto_ptr<Baz> parameter will not accept a raw Baz

    >>> try: baz.eat_baz(Baz())
    ... except RuntimeError, err:
    ...     assert re.match("Object of extension class 'Baz' does not wrap <.*>.",
    ...                     str(err))
    ... else:
    ...     print 'no exception'

We can pass std::auto_ptr<Baz> where it is expected

    >>> baz.eat_baz(baz_clone)

And if the auto_ptr has given up ownership?

    # MSVC6 ships with an outdated auto_ptr that doesn't get zeroed out when it
    # gives up ownership. If you are using MSVC6 without the new Dinkumware
    # library, SGI STL or the STLport, expect this test to crash unless you put
    # --broken-auto-ptr on the command line.
    >>> if not '--broken-auto-ptr' in sys.argv:
    ...     try: baz_clone.clone()
    ...     except RuntimeError, err:
    ...         assert re.match('Converting from python, pointer or smart pointer to <.*> is NULL.', str(err))
    ...     else:
    ...         print 'no exeption'
    
Polymorphism also works:
    
    >>> polymorphic_foo = baz.create_foo()
    >>> polymorphic_foo.call_pure()
    'this was never pure!'
    >>> baz.get_foo_value(polymorphic_foo)
    1000

Special member functions in action
  
    >>> m = StringMap()

__getitem__(<unknown key>)
    >>> m[1]
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 1

__setitem__()
  
    >>> m[1] = 'hello'

__getitem__(<known key>)    
    >>> m[1]
    'hello'
    
__delitem__(<known key>)
    >>> del m[1]
    >>> m[1]            # prove that it's gone
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 1

__delitem__(<unknown key>)
    >>> del m[2]
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 2

__length__()
    >>> len(m)
    0
    >>> m[3] = 'farther'
    >>> len(m)
    1

Check for sequence/mapping confusion:
    >>> for x in m:
    ...     print x
    ...
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 0

Overloading tests:
    >>> r = Range(3)
    >>> print str(r)
    (3, 3)
    >>> r.start
    3
    >>> r.finish
    3
    >>> r.__len__()
    0
    >>> r.__len__(4)
    >>> r.finish
    7
    >>> try: r = Range('yikes')
    ... except TypeError, e:
    ...     assert re.match(
    ... 'No overloaded functions match [(]Range, string[)]\. Candidates are:\n.*\n.*',
    ...  str(e))
    ... else: print 'no exception'
    
Sequence tests:
    >>> len(Range(3, 10))
    7
    
    >>> map(lambda x:x, Range(3, 10))
    [3, 4, 5, 6, 7, 8, 9]
    
    >>> map(lambda x:x, Range(3, 10)[-2:])
    [8, 9]
    
    >>> map(lambda x:x, Range(3, 10)[:-4])
    [3, 4, 5]
    
    >>> map(lambda x:x, Range(3, 10)[4:])
    [7, 8, 9]
      
    >>> map(lambda x:x, Range(3, 10)[4:100])
    [7, 8, 9]
      
    >>> map(lambda x:x, Range(3, 10)[20:])
    []
      
    >>> map(lambda x:x, Range(3, 10)[0:4])
    [3, 4, 5, 6]

Numeric tests:
    >>> x = Rational(2,3)
    >>> y = Rational(1,4)
    >>> print x + y
    11/12
    >>> print x - y
    5/12
    >>> print x * y
    1/6
    >>> print x / y
    8/3
    >>> print x + 1 # testing coercion
    5/3
    >>> print 1 + x # coercion the other way
    5/3
    
delete non-existent attribute:
    del m.foobar
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: delete non-existing instance attribute
    
Testing __getattr__ and __getattr__<name>:
  
    >>> n = IntPair(1, 2)
    >>> n.first
    1
    >>> n.second
    2
    >>> n.third
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: third

Testing __setattr__ and __setattr__<name>:
    >>> n.first = 33 # N.B  __setattr__first sets first to 
    >>> n.first      # the negative of its argument.
    -33
    >>> n.second = 66
    >>> n.second
    66
    
Testing __delattr__ and __delattr__<name>:
    >>> del n.first
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: first can't be deleted!
    >>> del n.second
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: Attributes can't be deleted!
    >>> del n.third
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: Attributes can't be deleted!
    
    # Now show that we can override it.
    
    >>> class IntTriple(IntPair):
    ...     def __getattr__(self, s):
    ...         if s in ['first', 'second']:
    ...             return IntPair.__getattr__(self, s)
    ...         elif s == 'third':
    ...             return 3
    ...         else:
    ...             raise AttributeError(s)
    ...     
    ...     # Also show that __setattr__ is supported
    ...     def __setattr__(self, name, value):
    ...         raise AttributeError('no writable attributes')
    ...
    >>> p = IntTriple(0, 1)
    >>> p.first
    0
    >>> p.second
    1
    >>> p.third
    3
    >>> p.bax
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: bax
    >>> p.third = 'yes'
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: no writable attributes
    >>> del p.third
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: Attributes can't be deleted!

demonstrate def_readonly, def_read_write:
    >>> sp = StringPair("hello", "world")
    >>> sp.first  # first is read-only
    'hello'
    >>> first_string(sp) # prove that we're not just looking in sp's __dict__
    'hello'
    >>> sp.first = 'hi' # we're not allowed to change it
    Traceback (innermost last):
      File "<string>", line 1, in ?
    AttributeError: 'first' attribute is read-only
    >>> first_string(sp) # prove that it hasn't changed
    'hello'
    
    >>> sp.second  # second is read/write
    'world'
    >>> second_string(sp)
    'world'
    >>> sp.second = 'universe' # set the second attribute
    >>> sp.second
    'universe'
    >>> second_string(sp)  # this proves we didn't just set it in sp's __dict__
    'universe'

some __str__ and __repr__ tests:
    >>> sp
    ('hello', 'universe')
    >>> repr(sp)
    "('hello', 'universe')"
    >>> str(sp)
    "('hello', 'universe')"

  Range has a __str__ function but not a __repr__ function
    >>> range = Range(5, 20)
    >>> str(range)
    '(5, 20)'
    >>> assert re.match('<Range object at [0-9a-fA-F]+>', repr(range))


__hash__ and __cmp__ tests:
    # Range has both __hash__ and __cmp__, thus is hashable
    >>> colors = { Range(3,4): 'blue', Range(7,9): 'red' }
    >>> colors[Range(3,4)]
    'blue'

    # StringPair has only __cmp__
    >>> { StringPair('yo', 'eddy'): 1 }
    Traceback (innermost last):
      File "<string>", line 1, in ?
    TypeError: unhashable type

    # But it can be sorted
    >>> stringpairs = [ StringPair('yo', 'eddy'), StringPair('yo', 'betty'), sp ]
    >>> stringpairs.sort()
    >>> stringpairs
    [('hello', 'universe'), ('yo', 'betty'), ('yo', 'eddy')]
    
make_pair is a global function in the module.

    >>> couple = make_pair(3,12)
    >>> couple.first
    3
    >>> couple.second
    12

Testing __call__:
    >>> couple2 = make_pair(3, 7)
    >>> comparator = CompareIntPair()
    >>> comparator(couple, couple)
    0
    >>> comparator(couple, couple2)
    0
    >>> comparator(couple2, couple)
    1

Testing overloaded free functions
    >>> overloaded()
    'Hello world!'
    >>> overloaded(1)
    1
    >>> overloaded('foo')
    'foo'
    >>> overloaded(1,2)
    3
    >>> overloaded(1,2,3)
    6
    >>> overloaded(1,2,3,4)
    10
    >>> overloaded(1,2,3,4,5)
    15
    >>> try: overloaded(1, 'foo')
    ... except TypeError, err:
    ...     assert re.match("No overloaded functions match \(int, string\)\. Candidates are:",
    ...                     str(err))
    ... else:
    ...     print 'no exception'
    
Testing overloaded constructors

    >>> over = OverloadTest()
    >>> over.getX()
    1000
    >>> over = OverloadTest(1)
    >>> over.getX()
    1
    >>> over = OverloadTest(1,1)
    >>> over.getX()
    2
    >>> over = OverloadTest(1,1,1)
    >>> over.getX()
    3
    >>> over = OverloadTest(1,1,1,1)
    >>> over.getX()
    4
    >>> over = OverloadTest(1,1,1,1,1)
    >>> over.getX()
    5
    >>> over = OverloadTest(over)
    >>> over.getX()
    5
    >>> try: over = OverloadTest(1, 'foo')
    ... except TypeError, err:
    ...     assert re.match("No overloaded functions match \(OverloadTest, int, string\)\. Candidates are:",
    ...                     str(err))
    ... else:
    ...     print 'no exception'
    
Testing overloaded methods

    >>> over.setX(3)
    >>> over.overloaded()
    3
    >>> over.overloaded(1)
    1
    >>> over.overloaded(1,1)
    2
    >>> over.overloaded(1,1,1)
    3
    >>> over.overloaded(1,1,1,1)
    4
    >>> over.overloaded(1,1,1,1,1)
    5
    >>> try: over.overloaded(1,'foo')
    ... except TypeError, err:
    ...     assert re.match("No overloaded functions match \(OverloadTest, int, string\)\. Candidates are:",
    ...                     str(err))
    ... else:
    ...     print 'no exception'

Testing base class conversions

    >>> testUpcast(over)
    Traceback (innermost last):
    TypeError: extension class 'OverloadTest' is not convertible into 'Base'.
    >>> der1 = Derived1(333)
    >>> der1.x()
    333
    >>> testUpcast(der1)
    333
    >>> der1 = derived1Factory(1000)
    >>> testDowncast1(der1)
    1000
    >>> testDowncast2(der1)
    Traceback (innermost last):
    TypeError: extension class 'Base' is not convertible into 'Derived2'.
    >>> der2 = Derived2(444)
    >>> der2.x()
    444
    >>> testUpcast(der2)
    444
    >>> der2 = derived2Factory(1111)
    >>> testDowncast2(der1)
    Traceback (innermost last):
    TypeError: extension class 'Base' is not convertible into 'Derived2'.
    
Testing interaction between callbacks, base declarations, and overloading
- testCallback() calls callback() (within C++)
- callback() is overloaded (in the wrapped class CallbackTest)
- callback() is redefined in RedefineCallback (overloading is simulated by type casing)
- testCallback() should use the redefined callback()

    >>> c = CallbackTest()
    >>> c.testCallback(1)
    2
    >>> c.testCallback('foo')
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    TypeError: illegal argument type for built-in operation
    >>> c.callback(1)
    2
    >>> c.callback('foo')
    'foo 1'
    
    >>> import types
    >>> class RedefineCallback(CallbackTest):
    ...     def callback(self, x): 
    ...             if type(x) is types.IntType:
    ...                     return x - 2
    ...             else:
    ...                     return CallbackTest.callback(self,x)
    ... 
    >>> r = RedefineCallback()
    >>> r.callback(1)
    -1
    >>> r.callback('foo')
    'foo 1'
    >>> r.testCallback('foo')
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    TypeError: illegal argument type for built-in operation
    >>> r.testCallback(1)
    -1
    >>> testCallback(r, 1)
    -1
'''

from demo import *
import string
import re
import sys

def run(args = None):
    if args is not None:
        sys.argv = args
    import doctest, test_extclass
    doctest.testmod(test_extclass)
    
if __name__ == '__main__':
    run()
