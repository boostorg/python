import unittest
from smart_ptr import *

class BasicExampleTest(unittest.TestCase):

    def testIt(self):
        c = NewC()
        d = NewD()
        c.value = 3
        d.Set(c)
        c1 = d.Get()
        c1.value = 6
        self.assertEqual(c.value, 6)

if __name__ == '__main__':
    unittest.main()     
