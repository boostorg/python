#include <boost/python/numpy.hpp>

namespace bp = boost::python;

bp::numpy::ndarray zeros(bp::tuple shape, bp::numpy::dtype dt) {
	return bp::numpy::zeros(shape, dt);
}

bp::numpy::ndarray array2(bp::object obj,bp::numpy::dtype dt) {
	return bp::numpy::array(obj,dt);
}

bp::numpy::ndarray array1(bp::object obj) {
	return bp::numpy::array(obj);
}

bp::numpy::ndarray empty1(bp::tuple shape, bp::numpy::dtype dt) {
	return bp::numpy::empty(shape,dt);
}

bp::numpy::ndarray c_empty(int nd,bp::tuple shape, bp::numpy::dtype dt) {
	bp::tuple c_tup  = bp::make_tuple(shape);
	Py_intptr_t* c_shape = bp::extract<Py_intptr_t *>(c_tup);
	return bp::numpy::empty(nd,c_shape,dt);
}

BOOST_PYTHON_MODULE(ndarray_mod) {
	bp::numpy::initialize();
	bp::def("zeros", &zeros);
	bp::def("array",&array2);
	bp::def("array",&array1);
	bp::def("empty",&empty1);
	bp::def("empty",&c_empty);
}
