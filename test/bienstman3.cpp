#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/mpl/type_list.hpp>

struct V 
{
 virtual void f() = 0;
};

struct B 
{
    B(const V&) {}    
};

BOOST_PYTHON_MODULE_INIT(bienstman3_ext)
{
  using namespace boost::python;
  using boost::mpl::type_list;

  module m("bienstman3_ext");
  
  m

    .add(
      class_<V, boost::noncopyable>("V")
      )

    .add(
      class_<B>("B")
      .def_init(type_list<const V&>())
      )
    ;
}
