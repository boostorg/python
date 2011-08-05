/**
 *  @brief An example to show how to create ndarrays with built-in python data types, and extract the types and values 
 *          of member variables
 *
 *  @todo Add an example to show type conversion.
 *        Add an example to show use of user-defined types
 *        
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
  // Roundabout way of creating a user defined dtype. Fix this if possible
/*
  p::tuple for_custom_dtype = p::make_tuple("ha",dtype) ;
  p::list list_for_dtype ;
  list_for_dtype.append(for_custom_dtype) ;
  np::dtype custom_dtype = np::dtype(list_for_dtype) ;
  np::ndarray new_array = np::zeros(shape,z);
*/
}
