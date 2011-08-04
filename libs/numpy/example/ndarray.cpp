/**
 *  @brief An example to show how to create ndarrays using arbitrary Python sequences
 *         The Python sequence could be any object whose __array__ method returns an array, or any (nested) sequence.
 *
 *  @todo Find a way to create a list explicitly
 *	  

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
  // Create an ndarray from a simple tuple
  p::object tu = p::make_tuple('a','b','c') ;
  np::ndarray example_tuple = np::array (tu) ; 
  // and from a list
  p::list l ;
  np::ndarray example_list = np::array (l) ; 
  // Optionally, you can also specify a dtype
  np::dtype dt = np::dtype::get_builtin<int>();
  np::ndarray example_list1 = np::array (l,dt);
  // You can also create an array by supplying data.First,create an integer array
  int data[] = {1,2,3,4} ;
  // Create a shape, and strides, needed by the function
  p::tuple shape = p::make_tuple(2,2) ;
  p::tuple strides = p::make_tuple(strides(data)) ; 
  // The function also needs an owner, to keep track of the data array passed. Passing none is dangerous
  p::object owner ;
  // The from_data function takes the data array, datatype,shape,stride and owner as arguments
  // and returns an ndarray
  np::ndarray data_ex1 = np::from_data(data,dt, shape,strides,owner);

}


