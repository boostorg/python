import unittest
from _enums import *

class EnumsTest(unittest.TestCase):

    def testIt(self):
        self.assertEqual(int(color.Red), 0)
        self.assertEqual(int(color.Blue), 1)

        self.assertEqual(int(X.Choices.Good), 1)
        self.assertEqual(int(X.Choices.Bad), 2)
        x = X()
        self.assertEqual(x.set(x.Choices.Good), 1)
        self.assertEqual(x.set(x.Choices.Bad), 2)
        self.assertEqual(unnamed.x, 0)
        self.assertEqual(unnamed.y, 1)


if __name__ == '__main__':
    unittest.main()
