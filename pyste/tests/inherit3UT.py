import unittest
from _inherit3 import *

class testInherit3(unittest.TestCase):

    def testIt(self):
        def testClass(class_):
            c = class_()
            self.assertEqual(c.x, 0)
            self.assertEqual(c.foo(), 1)
            x = class_.X()
            self.assertEqual(x.y, 0)
            self.assertEqual(class_.E.i, 0)
            self.assertEqual(class_.E.j, 1)
        testClass(B)
        testClass(C)

if __name__ == '__main__':
    unittest.main()
