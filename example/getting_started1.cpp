// Example by Ralf W. Grosse-Kunstleve

#include <string>

namespace { // Avoid cluttering the global namespace.

  // A couple of simple C++ functions that we want to expose to Python.
  std::string greet() { return "hello, world"; }
  int square(int number) { return number * number; }
}

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

// Python requires an exported function called init<module-name> in every
// extension module. This is where we build the module contents.
BOOST_PYTHON_MODULE_INIT(getting_started1)
{
    // Create an object representing this extension module.
    python::module_builder this_module("getting_started1");

    // Add regular functions to the module.
    this_module.def(greet, "greet");
    this_module.def(square, "square");
}
