#include "dvect.h"
#include "ivect.h"
#include <boost/python/class_builder.hpp>

//------------------ Overload DVECT --------------------------------

#define DVECT_BINARY_OPERATORS( oper ) \
namespace vects { \
  dvect operator##oper (const dvect& a, const dvect& b) {                  \
    if (a.size()!=b.size()){throw boost::python::argument_error();}        \
    dvect result(a.size());                                                \
    dvect::const_iterator a_it = a.begin();                                \
    dvect::const_iterator b_it = b.begin();                                \
    dvect::iterator r_it = result.begin();                                 \
    for (int i=0; i<a.size(); i++) { r_it[i] = (a_it[i] ##oper b_it[i]); } \
    return result;                                                         \
  } \
}
DVECT_BINARY_OPERATORS( + )
DVECT_BINARY_OPERATORS( - )
DVECT_BINARY_OPERATORS( * )
DVECT_BINARY_OPERATORS( / )
DVECT_BINARY_OPERATORS( > )
DVECT_BINARY_OPERATORS( >= )
DVECT_BINARY_OPERATORS( < )
DVECT_BINARY_OPERATORS( <= )
DVECT_BINARY_OPERATORS( == )
DVECT_BINARY_OPERATORS( != )
#undef DVECT_BINARY_OPERATORS

#define DVECT_SCALAR_BINARY_OPERATORS( scalar_type, oper ) \
namespace vects { \
  dvect operator##oper (const dvect& a, const scalar_type& b) {       \
    dvect result(a.size());                                           \
    dvect::const_iterator a_it = a.begin();                           \
    dvect::iterator r_it = result.begin();                            \
    for (int i=0; i<a.size(); i++) { r_it[i] = (a_it[i] ##oper b ); } \
    return result;                                                    \
  } \
}
DVECT_SCALAR_BINARY_OPERATORS( double, + )
DVECT_SCALAR_BINARY_OPERATORS( double, - )
DVECT_SCALAR_BINARY_OPERATORS( double, * )
DVECT_SCALAR_BINARY_OPERATORS( double, / )
DVECT_SCALAR_BINARY_OPERATORS( double, > )
DVECT_SCALAR_BINARY_OPERATORS( double, >= )
DVECT_SCALAR_BINARY_OPERATORS( double, < )
DVECT_SCALAR_BINARY_OPERATORS( double, <= )
DVECT_SCALAR_BINARY_OPERATORS( double, == )
DVECT_SCALAR_BINARY_OPERATORS( double, != )
#undef DVECT_SCALAR_BINARY_OPERATORS

#define SCALAR_DVECT_BINARY_OPERATORS( scalar_type, oper ) \
namespace vects { \
  dvect operator##oper (const scalar_type& a, const dvect& b) {       \
    dvect result(b.size());                                           \
    dvect::const_iterator b_it = b.begin();                           \
    dvect::iterator r_it = result.begin();                            \
    for (int i=0; i<b.size(); i++) { r_it[i] = (a ##oper b_it[i] ); } \
    return result;                                                    \
  } \
}
SCALAR_DVECT_BINARY_OPERATORS( double, + )
SCALAR_DVECT_BINARY_OPERATORS( double, - )
SCALAR_DVECT_BINARY_OPERATORS( double, * )
SCALAR_DVECT_BINARY_OPERATORS( double, / )
#undef SCALAR_DVECT_BINARY_OPERATORS

//------------------ Overload IVECT --------------------------------

#define IVECT_BINARY_OPERATORS( oper ) \
namespace vects { \
  ivect operator##oper (const ivect& a, const ivect& b) {\
    if (a.size()!=b.size()){throw boost::python::argument_error();}        \
    ivect result(a.size());                                                \
    ivect::const_iterator a_it = a.begin();                                \
    ivect::const_iterator b_it = b.begin();                                \
    ivect::iterator r_it = result.begin();                                 \
    for (int i=0; i<a.size(); i++) { r_it[i] = (a_it[i] ##oper b_it[i]); } \
    return result;                                                         \
  } \
}
IVECT_BINARY_OPERATORS( + )
IVECT_BINARY_OPERATORS( - )
IVECT_BINARY_OPERATORS( * )
IVECT_BINARY_OPERATORS( / )
IVECT_BINARY_OPERATORS( > )
IVECT_BINARY_OPERATORS( >= )
IVECT_BINARY_OPERATORS( < )
IVECT_BINARY_OPERATORS( <= )
IVECT_BINARY_OPERATORS( == )
IVECT_BINARY_OPERATORS( != )
#undef IVECT_BINARY_OPERATORS

#define IVECT_SCALAR_BINARY_OPERATORS( scalar_type, oper ) \
namespace vects { \
  ivect operator##oper (const ivect& a, const scalar_type& b) {       \
    ivect result(a.size());                                           \
    ivect::const_iterator a_it = a.begin();                           \
    ivect::iterator r_it = result.begin();                            \
    for (int i=0; i<a.size(); i++) { r_it[i] = (a_it[i] ##oper b ); } \
    return result;                                                    \
  } \
}
IVECT_SCALAR_BINARY_OPERATORS( int, + )
IVECT_SCALAR_BINARY_OPERATORS( int, - )
IVECT_SCALAR_BINARY_OPERATORS( int, * )
IVECT_SCALAR_BINARY_OPERATORS( int, / )
IVECT_SCALAR_BINARY_OPERATORS( int, > )
IVECT_SCALAR_BINARY_OPERATORS( int, >= )
IVECT_SCALAR_BINARY_OPERATORS( int, < )
IVECT_SCALAR_BINARY_OPERATORS( int, <= )
IVECT_SCALAR_BINARY_OPERATORS( int, == )
IVECT_SCALAR_BINARY_OPERATORS( int, != )
#undef IVECT_SCALAR_BINARY_OPERATORS

#define SCALAR_IVECT_BINARY_OPERATORS( scalar_type, oper ) \
namespace vects { \
  ivect operator##oper (const scalar_type& a, const ivect& b) {       \
    ivect result(b.size());                                           \
    ivect::const_iterator b_it = b.begin();                           \
    ivect::iterator r_it = result.begin();                            \
    for (int i=0; i<b.size(); i++) { r_it[i] = (a ##oper b_it[i] ); } \
    return result;                                                    \
  } \
}
SCALAR_IVECT_BINARY_OPERATORS( int, + )
SCALAR_IVECT_BINARY_OPERATORS( int, - )
SCALAR_IVECT_BINARY_OPERATORS( int, * )
SCALAR_IVECT_BINARY_OPERATORS( int, / )
#undef SCALAR_IVECT_BINARY_OPERATORS

//------------------ IVECT & DVECT Binary ops ---------------------------

#define DI_BINARY_OPERATORS( oper ) \
namespace vects { \
  dvect operator##oper (const dvect& a, const ivect& b) {\
    if (a.size()!=b.size()){throw boost::python::argument_error();}        \
    dvect result(a.size());                                                \
    dvect::const_iterator a_it = a.begin();                                \
    ivect::const_iterator b_it = b.begin();                                \
    dvect::iterator r_it = result.begin();                                 \
    for (int i=0; i<a.size(); i++) { r_it[i] = (a_it[i] ##oper b_it[i]); } \
    return result;                                                         \
  } \
}
DI_BINARY_OPERATORS( + )
DI_BINARY_OPERATORS( - )
DI_BINARY_OPERATORS( * )
DI_BINARY_OPERATORS( / )
DI_BINARY_OPERATORS( > )
DI_BINARY_OPERATORS( >= )
DI_BINARY_OPERATORS( < )
DI_BINARY_OPERATORS( <= )
DI_BINARY_OPERATORS( == )
DI_BINARY_OPERATORS( != )
#undef DI_BINARY_OPERATORS

#define ID_BINARY_OPERATORS( oper ) \
namespace vects { \
  dvect operator##oper (const ivect& a, const dvect& b) { \
    if (a.size()!=b.size()){throw boost::python::argument_error();}        \
    dvect result(a.size());                                                \
    ivect::const_iterator a_it = a.begin();                                \
    dvect::const_iterator b_it = b.begin();                                \
    dvect::iterator r_it = result.begin();                                 \
    for (int i=0; i<a.size(); i++) { r_it[i] = (a_it[i] ##oper b_it[i]); } \
    return result;                                                         \
  } \
}
ID_BINARY_OPERATORS( + )
ID_BINARY_OPERATORS( - )
ID_BINARY_OPERATORS( * )
ID_BINARY_OPERATORS( / )
ID_BINARY_OPERATORS( > )
ID_BINARY_OPERATORS( >= )
ID_BINARY_OPERATORS( < )
ID_BINARY_OPERATORS( <= )
ID_BINARY_OPERATORS( == )
ID_BINARY_OPERATORS( != )
#undef ID_BINARY_OPERATORS

//-------------------- Module ---------------------------------------
#define all_operators (boost::python::op_mul | boost::python::op_add |\
                       boost::python::op_div | boost::python::op_sub )

#define comp_operators (boost::python::op_gt | boost::python::op_ge  |\
                        boost::python::op_lt | boost::python::op_le  |\
                        boost::python::op_eq | boost::python::op_ne)

namespace {

