import ndarray_mod
import unittest
import numpy

class TestNdarray(unittest.TestCase):
	
	def testNdzeros(self):	
		for dtp in (numpy.int16, numpy.int32, numpy.float32, numpy.complex128):
			v = numpy.zeros(60, dtype=dtp)
			dt = numpy.dtype(dtp)
			for shape in ((60,),(6,10),(4,3,5),(2,2,3,5)):
				a1 = ndarray_mod.zeros(shape,dt)
				a2 = v.reshape(a1.shape)
				self.assertEqual(shape,a1.shape)
				self.assert_((a1 == a2).all())

	def testNdarray(self):	
		a = range(0,60)
		for dtp in (numpy.int16, numpy.int32, numpy.float32, numpy.complex128):
			v = numpy.array(a, dtype=dtp)
			dt = numpy.dtype(dtp)
			a1 = ndarray_mod.array(a)
			a2 = ndarray_mod.array(a,dt)
			self.assert_((a1 == v).all())
			self.assert_((a2 == v).all())
			for shape in ((60,),(6,10),(4,3,5),(2,2,3,5)):
				a1 = a1.reshape(shape)
				self.assertEqual(shape,a1.shape)
				a2 = a2.reshape(shape)
				self.assertEqual(shape,a2.shape)

	def testNdempty(self):
		for dtp in (numpy.int16, numpy.int32, numpy.float32, numpy.complex128):
			dt = numpy.dtype(dtp)
			for shape in ((60,),(6,10),(4,3,5),(2,2,3,5)):
				a1 = ndarray_mod.empty(shape,dt)
				a2 = ndarray_mod.empty(len(shape),shape,dt)
				self.assert_(shape,a1.shape)
				self.assert_(type(a1),dtp)
				self.assert_(shape,a2.shape)
				self.assert_(dt,type(a2))

if __name__=="__main__":
	unittest.main()
