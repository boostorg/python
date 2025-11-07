// Test for BOOST_PYTHON_MODULE with optional mod_gil_not_used argument

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

// Simple function to export
int get_value() {
    return 1234;
}

#ifdef HAS_CXX11
// C++11 build: test with mod_gil_not_used option
BOOST_PYTHON_MODULE(module_nogil_ext, boost::python::mod_gil_not_used())
{
    using namespace boost::python;
    def("get_value", get_value);
}
#else
// C++98 build: test without optional arguments
BOOST_PYTHON_MODULE(module_nogil_ext)
{
    using namespace boost::python;
    def("get_value", get_value);
}
#endif
