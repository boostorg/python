/*
    This example shows how to make an Extension Class "pickleable".

    The world class below can be fully restored by passing the
    appropriate argument to the constructor. Therefore it is sufficient
    to define the pickle interface method __getinitargs__.

    For more information refer to boost/libs/python/doc/pickle.html.
 */

#include <string>

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

namespace { // Avoid cluttering the global namespace.

  // A friendly class.
  class world
  {
    private:
      std::string country;
      int secret_number;
    public:
      world(const std::string& country) : secret_number(0) {
        this->country = country;
      }
      std::string greet() const { return "Hello from " + country + "!"; }
      std::string get_country() const { return country; }
  };

  // Support for pickle.
  python::ref world_getinitargs(const world& w) {
      python::tuple result(1);
      result.set_item(0, w.get_country());
      return result.reference();
  }
}

BOOST_PYTHON_MODULE_INIT(pickle1)
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("pickle1");

    // Create the Python type object for our extension class.
    python::class_builder<world> world_class(this_module, "world");

    // Add the __init__ function.
    world_class.def(python::constructor<std::string>());
    // Add a regular member function.
    world_class.def(&world::greet, "greet");

    // Support for pickle.
    world_class.def(world_getinitargs, "__getinitargs__");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
