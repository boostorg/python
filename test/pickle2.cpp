// Example by Ralf W. Grosse-Kunstleve

/*
    This example shows how to make an Extension Class "pickleable".

    The world class below contains member data (secret_number) that
    cannot be restored by any of the constructors. Therefore it is
    necessary to provide the __getstate__/__setstate__ pair of pickle
    interface methods.

    For simplicity, the __dict__ is not included in the result of
    __getstate__. This is not generally recommended, but a valid
    approach if it is anticipated that the object's __dict__ will
    always be empty. Note that safety guards are provided to catch
    the cases where this assumption is not true.

    pickle3.cpp shows how to include the object's __dict__ in the
    result of __getstate__.

    For more information refer to boost/libs/python/doc/pickle.html.
 */

#include <string>

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
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

  struct world_pickle_suite : boost::python::pickle_suite
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
    getstate(const world& w)
    {
        using namespace boost::python;
        list result;
        result.append(object(w.get_secret_number()));
        return tuple(result);
    }

    static
    void
    setstate(world& w, boost::python::object state)
    {
        using namespace boost::python;
        extract<tuple> state_proxy(state);
        if (!state_proxy.check() || len(state_proxy()) != 1) {
          PyErr_SetString(PyExc_ValueError,
            "Unexpected argument in call to __setstate__.");
          throw_error_already_set();
        }
        long number = extract<long>(state_proxy()[0])();
        if (number != 42) w.set_secret_number(number);
    }
  };

}

BOOST_PYTHON_MODULE_INIT(pickle2_ext)
{
    boost::python::class_<world>(
        "world", boost::python::args<const std::string&>())
        .def("greet", &world::greet)
        .def("get_secret_number", &world::get_secret_number)
        .def("set_secret_number", &world::set_secret_number)
        .def_pickle(world_pickle_suite())
        ;
}
