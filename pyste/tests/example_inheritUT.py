import unittest
from inherit import *

class InheritExampleTest(unittest.TestCase):

    def testIt(self):
        a = A_int()        
        b = B()
        self.assert_(isinstance(b, A_int))
        self.assert_(issubclass(B, A_int))
        a.set(10)
        self.assertEqual(a.get(), 10)        
        b.set(1)
        self.assertEqual(b.go(), 1)
        self.assertEqual(b.get(), 1)



if __name__ == '__main__':
    unittest.main() 
