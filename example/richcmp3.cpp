// Example by Ralf W. Grosse-Kunstleve & Nicholas K. Sauter.
// Comprehensive operator overloading for two vector types and scalars.

#include <boost/python/class_builder.hpp>
#include "vector_wrapper.h"
#include "dvect.h"
#include "ivect.h"

#define VECT_VECT_OPERATORS(result_type, vect_type1, oper, vect_type2) \
namespace vects { \
  result_type \
  operator##oper (const vect_type1& lhs, const vect_type2& rhs) { \
    if (lhs.size() != rhs.size()) { \
      PyErr_SetString(PyExc_ValueError, "vectors have different sizes"); \
      boost::python::throw_error_already_set(); \
    } \
    result_type result(lhs.size()); \
    for (std::size_t i=0; i<lhs.size(); i++) { \
      result[i] = (lhs[i] ##oper rhs[i]); \
    } \
    return result; \
  } \
}

#define VECT_SCALAR_OPERATORS(result_type, vect_type, oper, scalar_type) \
namespace vects { \
  result_type \
  operator##oper (const vect_type& lhs, const scalar_type& rhs) { \
    result_type result(lhs.size()); \
    for (std::size_t i=0; i<lhs.size(); i++) { \
      result[i] = (lhs[i] ##oper rhs ); \
    } \
    return result; \
  } \
}

#define SCALAR_VECT_OPERATORS(result_type, scalar_type, oper, vect_type) \
namespace vects { \
  result_type \
  operator##oper (const scalar_type& lhs, const vect_type& rhs) { \
    result_type result(rhs.size()); \
    for (std::size_t i=0; i<rhs.size(); i++) { \
      result[i] = (lhs ##oper rhs[i]); \
    } \
    return result; \
  } \
}

#define MATH_VECT_VECT_OPERATORS(result_type, vect_type1, vect_type2) \
  VECT_VECT_OPERATORS(result_type, vect_type1, +, vect_type2) \
  VECT_VECT_OPERATORS(result_type, vect_type1, -, vect_type2) \
  VECT_VECT_OPERATORS(result_type, vect_type1, *, vect_type2) \
  VECT_VECT_OPERATORS(result_type, vect_type1, /, vect_type2)

#define COMP_VECT_VECT_OPERATORS(vect_type1, vect_type2) \
  VECT_VECT_OPERATORS(std::vector<bool>, vect_type1, <,  vect_type2) \
  VECT_VECT_OPERATORS(std::vector<bool>, vect_type1, <=, vect_type2) \
  VECT_VECT_OPERATORS(std::vector<bool>, vect_type1, ==, vect_type2) \
  VECT_VECT_OPERATORS(std::vector<bool>, vect_type1, !=, vect_type2) \
  VECT_VECT_OPERATORS(std::vector<bool>, vect_type1, >,  vect_type2) \
  VECT_VECT_OPERATORS(std::vector<bool>, vect_type1, >=, vect_type2)

#define MATH_VECT_SCALAR_OPERATORS(result_type, vect_type, scalar_type) \
  VECT_SCALAR_OPERATORS(result_type, vect_type, +, scalar_type) \
  VECT_SCALAR_OPERATORS(result_type, vect_type, -, scalar_type) \
  VECT_SCALAR_OPERATORS(result_type, vect_type, *, scalar_type) \
  VECT_SCALAR_OPERATORS(result_type, vect_type, /, scalar_type)

#define COMP_VECT_SCALAR_OPERATORS(vect_type, scalar_type) \
  VECT_SCALAR_OPERATORS(std::vector<bool>, vect_type, <,  scalar_type) \
  VECT_SCALAR_OPERATORS(std::vector<bool>, vect_type, <=, scalar_type) \
  VECT_SCALAR_OPERATORS(std::vector<bool>, vect_type, ==, scalar_type) \
  VECT_SCALAR_OPERATORS(std::vector<bool>, vect_type, !=, scalar_type) \
  VECT_SCALAR_OPERATORS(std::vector<bool>, vect_type, >,  scalar_type) \
  VECT_SCALAR_OPERATORS(std::vector<bool>, vect_type, >=, scalar_type)

