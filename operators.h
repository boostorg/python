#ifndef OPERATORS_UK112000_H_
#define OPERATORS_UK112000_H_

#include "functions.h"
#if !defined(__GNUC__) || defined(__SGI_STL_PORT)
# include <sstream>
#else
# include <strstream>
#endif

namespace python {

namespace detail {
  
  // helper class for automatic operand type detection
  // during operator wrapping.
  struct auto_operand {};
}

// Define operator ids that can be or'ed together
// (python::op_add | python::op_sub | python::op_mul).
// This allows to wrap several operators in one line.
enum operator_id
{ 
    op_add = 0x1, 
    op_sub = 0x2, 
    op_mul = 0x4, 
    op_div = 0x8, 
    op_mod = 0x10, 
    op_divmod =0x20, 
    op_pow = 0x40, 
    op_lshift = 0x80, 
    op_rshift = 0x100, 
    op_and = 0x200, 
    op_xor = 0x400, 
    op_or = 0x800, 
    op_neg = 0x1000, 
    op_pos = 0x2000, 
    op_abs = 0x4000, 
    op_invert = 0x8000, 
    op_int = 0x10000, 
    op_long = 0x20000, 
    op_float = 0x40000, 
    op_str = 0x80000,
    op_cmp = 0x100000 
};

// Wrap the operators given by "which". Usage:
//   foo_class.def(python::operators<(python::op_add | python::op_sub)>());
template <long which, class operand = python::detail::auto_operand>
struct operators {};

// Wrap heterogeneous operators with given left operand type. Usage:
//   foo_class.def(python::operators<(python::op_add | python::op_sub)>(),
//                 python::left_operand<int>());
template <class T>
struct left_operand {};

// Wrap heterogeneous operators with given right operand type. Usage:
//   foo_class.def(python::operators<(python::op_add | python::op_sub)>(),
//                 python::right_operand<int>());
template <class T>
struct right_operand {};

namespace detail
{
  template <class Specified>
  struct operand_select
  {
      template <class wrapped_type>
      struct wrapped
      {
          typedef Specified type;
      };
  };

  template <>
  struct operand_select<auto_operand>
  {
      template <class wrapped_type>
      struct wrapped
      {
          typedef const wrapped_type& type;
      };
  };

  template <long> struct define_operator;

  // Base class which grants access to extension_class_base::add_method() to its derived classes
  struct add_operator_base
  {
   protected:
      static inline void add_method(extension_class_base* target, function* method, const char* name)
          { target->add_method(method, name); }
  };

//
// choose_op, choose_unary_op, and choose_rop
//
// These templates use "poor man's partial specialization" to generate the
// appropriate add_method() call (if any) for a given operator and argument set.
//
//  Usage:
//      choose_op<(which & op_add)>::template args<left_t,right_t>::add(ext_class);
// 
// (see extension_class<>::def_operators() for more examples).
//
  template <long op_selector>
  struct choose_op
  {
      template <class Left, class Right = Left>
      struct args : add_operator_base
      {
          static inline void add(extension_class_base* target)
          {
              typedef define_operator<op_selector> def_op;
              add_method(target,
                         new typename def_op::template operator_function<Left, Right>(),
                         def_op::name());
          }

      };
  };

  // specialization for 0 has no effect
  template <>
  struct choose_op<0>
  {
      template <class Left, class Right = Left>
      struct args
      {
          static inline void add(extension_class_base*)
          {
          }

      };
  };
  
  template <long op_selector>
  struct choose_unary_op
  {
      template <class Operand>
      struct args : add_operator_base
      {
          static inline void add(extension_class_base* target)
          {
              typedef define_operator<op_selector> def_op;
              add_method(target,
                         new typename def_op::template operator_function<Operand>(),
                         def_op::name());
          }

      };
  };
  
  // specialization for 0 has no effect
  template <>
  struct choose_unary_op<0>
  {
      template <class Operand>
      struct args
      {
          static inline void add(extension_class_base*)
          {
          }

      };
  };
  
  template <long op_selector>
  struct choose_rop
  {
      template <class Left, class Right = Left>
      struct args : add_operator_base
      {
          static inline void add(extension_class_base* target)
          {
              typedef define_operator<op_selector> def_op;
              add_method(target,
                         new typename def_op::template roperator_function<Right, Left>(),
                         def_op::rname());
          }

      };
  };
  
