#include <iostream>
#include <string>
#include <boost/python/class_builder.hpp>
namespace python = boost::python;

namespace { // Avoid cluttering the global namespace.

  // A friendly class.
  class world
  {
    private:
      std::string country;
    public:
      world(const std::string& country) { this->country = country; }
      std::string greet() const { return "Hello from " + country + "!"; }
  };

  // A function taking a world object as an argument.
  std::string invite(const world& w) {
    return w.greet() + " Please come soon!";
  }
}

extern "C"
DL_EXPORT(void)
initgetting_started2()
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("getting_started2");

    // Create the Python type object for our extension class.
    python::class_builder<world> world_class(this_module, "world");

    // Add the __init__ function.
    world_class.def(python::constructor<std::string>());
    // Add a regular member function.
    world_class.def(&world::greet, "greet");

    // Add invite() as a regular function to the module.
    this_module.def(invite, "invite");

    // Even better, invite() can also be made a member of world_class!!!
    world_class.def(invite, "invite");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
