#include <boost/python/numpy.hpp>

namespace bp = boost::python;

bp::numpy::ndarray reshape(bp::numpy::ndarray old_array, bp::tuple shape) {
	bp::numpy::ndarray local_shape =  old_array.reshape(shape);
	return local_shape;
}

BOOST_PYTHON_MODULE(shapes_mod) {
    bp::numpy::initialize();
    bp::def("reshape", &reshape);
}
