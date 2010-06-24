#include <boost/python/numpy/numpy.hpp>
#include <boost/mpl/vector.hpp>

namespace bp = boost::python;

struct ArrayFiller {

    typedef boost::mpl::vector< short, int, float, std::complex<double> > Sequence;

    template <typename T>
    void apply() const {
        char * p = argument.get_data();
        int stride = argument.strides(0);
        int size = argument.shape(0);
        for (int n = 0; n != size; ++n, p += stride) {
            *reinterpret_cast<T*>(p) = static_cast<T>(n);
        }
    }

    bp::numpy::ndarray argument;

    explicit ArrayFiller(bp::numpy::ndarray const & arg) : argument(arg) {}

};

void fill(bp::numpy::ndarray const & arg) {
    ArrayFiller filler(arg);
    arg.get_dtype().invoke_matching_template< ArrayFiller::Sequence >(filler);
}

BOOST_PYTHON_MODULE(templates_mod) {
    bp::numpy::initialize();
    bp::def("fill", &fill);
}