#define MATH_SCALAR_VECT_OPERATORS(result_type, scalar_type, vect_type) \
  SCALAR_VECT_OPERATORS(result_type, scalar_type, +, vect_type) \
  SCALAR_VECT_OPERATORS(result_type, scalar_type, -, vect_type) \
  SCALAR_VECT_OPERATORS(result_type, scalar_type, *, vect_type) \
  SCALAR_VECT_OPERATORS(result_type, scalar_type, /, vect_type)

MATH_VECT_VECT_OPERATORS(dvect, dvect, dvect)
COMP_VECT_VECT_OPERATORS(       dvect, dvect)
MATH_VECT_SCALAR_OPERATORS(dvect, dvect, double)
COMP_VECT_SCALAR_OPERATORS(       dvect, double)
MATH_SCALAR_VECT_OPERATORS(dvect, double, dvect)
// comparison operators not needed since Python uses reflection

MATH_VECT_VECT_OPERATORS(ivect, ivect, ivect)
COMP_VECT_VECT_OPERATORS(       ivect, ivect)
MATH_VECT_SCALAR_OPERATORS(ivect, ivect, int)
COMP_VECT_SCALAR_OPERATORS(       ivect, int)
MATH_SCALAR_VECT_OPERATORS(ivect, int, ivect)
// comparison operators not needed since Python uses reflection

MATH_VECT_VECT_OPERATORS(dvect, dvect, ivect)
COMP_VECT_VECT_OPERATORS(       dvect, ivect)
MATH_VECT_VECT_OPERATORS(dvect, ivect, dvect)
COMP_VECT_VECT_OPERATORS(       ivect, dvect)

#undef VECT_VECT_OPERATORS
#undef SCALAR_VECT_OPERATORS
#undef VECT_SCALAR_OPERATORS
#undef MATH_VECT_VECT_OPERATORS
#undef COMP_VECT_VECT_OPERATORS
#undef MATH_VECT_SCALAR_OPERATORS
#undef COMP_VECT_SCALAR_OPERATORS
#undef MATH_SCALAR_VECT_OPERATORS

namespace {

  void init_module(boost::python::module_builder& this_module)
  {
    (void) example::wrap_vector(this_module, "vector_of_bool", bool());

    const long
    math_operators (  boost::python::op_mul | boost::python::op_add
                    | boost::python::op_div | boost::python::op_sub);
    const long
    comp_operators = (  boost::python::op_lt | boost::python::op_le
                      | boost::python::op_eq | boost::python::op_ne
                      | boost::python::op_gt | boost::python::op_ge);

    boost::python::class_builder<vects::dvect>
      dvect_class(this_module, "dvect");
    boost::python::class_builder<vects::ivect>
      ivect_class(this_module, "ivect");

    dvect_class.def(boost::python::constructor<boost::python::tuple>());
    dvect_class.def(&vects::dvect::as_tuple,"as_tuple");

    dvect_class.def(boost::python::operators<math_operators>());
    dvect_class.def(boost::python::operators<math_operators>(),
      boost::python::right_operand<double>() );
    dvect_class.def(boost::python::operators<math_operators>(),
      boost::python::left_operand<double>() );
    dvect_class.def(boost::python::operators<math_operators>(),
      boost::python::right_operand<vects::ivect>() );

    dvect_class.def(boost::python::operators<comp_operators>());
    dvect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<double>() );
    // left_operand not needed since Python uses reflection
    dvect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<vects::ivect>() );

    ivect_class.def(boost::python::constructor<boost::python::tuple>());
    ivect_class.def(&vects::ivect::as_tuple,"as_tuple");

    ivect_class.def(boost::python::operators<math_operators>());
    ivect_class.def(boost::python::operators<math_operators>(),
      boost::python::right_operand<int>() );
    ivect_class.def(boost::python::operators<math_operators>(),
      boost::python::left_operand<int>() );
    ivect_class.def(boost::python::operators<math_operators>(),
      boost::python::right_operand<vects::dvect>() );

    ivect_class.def(boost::python::operators<comp_operators>());
    ivect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<int>() );
    // left_operand not needed since Python uses reflection
    ivect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<vects::dvect>() );
  }

} // namespace <anonymous>

BOOST_PYTHON_MODULE_INIT(richcmp3)
{
    boost::python::module_builder this_module("richcmp3");
    // The actual work is done in a separate function in order
    // to suppress a bogus VC60 warning.
    init_module(this_module);
}