  void init_module(boost::python::module_builder& this_module)
  {
    boost::python::class_builder<vects::dvect>
      dvect_class(this_module, "dvect");
    boost::python::class_builder<vects::ivect>
      ivect_class(this_module, "ivect");

    dvect_class.def(boost::python::constructor<boost::python::tuple>());
    dvect_class.def(&vects::dvect::as_tuple,"as_tuple");

    dvect_class.def(boost::python::operators<all_operators>());
    dvect_class.def(boost::python::operators<all_operators>(),
      boost::python::right_operand<double>() );
    dvect_class.def(boost::python::operators<all_operators>(),
      boost::python::left_operand<double>() );
    dvect_class.def(boost::python::operators<all_operators>(),
      boost::python::right_operand<vects::ivect>() );

    dvect_class.def(boost::python::operators<comp_operators>());
    dvect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<double>() );
    // left_operand not needed since Python uses reflection
    dvect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<vects::ivect>() );

    ivect_class.def(boost::python::constructor<boost::python::tuple>());
    ivect_class.def(&vects::ivect::as_tuple,"as_tuple");

    ivect_class.def(boost::python::operators<all_operators>());
    ivect_class.def(boost::python::operators<all_operators>(),
      boost::python::right_operand<int>() );
    ivect_class.def(boost::python::operators<all_operators>(),
      boost::python::left_operand<int>() );
    ivect_class.def(boost::python::operators<all_operators>(),
      boost::python::right_operand<vects::dvect>() );

    ivect_class.def(boost::python::operators<comp_operators>());
    ivect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<int>() );
    // left_operand not needed since Python uses reflection
    ivect_class.def(boost::python::operators<comp_operators>(),
      boost::python::right_operand<vects::dvect>() );
  }

} // namespace <anonymous>

BOOST_PYTHON_MODULE_INIT(richcmp)
{
  try {
    boost::python::module_builder this_module("richcmp");
    // The actual work is done in separate function in order
    // to suppress a bogus VC60 warning.
    init_module(this_module);
  }
  catch(...){boost::python::handle_exception();}
}
