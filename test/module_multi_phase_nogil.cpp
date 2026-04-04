// Test for BOOST_PYTHON_MODULE_MULTI_PHASE with optional mod_gil_not_used argument

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

// Simple function to export
int get_value() {
    return 1234;
}

#if defined(HAS_CXX11) && (PY_VERSION_HEX >= 0x030D0000)
// C++11 build with Python 3.13+: test with mod_gil_not_used option
BOOST_PYTHON_MODULE_MULTI_PHASE(module_multi_phase_nogil_ext, boost::python::mod_gil_not_used())
{
    using namespace boost::python;
    def("get_value", get_value);
}
#else
// C++98 build or Python 3.12-: test without optional arguments
BOOST_PYTHON_MODULE_MULTI_PHASE(module_multi_phase_nogil_ext)
{
    using namespace boost::python;
    def("get_value", get_value);
}
#endif
