import unittest
import numpy
import indexing_mod

class TestIndexing(unittest.TestCase):

	def testSingle(self):
		x = numpy.arange(0,10)
		for i in range(0,10):
			indexing_mod.single(x,i,i)
		for i in range(-10,0):
			indexing_mod.single(x,i,10+i)

	def testSlice(self):
		x = numpy.arange(0,10)
		sl = slice(3,8)
		b = [3,4,5,6,7]
		indexing_mod.slice(x,sl,b)

if __name__=="__main__":
	unittest.main()
