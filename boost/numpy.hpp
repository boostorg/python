#ifndef BOOST_NUMPY_HPP_INCLUDED
#define BOOST_NUMPY_HPP_INCLUDED

/**
 *  @file boost/numpy.hpp
 *  @brief Main public header file for boost.numpy.
 */

#include <boost/numpy/dtype.hpp>
#include <boost/numpy/ndarray.hpp>
#include <boost/numpy/scalars.hpp>
#include <boost/numpy/matrix.hpp>
#include <boost/numpy/ufunc.hpp>
#include <boost/numpy/invoke_matching.hpp>

namespace boost {
namespace numpy {

/**
 *  @brief Initialize the Numpy C-API
 *
 *  This must be called before using anything in boost.numpy;
 *  It should probably be the first line inside BOOST_PYTHON_MODULE.
 *
 *  @internal This just calls the Numpy C-API functions "import_array()"
 *            and "import_ufunc()".
 */
void initialize();

} // namespace boost::numpy
} // namespace boost

#endif // !BOOST_NUMPY_HPP_INCLUDED
