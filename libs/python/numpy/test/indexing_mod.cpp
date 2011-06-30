#include <boost/python/numpy.hpp>
#include <boost/python/slice.hpp>

namespace bp = boost::python;

bp::object single(bp::numpy::ndarray ndarr, int i) { return ndarr[i];}
bp::object slice(bp::numpy::ndarray ndarr, bp::slice sl) { return ndarr[sl];}
bp::object indexarray(bp::numpy::ndarray ndarr, bp::numpy::ndarray d1) { return ndarr[d1];}
bp::object indexarray_2d(bp::numpy::ndarray ndarr, bp::numpy::ndarray d1,bp::numpy::ndarray d2) { return ndarr[d1][d2];}
bp::object indexslice(bp::numpy::ndarray ndarr, bp::numpy::ndarray d1,bp::slice sl) { return ndarr[d1][sl];}

BOOST_PYTHON_MODULE(indexing_mod) 
{
	bp::numpy::initialize();
	bp::def("single", &single);
	bp::def("slice", &slice);
	bp::def("indexarray", &indexarray);
	bp::def("indexarray", &indexarray_2d);
	bp::def("indexslice", &indexslice);

}
