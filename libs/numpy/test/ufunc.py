import ufunc_mod
import unittest
import numpy

class TestUnary(unittest.TestCase):

    def testScalar(self):
        f = ufunc_mod.UnaryCallable()
        self.assertEqual(f(1.0), 2.0)
        self.assertEqual(f(3.0), 6.0)

    def testArray(self):
        f = ufunc_mod.UnaryCallable()
        a = numpy.arange(5, dtype=float)
        b = f(a)
        self.assert_((b == a*2.0).all())
        c = numpy.zeros(5, dtype=float)
        d = f(a,output=c)
        self.assert_((c == a*2.0).all())
        self.assert_((d == a*2.0).all())

    def testList(self):
        f = ufunc_mod.UnaryCallable()
        a = range(5)
        b = f(a)
        self.assert_((b/2.0 == a).all())

class TestBinary(unittest.TestCase):

    def testScalar(self):
        f = ufunc_mod.BinaryCallable()
        self.assertEqual(f(1.0, 3.0), 11.0)
        self.assertEqual(f(3.0, 2.0), 12.0)

    def testArray(self):
        f = ufunc_mod.BinaryCallable()
        a = numpy.random.randn(5)
        b = numpy.random.randn(5)
        self.assert_((f(a,b) == (a*2+b*3)).all())
        c = numpy.zeros(5, dtype=float)
        d = f(a,b,output=c)
        self.assert_((c == a*2 + b*3).all())
        self.assert_((d == a*2 + b*3).all())
        self.assert_((f(a, 2.0) == a*2 + 6.0).all())
        self.assert_((f(1.0, b) == 2.0 + b*3).all())
        

if __name__=="__main__":
    unittest.main()