  // specialization for 0 has no effect
  template <>
  struct choose_rop<0>
  {
      template <class Left, class Right = Left>
      struct args
      {
          static inline void add(extension_class_base*)
          {
          }

      };
  };
  
// Fully specialize define_operator for all operators defined in operator_id above.
// Every specialization defines one function object for normal operator calls and one
// for operator calls with operands reversed ("__r*__" function variants).
// Specializations for most operators follow a standard pattern: execute the expression
// that uses the operator in question. This standard pattern is realized by the following 
// macros so that the actual specialization can be done by just calling a macro.
#define PY_DEFINE_BINARY_OPERATORS(id, oper)                                            \
  template <>                                                                           \
  struct define_operator<op_##id>                                                       \
  {                                                                                     \
      template <class Left, class Right = Left>                                         \
      struct operator_function : function                                               \
      {                                                                                 \
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const        \
          {                                                                             \
              tuple args(ref(arguments, ref::increment_count));                         \
                                                                                        \
              return BOOST_PYTHON_CONVERSION::to_python(                                          \
                  BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Left>()) oper      \
                  BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Right>()));        \
          }                                                                             \
                                                                                        \
          string function_name() const                                                  \
              { return string(name()); }                                                \
                                                                                        \
          PyObject* description() const                                                 \
          {                                                                             \
            return function_signature(python::type<Left>(), python::type<Right>());     \
          }                                                                             \
      };                                                                                \
                                                                                        \
      template <class Right, class Left>                                                \
      struct roperator_function : function                                              \
      {                                                                                 \
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const        \
          {                                                                             \
              tuple args(ref(arguments, ref::increment_count));                         \
                                                                                        \
              return BOOST_PYTHON_CONVERSION::to_python(                                \
                  BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Left>()) oper      \
                  BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Right>()));        \
          }                                                                             \
                                                                                        \
          string function_name() const                                                  \
              { return string(rname()); }                                               \
                                                                                        \
          PyObject* description() const                                                 \
          {                                                                             \
            return function_signature(python::type<Left>(), python::type<Right>());     \
          }                                                                             \
                                                                                        \
      };                                                                                \
                                                                                        \
      static const char * name() { return "__" #id "__"; }                              \
      static const char * rname() { return "__r" #id "__"; }                            \
  }

#define PY_DEFINE_UNARY_OPERATORS(id, oper) \
  template <>                                                                                   \
  struct define_operator<op_##id>                                                               \
  {                                                                                             \
      template <class operand>                                                                  \
      struct operator_function : function                                                       \
      {                                                                                         \
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const                \
          {                                                                                     \
              tuple args(ref(arguments, ref::increment_count));                                 \
                                                                                                \
              return BOOST_PYTHON_CONVERSION::to_python(                                        \
                  oper(BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<operand>())));        \
          }                                                                                     \
                                                                                                \
          string function_name() const                                                          \
              { return string(name()); }                                                 \
                                                                                                \
          PyObject* description() const                                                         \
          {                                                                                     \
            return function_signature(python::type<operand>());   \
          }                                                                                     \
      };                                                                                        \
                                                                                                \
      static const char * name() { return "__" #id "__"; }                                      \
  }

  PY_DEFINE_BINARY_OPERATORS(add, +);
  PY_DEFINE_BINARY_OPERATORS(sub, -);
  PY_DEFINE_BINARY_OPERATORS(mul, *);
  PY_DEFINE_BINARY_OPERATORS(div, /);
  PY_DEFINE_BINARY_OPERATORS(mod, %);
  PY_DEFINE_BINARY_OPERATORS(lshift, <<);
  PY_DEFINE_BINARY_OPERATORS(rshift, >>);
  PY_DEFINE_BINARY_OPERATORS(and, &);
  PY_DEFINE_BINARY_OPERATORS(xor, ^);
  PY_DEFINE_BINARY_OPERATORS(or, |);

  PY_DEFINE_UNARY_OPERATORS(neg, -);
  PY_DEFINE_UNARY_OPERATORS(pos, +);
  PY_DEFINE_UNARY_OPERATORS(abs, abs);
  PY_DEFINE_UNARY_OPERATORS(invert, ~);
  PY_DEFINE_UNARY_OPERATORS(int, long);
  PY_DEFINE_UNARY_OPERATORS(long, PyLong_FromLong);
  PY_DEFINE_UNARY_OPERATORS(float, double);

#undef PY_DEFINE_BINARY_OPERATORS
#undef PY_DEFINE_UNARY_OPERATORS

// Some operators need special treatment, e.g. because there is no corresponding 
// expression in C++. These are specialized manually.

// pow(): Manual specialization needed because an error message is required if this 
// function is called with three arguments. The "power modulo" operator is not  
// supported by define_operator, but can be wrapped manually (see special.html).
  template <>
  struct define_operator<op_pow>
  {
      template <class Left, class Right = Left>
      struct operator_function : function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              tuple args(ref(arguments, ref::increment_count));

              if (args.size() == 3 && args[2]->ob_type != Py_None->ob_type)
              {
                  PyErr_SetString(PyExc_TypeError, "expected 2 arguments, got 3");
                  throw argument_error();
              }

              return BOOST_PYTHON_CONVERSION::to_python(
                  pow(BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Left>()),
                   BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Right>()))); 
          }

          string function_name() const  
              { return string(name()); } 

          PyObject* description() const 
          {
            return function_signature(python::type<Left>(), python::type<Right>());
          }

      };

      template <class Right, class Left>
      struct roperator_function : function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              tuple args(ref(arguments, ref::increment_count));

              if (args.size() == 3 && args[2]->ob_type != Py_None->ob_type)
              {
                  PyErr_SetString(PyExc_TypeError, "'__pow__' expected 2 arguments, got 3.");
                  throw argument_error();
              }

              return BOOST_PYTHON_CONVERSION::to_python(
                  pow(BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Left>()),
                   BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Right>()))); 
          }

          string function_name() const  
              { return string(rname()); } 

          PyObject* description() const 
          {
            return function_signature(python::type<Left>(), python::type<Right>());
          }

      };

      static const char * name() { return "__pow__"; }
      static const char * rname() { return "__rpow__"; }
  };

