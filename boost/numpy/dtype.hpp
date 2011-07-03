#ifndef BOOST_NUMPY_DTYPE_HPP_INCLUDED
#define BOOST_NUMPY_DTYPE_HPP_INCLUDED

/**
 *  @file boost/numpy/dtype.hpp
 *  @brief Object manager for Python's numpy.dtype class.
 */

#include <boost/python.hpp>
#include <boost/numpy/numpy_object_mgr_traits.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/type_traits/add_pointer.hpp>

namespace boost 
{
namespace numpy 
{

/**
 *  @brief A boost.python "object manager" (subclass of object) for numpy.dtype.
 *
 *  @todo This could have a lot more interesting accessors.
 */
class dtype : public python::object 
{
  static python::detail::new_reference convert(python::object::object_cref arg, bool align);
public:

  /// @brief Convert an arbitrary Python object to a data-type descriptor object.
  template <typename T>
  explicit dtype(T arg, bool align=false) : python::object(convert(arg, align)) {}

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

  BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(dtype, python::object);

};

} // namespace boost::numpy

namespace python 
{
namespace converter 
{
NUMPY_OBJECT_MANAGER_TRAITS(numpy::dtype);
} // namespace boost::python::converter
} // namespace boost::python
} // namespace boost

#endif // !BOOST_NUMPY_DTYPE_HPP_INCLUDED
