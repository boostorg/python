/**
 *  @brief An example to show how to create ndarrays from C++ containers of (almost) arbitrary type.
 *
 */

#include <boost/numpy.hpp>
#include <vector>
#include <iostream>

namespace p = boost::python;
namespace np = boost::numpy;


int main(int argc, char **argv)
{
  // Initialize the Python runtime.
  Py_Initialize();
  // Initialize NumPy
  np::initialize();
  // Create an array in C++
  int arr[] = {1,2,3,4} ; 
  // Create the ndarray in Python
  np::ndarray py_array = np::from_data(arr, np::dtype::get_builtin<int>() , p::make_tuple(4), p::make_tuple(4), p::object());
  // Print the ndarray that we created, just to be sure
  std::cout << "C++ array :" << std::endl ;
  for (int j=0;j<4;j++)
  {
    std::cout << arr[j] << ' ' ;
  }
  std::cout << std::endl << "Python ndarray :" << p::extract<char const *>(p::str(py_array)) << std::endl;
  // Change an element in the python ndarray
  py_array[1] = 5 ; 
  // And see if the C++ container is changed or not
  std::cout << "Is the change reflected in the C++ array used to create the ndarray ? " << std::endl ; 
  for (int j = 0;j<4 ; j++)
  {
    std::cout << arr[j] << ' ' ;
  }
  // Conversely, change it in C++
  arr[2] = 8 ;
  // And see if the changes are reflected in the Python ndarray
  std::cout << std::endl << "Is the change reflected in the Python ndarray ?" << std::endl << p::extract<char const *>(p::str(py_array)) << std::endl;

  // Now print it.
//  std::cout << "Pixel array :" << p::extract<char const *>(p::str(py_array)) << std::endl;
}
