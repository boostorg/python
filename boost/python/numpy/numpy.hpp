#ifndef BOOST_PYTHON_NUMPY_HPP_INCLUDED
#define BOOST_PYTHON_NUMPY_HPP_INCLUDED

/**
 *  @file boost/python/numpy.hpp
 *  @brief Main public header file for boost.python.numpy.
 */

#include <boost/python/numpy/dtype.hpp>
#include <boost/python/numpy/ndarray.hpp>
#include <boost/python/numpy/scalars.hpp>
#include <boost/python/numpy/matrix.hpp>
#include <boost/python/numpy/ufunc.hpp>

namespace boost { namespace python {
namespace numpy {

/**
 *  @brief Initialize the Numpy C-API
 *
 *  This must be called before using anything in boost.python.numpy;
 *  It should probably be the first line inside BOOST_PYTHON_MODULE.
 *
 *  @internal This just calls the Numpy C-API functions "import_array()"
 *            and "import_ufunc()".
 */
void initialize();

} // namespace boost::python::numpy
}} // namespace boost::python

#endif // !BOOST_PYTHON_NUMPY_HPP_INCLUDED
