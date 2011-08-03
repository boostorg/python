/**
 *  @brief An example to show how to create ndarrays with built-in python data types, and extract the types and values 
 *          of member variables
 *
 *  @todo Add an example to show type conversion.
 *        Add an example to show use of user-defined types
 *        Doesn't work for char. Works for int, long int, short int, float, double
 */

#include <boost/numpy.hpp>
#include <iostream>

namespace p = boost::python;
namespace np = boost::numpy;

int main(int argc, char **argv)
{
  // Initialize the Python runtime.
  Py_Initialize();
  // Initialize NumPy
  np::initialize();
  // Create a 3x3 shape...
  p::tuple shape = p::make_tuple(3, 3);
  // ...as well as a type for C++ double
  np::dtype dtype = np::dtype::get_builtin<double>();
  // Construct an array with the above shape and type
  np::ndarray a = np::zeros(shape, dtype);
  // Print the array
  std::cout << "Original array:\n" << p::extract<char const *>(p::str(a)) << std::endl;
  // Print the datatype of the elements
  std::cout << "Datatype is:\n" << p::extract<char const *>(p::str(a.get_dtype())) << std::endl ;

}
