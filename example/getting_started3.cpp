/*
    This example shows how to make an Extension Class "pickleable".

    Python's pickle module implements a basic but powerful algorithm
    for "pickling" (a.k.a. serializing, marshalling or flattening)
    nearly arbitrary Python objects.

    The user can influence how an Extension Class instance is pickled
    by defining three special methods: __getinitargs__(),
    __getstate__(), and __setstate(). This interface is similar to
    that for regular Python classes as described in detail in the
    Python Library Reference for pickle:

    http://www.python.org/doc/current/lib/module-pickle.html

    When an Extension Class instance is pickled, __getinitargs__() is
    called, if implemented. This method should return a tuple
    containing the arguments to be passed to the class constructor when
    the object is restored.

    If there is no __getstate__() method, the instance's __dict__ is
    pickled if it is not empty. If __getstate__() is defined, it should
    return an object representing the state of the instance.

    If there is no __setstate__() method, __getstate__() must return a
    dictionary. When the instance is restored, the items in this dictionary
    are added to the instance's __dict__.

    If the Extension Class defines __setstate__(), the pickle loader
    calls it with the result of __getstate__() as arguments. In this
    case, the state object need not be a dictionary.  The
    __getstate__() and __setstate__() methods can do what they want.

    If both __getinitargs__() and __getstate__() are defined, the
    instance is restored by first calling the constructor with
    the result of __getinitargs__() as argument. After the instance
    is reconstructed, the __dict__ is updated or __setstate__() is
    called if implemented.

    The mechanism described here is an exact replication of that one
    implemented by Jim Fulton's ExtensionClass (included in Zope 2.2.2).
 */

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
      int secret_number;
    public:
      world(const std::string& country) : secret_number(0) {
        this->country = country;
      }
      std::string greet() const { return "Hello from " + country + "!"; }
      std::string get_country() const { return country; }
      void set_secret_number(int number) { secret_number = number; }
      int get_secret_number() const { return secret_number; }
  };

  // Support for pickle.
  python::tuple world_getinitargs(const world& w) {
      python::tuple result(1);
      result.set_item(0, w.get_country());
      return result;
  }

  python::tuple world_getstate(const world& w) {
      python::tuple result(1);
      result.set_item(0, w.get_secret_number());
      return result;
  }

  void world_setstate(world& w, python::tuple state) {
    if (state.size() != 1) {
      PyErr_SetString(PyExc_ValueError,
        "Unexpected argument in call to __setstate__.");
      throw python::error_already_set();
    }
    int number = BOOST_PYTHON_CONVERSION::from_python(state[0].get(),
      python::type<int>());
    if (number != 42)
      w.set_secret_number(number);
  }

  template <class T>
  class a_number {
    private:
      T m_number;
    public:
      a_number() : m_number(0) {}
      a_number(T number) : m_number(number) {}
      const T get() const { return m_number; }
  };
}

extern "C"
DL_EXPORT(void)
initgetting_started3()
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("getting_started3");

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

    // This Python class has no pickle support.
    python::class_builder<a_number<int> >
    py_a_lame_number(this_module, "a_lame_number");
    py_a_lame_number.def(python::constructor<>());
    py_a_lame_number.def(python::constructor<int>());
    py_a_lame_number.def(&a_number<int>::get, "get");

    // Enable pickling of the object's __dict__.
    python::class_builder<a_number<double> >
    py_a_number(this_module, "a_number");
    py_a_number.dict_defines_state();
    py_a_number.def(python::constructor<>());
    py_a_number.def(python::constructor<double>());
    py_a_number.def(&a_number<double>::get, "get");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
