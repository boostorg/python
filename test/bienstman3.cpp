#include <boost/python/module.hpp>
#include <boost/python/class.hpp>

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

  module m("bienstman3_ext");
  
  m
    .add(
      class_<V, boost::noncopyable>("V", no_init)
      )

    .add(
      class_<B>("B", args<const V&>())
      )
    ;
}
