#include <cmath>
#include <memory>

#include <boost/numpy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace bp = boost::python;
namespace bn = boost::numpy;

/**
 *  This class represents a simple 2-d Gaussian (Normal) distribution, defined by a
 *  mean vector 'mu' and a covariance matrix 'sigma'.
 */
class bivariate_gaussian {
public:

    /** 
     *  Boost.NumPy isn't designed to support specific C++ linear algebra or matrix/vector libraries;
     *  it's intended as a lower-level interface that can be used with any such C++ library.
     *
     *  Here, we'll demonstrate these techniques with boost::ublas, but the same general principles
     *  should apply to other matrix/vector libraries.
     */
    typedef boost::numeric::ublas::c_vector<double,2> vector;
    typedef boost::numeric::ublas::c_matrix<double,2,2> matrix;

    vector const & get_mu() const { return _mu; }

    matrix const & get_sigma() const { return _sigma; }

    /**
     *  Evaluate the density of the distribution at a point defined by a two-element vector.
     */
    double operator()(vector const & p) const {
        vector u = prod(_cholesky, p - _mu);
        return 0.5 * _cholesky(0, 0) * _cholesky(1, 1) * std::exp(-0.5 * inner_prod(u, u)) / M_PI;
    }

    /**
     *  Evaluate the density of the distribution at an (x, y) point.
     */
    double operator()(double x, double y) const {
        vector p;
        p[0] = x;
        p[1] = y;
        return operator()(p);
    }

    /**
     *  Construct from a mean vector and covariance matrix.
     */
    bivariate_gaussian(vector const & mu, matrix const & sigma)
        : _mu(mu), _sigma(sigma), _cholesky(compute_inverse_cholesky(sigma))
    {}
    
private:

    /**
     *  This evaluates the inverse of the Cholesky factorization of a 2x2 matrix;
     *  it's just a shortcut in evaluating the density.
     */
    static matrix compute_inverse_cholesky(matrix const & m) {
        matrix l;
        // First do cholesky factorization: l l^t = m
        l(0, 0) = std::sqrt(m(0, 0));
        l(0, 1) = m(0, 1) / l(0, 0);
        l(1, 1) = std::sqrt(m(1, 1) - l(0,1) * l(0,1));
        // Now do forward-substitution (in-place) to invert:
        l(0, 0) = 1.0 / l(0, 0);
        l(1, 0) = l(0, 1) = -l(0, 1) / l(1, 1);
        l(1, 1) = 1.0 / l(1, 1);
        return l;
    }

    vector _mu;
    matrix _sigma;
    matrix _cholesky;
                        
};

/*
 *  We have a two options for wrapping get_mu and get_sigma into NumPy-returning Python methods:
 *   - we could deep-copy the data, making totally new NumPy arrays;
 *   - we could make NumPy arrays that point into the existing memory.
 *  The latter is often preferable, especially if the arrays are large, but it's dangerous unless
 *  the reference counting is correct: the returned NumPy array needs to hold a reference that
 *  keeps the memory it points to from being deallocated as long as it is alive.  This is what the
 *  "owner" argument to from_data does - the NumPy array holds a reference to the owner, keeping it
 *  from being destroyed.
 *
 *  Note that this mechanism isn't completely safe for data members that can have their internal
 *  storage reallocated.  A std::vector, for instance, can be invalidated when it is resized,
 *  so holding a Python reference to a C++ class that holds a std::vector may not be a guarantee
 *  that the memory in the std::vector will remain valid.
 */

/**
 *  These two functions are custom wrappers for get_mu and get_sigma, providing the shallow-copy
 *  conversion with reference counting described above.
 *
 *  It's also worth noting that these return NumPy arrays that cannot be modified in Python;
 *  the const overloads of vector::data() and matrix::data() return const references, 
 *  and passing a const pointer to from_data causes NumPy's 'writeable' flag to be set to false.
 */
static bn::ndarray py_get_mu(bp::object const & self) {
    bivariate_gaussian::vector const & mu = bp::extract<bivariate_gaussian const &>(self)().get_mu();
    return bn::from_data(
        mu.data(),
        bn::dtype::get_builtin<double>(),
        bp::make_tuple(2),
        bp::make_tuple(sizeof(double)),
        self
    );  
}
static bn::ndarray py_get_sigma(bp::object const & self) {
    bivariate_gaussian::matrix const & sigma = bp::extract<bivariate_gaussian const &>(self)().get_sigma();
    return bn::from_data(
        sigma.data(),
        bn::dtype::get_builtin<double>(),
        bp::make_tuple(2, 2),
        bp::make_tuple(2 * sizeof(double), sizeof(double)),
        self
    );
}

