#include <boost/python/numpy.hpp>
#include <assert.h>
#include <boost/python/slice.hpp>

namespace bp = boost::python;

void single(bp::numpy::ndarray ndarr, int i,bp::object value) {
	bp::object element = bp::extract<bp::object>(ndarr[i]);
	assert(element == value);
}


void slice(bp::numpy::ndarray ndarr, bp::slice sl,bp::object val) {
	int start = bp::extract<int>(sl.start());
	int stop  = bp::extract<int>(sl.stop());
	unsigned j=0;
 	for (int i = start; i < stop; i++)
    	{
			bp::object element = bp::extract<bp::object>(ndarr[i]);
			bp::object value = bp::extract<bp::object>(val[j]);
			assert(element == value);
			++j;
	}
}


void step_slice(bp::numpy::ndarray ndarr, bp::slice sl,bp::object val) {
	int start = bp::extract<int>(sl.start());
	int stop  = bp::extract<int>(sl.stop());
	int step = bp::extract<int>(sl.step());
	unsigned j=0;
 	for (int i = start; i < stop; i=i+step)
    	{
			bp::object element = bp::extract<bp::object>(ndarr[i]);
			bp::object value = bp::extract<bp::object>(val[j]);
			assert(element == value);
			++j;
	}
}


BOOST_PYTHON_MODULE(indexing_mod) {
    bp::numpy::initialize();
	bp::def("single",&single);
	bp::def("slice",&slice);
	bp::def("step_slice",&step_slice);
}