// divmod(): Manual specialization needed because we must actually call two operators and
// return a tuple containing both results
  template <>
  struct define_operator<op_divmod>
  {
      template <class Left, class Right = Left>
      struct operator_function : function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              tuple args(ref(arguments, ref::increment_count));
              PyObject * res = PyTuple_New(2);

              PyTuple_SET_ITEM(res, 0,
                BOOST_PYTHON_CONVERSION::to_python(
                   BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Left>()) /
                   BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Right>()))); 
              PyTuple_SET_ITEM(res, 1,
                BOOST_PYTHON_CONVERSION::to_python(
                   BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Left>()) %
                   BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Right>())));

              return res; 
          }

          string function_name() const  
              { return string(name()); } 

          PyObject* description() const 
          {
            return function_signature(python::type<Left>(), python::type<Right>());
          }

      };

      template <class Right, class Left>
      struct roperator_function : function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              tuple args(ref(arguments, ref::increment_count));
              PyObject * res = PyTuple_New(2);

              PyTuple_SET_ITEM(res, 0,
                BOOST_PYTHON_CONVERSION::to_python(
                   BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Left>()) /
                   BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Right>()))); 
              PyTuple_SET_ITEM(res, 1,
                BOOST_PYTHON_CONVERSION::to_python(
                   BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Left>()) %
                   BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Right>())));

              return res; 
          }

          string function_name() const  
              { return string(rname()); } 

          PyObject* description() const 
          {
            return function_signature(python::type<Left>(), python::type<Right>());
          }
      };

      static const char * name() { return "__divmod__"; }
      static const char * rname() { return "__rdivmod__"; }
  };

// cmp(): Manual specialization needed because there is no three-way compare in C++.
// It is implemented by two one-way comparisons with operators reversed in the second.
  template <>
  struct define_operator<op_cmp>
  {
      template <class Left, class Right = Left>
      struct operator_function : function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              tuple args(ref(arguments, ref::increment_count));

              return BOOST_PYTHON_CONVERSION::to_python(
                  (BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Left>()) <
                   BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Right>())) ?
                       - 1 :
                       (BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Right>()) <
                       BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Left>())) ?
                           1 :
                           0) ; 
          }

          string function_name() const  
              { return string(name()); } 

          PyObject* description() const 
          {
            return function_signature(python::type<Left>(), python::type<Right>());
          }

      };

      template <class Right, class Left>
      struct roperator_function : function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              tuple args(ref(arguments, ref::increment_count));

              return BOOST_PYTHON_CONVERSION::to_python(
                  (BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Left>()) <
                   BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Right>())) ?
                       - 1 :
                       (BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<Right>()) <
                       BOOST_PYTHON_CONVERSION::from_python(args[1].get(), python::type<Left>())) ?
                           1 :
                           0) ; 
          }

          string function_name() const  
              { return string(rname()); } 

          PyObject* description() const 
          {
            return function_signature(python::type<Left>(), python::type<Right>());
          }

      };

      static const char * name() { return "__cmp__"; }
      static const char * rname() { return "__rcmp__"; }
  };

// str(): Manual specialization needed because the string conversion does not follow
// the standard pattern relized by the macros.
  template <>
  struct define_operator<op_str>
  {
      template <class operand>
      struct operator_function : function
      {
          PyObject* do_call(PyObject* arguments, PyObject*) const
          { 
              tuple args(ref(arguments, ref::increment_count));

#if !defined(__GNUC__) || defined(__SGI_STL_PORT)
              std::ostringstream s;
              s << BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<operand>());
#else
              std::ostrstream s;
              s << BOOST_PYTHON_CONVERSION::from_python(args[0].get(), python::type<operand>()) << char();
#endif

#if !defined(__GNUC__) || defined(__SGI_STL_PORT)
              return BOOST_PYTHON_CONVERSION::to_python(s.str()); 
#else
              return BOOST_PYTHON_CONVERSION::to_python(const_cast<char const *>(s.str())); 
#endif
          }

          string function_name() const  
              { return string(name()); } 

          PyObject* description() const 
          {
            return function_signature(python::type<operand>());
          }

      };

      static const char * name() { return "__str__"; }
  };


} // namespace detail

} // namespace python

#endif /* OPERATORS_UK112000_H_ */
