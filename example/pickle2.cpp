/*
    This example shows how to make an Extension Class "pickleable".

    The world class below contains member data (secret_number) that
    cannot be restored by any of the constructors. Therefore it is
    necessary to provide the __getstate__/__setstate__ pair of pickle
    interface methods.

    For simplicity, the __dict__ is not included in the result of
    __getstate__. This is not generally recommended, but a valid
    approach if it is anticipated that the object's __dict__ will
    always be empty. Note that safety guard are provided to catch the
    cases where this assumption is not true.

    pickle3.cpp shows how to include the object's __dict__ in the
    result of __getstate__.

    For more information refer to boost/libs/python/doc/pickle.html.
 */

#include <string>

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

namespace { // Avoid cluttering the global namespace.

  // A friendly class.
  class world
  {
    public:
      world(const std::string& country) : secret_number(0) {
        this->country = country;
      }
      std::string greet() const { return "Hello from " + country + "!"; }
      std::string get_country() const { return country; }
      void set_secret_number(int number) { secret_number = number; }
      int get_secret_number() const { return secret_number; }
    private:
      std::string country;
      int secret_number;
  };

  // Support for pickle.
  python::ref world_getinitargs(const world& w) {
      python::tuple result(1);
      result.set_item(0, w.get_country());
      return result.reference(); // returning the reference avoids the copying.
  }

  python::ref world_getstate(const world& w) {
      python::tuple result(1);
      result.set_item(0, w.get_secret_number());
      return result.reference(); // returning the reference avoids the copying.
  }

  void world_setstate(world& w, python::tuple state) {
    if (state.size() != 1) {
      PyErr_SetString(PyExc_ValueError,
        "Unexpected argument in call to __setstate__.");
      throw python::error_already_set();
    }
    int number = state[0].get<int>();
    if (number != 42)
      w.set_secret_number(number);
  }
}

BOOST_PYTHON_MODULE_INIT(pickle2)
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("pickle2");

    // Create the Python type object for our extension class.
    python::class_builder<world> world_class(this_module, "world");

    // Add the __init__ function.
    world_class.def(python::constructor<std::string>());
    // Add a regular member function.
    world_class.def(&world::greet, "greet");
    world_class.def(&world::get_secret_number, "get_secret_number");
    world_class.def(&world::set_secret_number, "set_secret_number");

    // Support for pickle.
    world_class.def(world_getinitargs, "__getinitargs__");
    world_class.def(world_getstate, "__getstate__");
    world_class.def(world_setstate, "__setstate__");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
