#ifndef BOOST_PYTHON_NUMPY_DTYPE_HPP_INCLUDED
#define BOOST_PYTHON_NUMPY_DTYPE_HPP_INCLUDED

/**
 *  @file boost/python/numpy/dtype.hpp
 *  @brief Object manager for Python's numpy.dtype class.
 */

#include <boost/python.hpp>
#include <boost/python/numpy/numpy_object_mgr_traits.hpp>

namespace boost { namespace python {
namespace numpy {

/**
 *  @brief A boost.python "object manager" (subclass of object) for numpy.dtype.
 *
 *  @todo This could have a lot more interesting accessors.
 */
class dtype : public object {
    static python::detail::new_reference convert(object_cref arg, bool align);
public:

    /// @brief Convert an arbitrary Python object to a data-type descriptor object.
    template <typename T>
    explicit dtype(T arg, bool align=false) : object(convert(arg, align)) {}

    /**
     *  @brief Get the built-in numpy dtype associated with the given scalar template type.
     *
     *  This is perhaps the most useful part of the numpy API: it returns the dtype object
     *  corresponding to a built-in C++ type.  This should work for any integer or floating point
     *  type supported by numpy, and will also work for std::complex if 
     *  sizeof(std::complex<T>) == 2*sizeof(T).
     *
     *  It can also be useful for users to add explicit specializations for POD structs
     *  that return field-based dtypes.
     */
    template <typename T> static dtype get_builtin();

    /// @brief Return the size of the data type in bytes.
    int get_itemsize() const;

    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(dtype, object);

};

} // namespace boost::python::numpy

namespace converter {
NUMPY_OBJECT_MANAGER_TRAITS(python::numpy::dtype);
} // namespace boost::python::converter

}} // namespace boost::python

#endif // !BOOST_PYTHON_NUMPY_DTYPE_HPP_INCLUDED
