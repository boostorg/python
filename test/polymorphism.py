import unittest
from polymorphism_ext import *

class PolymorphTest(unittest.TestCase):

   def testReturnCpp(self):

      # Python Created Object With Same Id As
      # Cpp Created B Object 
      # b = B(872)  

      #  Get Reference To Cpp Created B Object
      a = getBCppObj()

      # Python Created B Object and Cpp B Object
      # Should have same result by calling f()
      self.failUnlessEqual ('B::f()', a.f())
      self.failUnlessEqual ('B::f()', call_f(a))
      self.failUnlessEqual ('A::f()', call_f(A()))
      
   def testReturnPy(self):

      class C(A):
         def f(self):
            return 'C.f'

      c = C()
      
      self.failUnlessEqual ('C.f', c.f())
      self.failUnlessEqual ('C.f', call_f(c))

if __name__ == "__main__":
   
   # remove the option which upsets unittest
   import sys
   sys.argv = [ x for x in sys.argv if x != '--broken-auto-ptr' ]
   
   unittest.main()
