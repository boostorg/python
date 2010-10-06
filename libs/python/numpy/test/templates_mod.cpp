#include <boost/python/numpy/numpy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>

namespace bp = boost::python;

struct ArrayFiller {

    typedef boost::mpl::vector< short, int, float, std::complex<double> > TypeSequence;
    typedef boost::mpl::vector_c< int, 1, 2 > DimSequence;

    template <typename T, int N>
    void apply() const {
        if (N == 1) {
            char * p = argument.get_data();
            int stride = argument.strides(0);
            int size = argument.shape(0);
            for (int n = 0; n != size; ++n, p += stride) {
                *reinterpret_cast<T*>(p) = static_cast<T>(n);
            }
        } else {
            char * row_p = argument.get_data();
            int row_stride = argument.strides(0);
            int col_stride = argument.strides(1);
            int rows = argument.shape(0);
            int cols = argument.shape(1);
            int i = 0;
            for (int n = 0; n != rows; ++n, row_p += row_stride) {
                char * col_p = row_p;
                for (int m = 0; m != cols; ++i, ++m, col_p += col_stride) {
                    *reinterpret_cast<T*>(col_p) = static_cast<T>(i);
                }
            }
        }
    }

    bp::numpy::ndarray argument;

    explicit ArrayFiller(bp::numpy::ndarray const & arg) : argument(arg) {}

};

void fill(bp::numpy::ndarray const & arg) {
    ArrayFiller filler(arg);
    bp::numpy::invoke_matching_array< ArrayFiller::TypeSequence, ArrayFiller::DimSequence >(arg, filler);
}

BOOST_PYTHON_MODULE(templates_mod) {
    bp::numpy::initialize();
    bp::def("fill", &fill);
}
