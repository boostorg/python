// Example by Ralf W. Grosse-Kunstleve

/*
    This example shows how to make an Extension Class "pickleable".

    The world class below can be fully restored by passing the
    appropriate argument to the constructor. Therefore it is sufficient
    to define the pickle interface method __getinitargs__.

    For more information refer to boost/libs/python/doc/pickle.html.
 */

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>

#include <string>

namespace {

  // A friendly class.
  class world
  {
    private:
      std::string country;
    public:
      world(const std::string& country) {
        this->country = country;
      }
      std::string greet() const { return "Hello from " + country + "!"; }
      std::string get_country() const { return country; }
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
  };

}

BOOST_PYTHON_MODULE_INIT(pickle1_ext)
{
  using namespace boost::python;
  module("pickle1_ext")
    .add(class_<world>("world")
      .def_init(args<const std::string&>())
      .def("greet", &world::greet)
      .def_pickle(world_pickle_group())
    )
  ;
}
