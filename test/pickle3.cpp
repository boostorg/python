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

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/detail/api_placeholder.hpp>

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

  struct world_pickle_group : boost::python::pickle_group
  {
    static
    boost::python::tuple
    getinitargs(const world& w)
    {
        using namespace boost::python;
        list result;
        result.append(object(w.get_country()));
        return tuple(result);
    }

    static
    boost::python::tuple
    getstate(boost::python::object w_obj)
    {
        using namespace boost::python;
        world const& w = extract<world const&>(w_obj)();
        list result;
        // store the object's __dict__
        result.append(w_obj.attr("__dict__"));
        // store the internal state of the C++ object
        result.append(object(w.get_secret_number()));
        return tuple(result);
    }

    static
    void
    setstate(boost::python::object w_obj, boost::python::object state)
    {
        using namespace boost::python;
        world& w = extract<world&>(w_obj)();
        extract<tuple> state_proxy(state);
        if (!state_proxy.check() || len(state_proxy()) != 2) {
          PyErr_SetString(PyExc_ValueError,
            "Unexpected argument in call to __setstate__.");
          throw_error_already_set();
        }
        // restore the object's __dict__
        w_obj.attr("__dict__").attr("update")(object(state_proxy()[0]));
        // restore the internal state of the C++ object
        long number = extract<long>(state_proxy()[1])();
        if (number != 42) w.set_secret_number(number);
    }

    static bool getstate_manages_dict() { return true; }
  };

}

BOOST_PYTHON_MODULE_INIT(pickle3_ext)
{
  boost::python::module("pickle3_ext")
    .add(boost::python::class_<world>("world")
      .def_init(boost::python::args<const std::string&>())
      .def("greet", &world::greet)
      .def("get_secret_number", &world::get_secret_number)
      .def("set_secret_number", &world::set_secret_number)
      .def_pickle(world_pickle_group())
    )
  ;
}
