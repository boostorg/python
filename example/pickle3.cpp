// Example by Ralf W. Grosse-Kunstleve

/*
    This example shows how to make an Extension Class "pickleable".

    The world class below contains member data (secret_number) that
    cannot be restored by any of the constructors. Therefore it is
    necessary to provide the __getstate__/__setstate__ pair of pickle
    interface methods.

    The object's __dict__ is included in the result of __getstate__.
    This requires more code (compare with pickle2.cpp), but is
    unavoidable if the object's __dict__ is not always empty.

    For more information refer to boost/libs/python/doc/pickle.html.
 */

#include <string>

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

namespace boost { namespace python {

  ref getattr(PyObject* o, const std::string& attr_name) {
    return ref(PyObject_GetAttrString(o, const_cast<char*>(attr_name.c_str())));
  }
  ref getattr(const ref& r, const std::string& attr_name) {
    return getattr(r.get(), attr_name);
  }

}}

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

  python::ref world_getstate(python::tuple const & args,
                             python::dictionary const & keywords);

  PyObject* world_setstate(python::tuple const & args,
                           python::dictionary const & keywords);
}

BOOST_PYTHON_MODULE_INIT(pickle3)
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("pickle3");

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
    world_class.def_raw(world_getstate, "__getstate__");
    world_class.def_raw(world_setstate, "__setstate__");
    world_class.getstate_manages_dict();
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}

namespace {

  using boost::python::type;
  using boost::python::ref;
  using boost::python::tuple;
  using boost::python::list;
  using boost::python::dictionary;
  using boost::python::getattr;

  ref world_getstate(tuple const & args, dictionary const & keywords)
  {
      if(args.size() != 1 || keywords.size() != 0) {
          PyErr_SetString(PyExc_TypeError, "wrong number of arguments");
          throw boost::python::argument_error();
      }
      const world& w = from_python(args[0].get(), type<const world&>());
      ref mydict = getattr(args[0], "__dict__");
      tuple result(2);
      // store the object's __dict__
      result.set_item(0, mydict);
      // store the internal state of the C++ object
      result.set_item(1, w.get_secret_number());
      return result.reference(); // returning the reference avoids the copying.
  }

  PyObject* world_setstate(tuple const & args, dictionary const & keywords)
  {
      if(args.size() != 2 || keywords.size() != 0) {
          PyErr_SetString(PyExc_TypeError, "wrong number of arguments");
          throw boost::python::argument_error();
      }
      world& w = from_python(args[0].get(), type<world&>());
      ref mydict = getattr(args[0], "__dict__");
      tuple state = from_python(args[1].get(), type<tuple>());
      if (state.size() != 2) {
        PyErr_SetString(PyExc_ValueError,
          "Unexpected argument in call to __setstate__.");
        throw python::error_already_set();
      }
      // restore the object's __dict__
      dictionary odict = from_python(mydict.get(), type<dictionary>());
      const dictionary& pdict = from_python(state[0].get(), type<const dictionary&>());
      list pkeys(pdict.keys());
      for (int i = 0; i < pkeys.size(); i++) {
        ref k(pkeys[i]);
        //odict[k] = pdict[k]; // XXX memory leak!
        odict[k] = pdict.get_item(k); // this does not leak.
      }
      // restore the internal state of the C++ object
      int number = from_python(state[1].get(), type<int>());
      if (number != 42)
        w.set_secret_number(number);
      return python::detail::none();
  }
}
