// Example by Ralf W. Grosse-Kunstleve & Nicholas K. Sauter
// This example shows how to use rich comparisons for a vector type.
// It also shows how to template the entire wrapping of a std::vector.
// See vector_wrapper.h.

#include <boost/python/class_builder.hpp>
#include "vector_wrapper.h"

namespace std {

# define VECTOR_BINARY_OPERATORS(oper) \
  template <class T> \
  std::vector<bool> \
  operator##oper(const std::vector<T>& a, const std::vector<T>& b) \
  { \
    if (a.size()!=b.size()){throw boost::python::argument_error();} \
    std::vector<bool> result(a.size()); \
    for (std::size_t i=0; i<a.size(); i++) { \
      result[i] = (a[i] ##oper b[i]); \
    } \
    return result; \
  }
  VECTOR_BINARY_OPERATORS(<)
  VECTOR_BINARY_OPERATORS(<=)
  VECTOR_BINARY_OPERATORS(==)
  VECTOR_BINARY_OPERATORS(!=)
  VECTOR_BINARY_OPERATORS(>)
  VECTOR_BINARY_OPERATORS(>=)
# undef VECTOR_BINARY_OPERATORS

}

namespace {

  void init_module(boost::python::module_builder& this_module)
  {
    (void)
    example::wrap_vector(this_module, "vector_of_bool", bool());

    boost::python::class_builder<
    std::vector<double>, example::vector_wrapper<double> >
    py_vector_of_double =
    example::wrap_vector(this_module, "vector_of_double", double());

    const long comp_operators =
      (  boost::python::op_lt | boost::python::op_le
       | boost::python::op_eq | boost::python::op_ne
       | boost::python::op_gt | boost::python::op_ge);
    py_vector_of_double.def(boost::python::operators<comp_operators>());
  }

} // namespace <anonymous>

BOOST_PYTHON_MODULE_INIT(richcmp1)
{
  try {
    boost::python::module_builder this_module("richcmp1");
    // The actual work is done in separate function in order
    // to suppress a bogus VC60 warning.
    init_module(this_module);
  }
  catch(...){boost::python::handle_exception();}
}
