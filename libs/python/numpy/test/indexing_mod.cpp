#include <boost/python/numpy.hpp>
#include <boost/python/slice.hpp>

namespace bp = boost::python;

bp::object single(bp::numpy::ndarray ndarr, int i) { return ndarr[i];}
bp::object slice(bp::numpy::ndarray ndarr, bp::slice sl) { return ndarr[sl];}

BOOST_PYTHON_MODULE(indexing_mod) 
{
  bp::numpy::initialize();
  bp::def("single", single);
  bp::def("slice", slice);
}
