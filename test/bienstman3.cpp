#include <boost/python/module_init.hpp>
#include <boost/python/def.hpp>
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

  class_<V, boost::noncopyable>("V", no_init);
  class_<B>("B", args<const V&>());

}
