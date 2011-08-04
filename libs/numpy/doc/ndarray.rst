Creating ndarrays
=================

The Boost.Numpy library exposes quite a few methods to create ndarrays. ndarrays can be created in a variety of ways, include empty arrays and zero filled arrays.
ndarrays can also be created from arbitrary python sequences as well as from data and dtypes. 

This tutorial will introduce you to some of the ways in which you can create ndarrays.

First, as before, initialise the necessary namepaces and runtimes ::

	#include <boost/numpy.hpp>
	#include <iostream>

	namespace p = boost::python;
	namespace np = boost::numpy;

	int main(int argc, char **argv)
	{
	  Py_Initialize();
	  np::initialize();

Let's now create an ndarray from a simple tuple. We first create a tuple object, and then pass it to the array method, to generate the necessary tuple ::

  p::object tu = p::make_tuple('a','b','c') ;
  np::ndarray example_tuple = np::array(tu) ; 

Let's now try the same with a list. We create an empty list, add an element using the append method, and as before, call the array method ::

  p::list l ;
  l.append('a') ;
  np::ndarray example_list = np::array (l) ;

Optionally, we can also specify a dtype for the array ::

  np::dtype dt = np::dtype::get_builtin<int>();
  np::ndarray example_list1 = np::array (l,dt);

We can also create an array by supplying data arrays and a few other parameters.

First,create an integer array ::

  int data[] = {1,2,3,4} ;

Create a shape, and strides, needed by the function ::

  p::tuple shape = p::make_tuple(2,2) ;
  p::tuple strides = p::make_tuple(strides(data)) ; 

The function also needs an owner, to keep track of the data array passed. Passing none is dangerous ::

  p::object owner ;

The from_data function takes the data array, datatype,shape,stride and owner as arguments and returns an ndarray ::

  np::ndarray data_ex1 = np::from_data(data,dt, shape,strides,owner);

}



