// Example by Ralf W. Grosse-Kunstleve & Nicholas K. Sauter
// This example shows how to use rich comparisons for a vector type.
// It also shows how to template the entire wrapping of a std::vector.
// See vector_wrapper.h.

#include <boost/python/class_builder.hpp>
#include "vector_wrapper.h"

namespace vects {

  struct dvect : public std::vector<double>
  {
    dvect() : std::vector<double>() {}
    dvect(size_t n) : std::vector<double>(n) {}
    dvect(boost::python::tuple tuple) : std::vector<double>(tuple.size())
    {
      std::vector<double>::iterator v_it = begin();
      for (std::size_t i = 0; i < tuple.size(); i++)
        v_it[i] = BOOST_PYTHON_CONVERSION::from_python(tuple[i].get(),
          boost::python::type<double>());
    }

    boost::python::tuple as_tuple() const
    {
      boost::python::tuple t(size());
      for (std::size_t i = 0; i < size(); i++)
        t.set_item(i,
          boost::python::ref(BOOST_PYTHON_CONVERSION::to_python((*this)[i])));
      return t;
    }

#   define DVECT_BINARY_OPERATORS(oper) \
    friend std::vector<bool> \
    operator##oper(const dvect& lhs, const dvect& rhs) \
    { \
      if (lhs.size() != rhs.size()) { \
        PyErr_SetString(PyExc_ValueError, "vectors have different sizes"); \
        throw boost::python::error_already_set(); \
      } \
      std::vector<bool> result(lhs.size()); \
      for (std::size_t i=0; i<lhs.size(); i++) { \
        result[i] = (lhs[i] ##oper rhs[i]); \
      } \
      return result; \
    }
    DVECT_BINARY_OPERATORS(<)
    DVECT_BINARY_OPERATORS(<=)
    DVECT_BINARY_OPERATORS(==)
    DVECT_BINARY_OPERATORS(!=)
    DVECT_BINARY_OPERATORS(>)
    DVECT_BINARY_OPERATORS(>=)
#   undef VECTOR_BINARY_OPERATORS
  };

} // namespace <anonymous>


namespace {

  void init_module(boost::python::module_builder& this_module)
  {
    (void) example::wrap_vector(this_module, "vector_of_bool", bool());

    boost::python::class_builder<vects::dvect> py_dvect(this_module, "dvect");

    py_dvect.def(boost::python::constructor<boost::python::tuple>());
    py_dvect.def(&vects::dvect::as_tuple, "as_tuple");

    const long
    comp_operators = (  boost::python::op_lt | boost::python::op_le
                      | boost::python::op_eq | boost::python::op_ne
                      | boost::python::op_gt | boost::python::op_ge);
    py_dvect.def(boost::python::operators<comp_operators>());
  }

} // namespace <anonymous>

BOOST_PYTHON_MODULE_INIT(richcmp1)
{
    boost::python::module_builder this_module("richcmp1");
    // The actual work is done in a separate function in order
    // to suppress a bogus VC60 warning.
    init_module(this_module);
}
