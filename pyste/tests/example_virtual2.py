import unittest
from virtual2 import *

class Virtual2Test(unittest.TestCase):

    def testIt(self):
        a = A()
        self.assertEqual(a.f1(), 10)
        b = B()
        self.assertEqual(b.f1(), 10)
        self.assertEqual(b.f2(), 20)
        self.assertEqual(call(b), 30)

        class C(B):
            def f1(self): return 1
            def f2(self): return 2

        c = C()
        self.assertEqual(call(c), 3)


if __name__ == '__main__':
    unittest.main()  
