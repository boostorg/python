// Example by Ralf W. Grosse-Kunstleve

#include <iostream>
#include <string>

namespace { // Avoid cluttering the global namespace.

  // A friendly class.
  class hello
  {
    public:
      hello(const std::string& country) { this->country = country; }
      std::string greet() const { return "Hello from " + country; }
    private:
      std::string country;
  };

  // A function taking a hello object as an argument.
  std::string invite(const hello& w) {
    return w.greet() + "! Please come soon!";
  }
}

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

BOOST_PYTHON_MODULE_INIT(getting_started2)
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("getting_started2");

    // Create the Python type object for our extension class.
    python::class_builder<hello> hello_class(this_module, "hello");

    // Add the __init__ function.
    hello_class.def(python::constructor<std::string>());
    // Add a regular member function.
    hello_class.def(&hello::greet, "greet");

    // Add invite() as a regular function to the module.
    this_module.def(invite, "invite");

    // Even better, invite() can also be made a member of hello_class!!!
    hello_class.def(invite, "invite");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
