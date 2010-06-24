import templates_mod
import unittest
import numpy

class TestTemplates(unittest.TestCase):

    def testTemplates(self):
        for dtype in (numpy.int16, numpy.int32, numpy.float32, numpy.complex128):
            a1 = numpy.zeros((12,), dtype=dtype)
            a2 = numpy.arange(12, dtype=dtype)
            templates_mod.fill(a1)
            self.assert_((a1 == a2).all())
        a1 = numpy.zeros((12,), dtype=numpy.float64)
        self.assertRaises(TypeError, templates_mod.fill, a1)

if __name__=="__main__":
    unittest.main()
