import unittest
import vars


class VarsTest(unittest.TestCase):

    def testIt(self):
        def testColor(c, r, g, b):
            self.assertEqual(c.r, r)            
            self.assertEqual(c.g, g)            
            self.assertEqual(c.b, b)            
        testColor(vars.black, 0, 0, 0)
        testColor(vars.red, 255, 0, 0)
        testColor(vars.green, 0, 255, 0)
        testColor(vars.blue, 0, 0, 255)