/**
 *  To allow the constructor to work, we need to define some from-Python converters from NumPy arrays
 *  to the ublas types.  The rvalue-from-python functionality is not well-documented in Boost.Python
 *  itself; you can learn more from boost/python/converter/rvalue_from_python_data.hpp.
 */

/**
 *  We start with two functions that just copy a NumPy array into ublas objects.  These will be used
 *  in the templated converted below.  The first just uses the operator[] overloads provided by
 *  bp::object.
 */
static void copy_ndarray_to_ublas(bn::ndarray const & array, bivariate_gaussian::vector & vec) {
    vec[0] = bp::extract<double>(array[0]);
    vec[1] = bp::extract<double>(array[1]);
}
/**
 *  Here, we'll take the alternate approach of using the strides to access the array's memory directly.
 *  This can be much faster for large arrays.
 */
static void copy_ndarray_to_ublas(bn::ndarray const & array, bivariate_gaussian::matrix & mat) {
    // Unfortunately, get_strides() can't be inlined, so it's best to call it once up-front.
    Py_intptr_t const * strides = array.get_strides();
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            mat(i, j) = *reinterpret_cast<double const *>(array.get_data() + i * strides[0] + j * strides[1]);
        }
    }
}

template <typename T, int N>
struct bivariate_gaussian_ublas_from_python {
    
    /**
     *  Register the converter.
     */
    bivariate_gaussian_ublas_from_python() {
        bp::converter::registry::push_back(
            &convertible,
            &construct,
            bp::type_id< T >()
        );
    }

    /**
     *  Test to see if we can convert this to the desired type; if not return zero.
     *  If we can convert, returned pointer can be used by construct().
     */
    static void * convertible(PyObject * p) {
        try {
            bp::object obj(bp::handle<>(bp::borrowed(p)));
            std::auto_ptr<bn::ndarray> array(
                new bn::ndarray(
                    bn::from_object(obj, bn::dtype::get_builtin<double>(), N, N, bn::ndarray::V_CONTIGUOUS)
                )
            );
            if (array->shape(0) != 2) return 0;
            if (N == 2 && array->shape(1) != 2) return 0;
            return array.release();
        } catch (bp::error_already_set & err) {
            bp::handle_exception();
            return 0;
        }
    }

    /**
     *  Finish the conversion by initializing the C++ object into memory prepared by Boost.Python.
     */
    static void construct(PyObject * obj, bp::converter::rvalue_from_python_stage1_data * data) {
        // Extract the array we passed out of the convertible() member function.
        std::auto_ptr<bn::ndarray> array(reinterpret_cast<bn::ndarray*>(data->convertible));
        // Find the memory block Boost.Python has prepared for the result.
        typedef bp::converter::rvalue_from_python_storage<T> storage_t;
        storage_t * storage = reinterpret_cast<storage_t*>(data);
        // Use placement new to initialize the result.
        T * ublas_obj = new (storage->storage.bytes) T();
        // Fill the result with the values from the NumPy array.
        copy_ndarray_to_ublas(*array, *ublas_obj);
        // Finish up.
        data->convertible = storage->storage.bytes;
    }

};


BOOST_PYTHON_MODULE(gaussian) {
    bn::initialize();

    // Register the from-python converters
    bivariate_gaussian_ublas_from_python< bivariate_gaussian::vector, 1 >();
    bivariate_gaussian_ublas_from_python< bivariate_gaussian::matrix, 2 >();

    typedef double (bivariate_gaussian::*call_vector)(bivariate_gaussian::vector const &) const;

    bp::class_<bivariate_gaussian>("bivariate_gaussian", bp::init<bivariate_gaussian const &>())

        // Declare the constructor (wouldn't work without the from-python converters).
        .def(bp::init< bivariate_gaussian::vector const &, bivariate_gaussian::matrix const & >())

        // Use our custom reference-counting getters
        .add_property("mu", &py_get_mu)
        .add_property("sigma", &py_get_sigma)

        // First overload accepts a two-element array argument
        .def("__call__", (call_vector)&bivariate_gaussian::operator())

        // This overload works like a binary NumPy universal function: you can pass
        // in scalars or arrays, and the C++ function will automatically be called
        // on each element of an array argument.
        .def("__call__", bn::binary_ufunc<bivariate_gaussian,double,double,double>::make())
        ;
}
