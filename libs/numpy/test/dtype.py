#!/usr/bin/env python

import dtype_mod
import unittest
import numpy

class DtypeTestCase(unittest.TestCase):
    
    def testIntegers(self):
        for bits in (8, 16, 32, 64):
            s = getattr(numpy, "int%d" % bits)
            u = getattr(numpy, "uint%d" % bits)
            fs = getattr(dtype_mod, "accept_int%d" % bits)
            fu = getattr(dtype_mod, "accept_uint%d" % bits)
            self.assertEqual(fs(s(1)), numpy.dtype(s))
            self.assertEqual(fu(u(1)), numpy.dtype(u))
            # these should just use the regular Boost.Python converters
            self.assertEqual(fs(True), numpy.dtype(s))
            self.assertEqual(fu(True), numpy.dtype(u))
            self.assertEqual(fs(int(1)), numpy.dtype(s))
            self.assertEqual(fu(int(1)), numpy.dtype(u))
            self.assertEqual(fs(long(1)), numpy.dtype(s))
            self.assertEqual(fu(long(1)), numpy.dtype(u))
        for name in ("bool_", "byte", "ubyte", "short", "ushort", "intc", "uintc"):
            t = getattr(numpy, name)
            ft = getattr(dtype_mod, "accept_%s" % name)
            self.assertEqual(ft(t(1)), numpy.dtype(t))
            # these should just use the regular Boost.Python converters
            self.assertEqual(ft(True), numpy.dtype(t))
            if name != "bool_":
                self.assertEqual(ft(int(1)), numpy.dtype(t))
                self.assertEqual(ft(long(1)), numpy.dtype(t))


    def testFloats(self):
        f = numpy.float32
        c = numpy.complex64
        self.assertEqual(dtype_mod.accept_float32(f(numpy.pi)), numpy.dtype(f))
        self.assertEqual(dtype_mod.accept_complex64(c(1+2j)), numpy.dtype(c))
        f = numpy.float64
        c = numpy.complex128
        self.assertEqual(dtype_mod.accept_float64(f(numpy.pi)), numpy.dtype(f))
        self.assertEqual(dtype_mod.accept_complex128(c(1+2j)), numpy.dtype(c))
        if hasattr(numpy, "longdouble"):
            f = numpy.longdouble
            c = numpy.clongdouble
            self.assertEqual(dtype_mod.accept_longdouble(f(numpy.pi)), numpy.dtype(f))
            self.assertEqual(dtype_mod.accept_clongdouble(c(1+2j)), numpy.dtype(c))
            

if __name__=="__main__":
    unittest.main()
