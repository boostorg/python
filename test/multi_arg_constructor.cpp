#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>

struct A
{
    A(const double, const double, const double, const double, const double
      , const double, const double
      , const double, const double
        ) {}
};

BOOST_PYTHON_MODULE(multi_arg_constructor_ext)
{
  using namespace boost::python;
  using boost::shared_ptr;

  class_<A, shared_ptr<A> >(
      "A"
      , init<double, double, double, double, double, double, double, double, double>()
      )
      ;

}

