#define BOOST_PYTHON_NUMPY_INTERNAL_MAIN
#include <boost/python/numpy/internal.hpp>

namespace boost { namespace python {

namespace numpy {

void initialize() {
    import_array();
    import_ufunc();
}

}}}
