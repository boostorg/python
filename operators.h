#ifndef OPERATORS_UK112000_H_
#define OPERATORS_UK112000_H_

#include "functions.h"
#if !defined(__GNUC__) || defined(__SGI_STL_PORT)
# include <sstream>
#else
# include <strstream>
#endif

namespace py {

namespace detail {

  template <long> struct define_operator;

  struct add_operator_base
  {
   protected:
      static inline void add_method(ExtensionClassBase* target, Function* method, const char* name)
          { target->add_method(method, name); }
  };

  template <long op_selector>
  struct choose_op
  {
      template <class Left, class Right = Left>
      struct args : add_operator_base
      {
          static inline void add(ExtensionClassBase* target)
          {
              typedef define_operator<op_selector> def_op;
              add_method(target,
                         new typename def_op::template operator_function<Left, Right>(),
                         def_op::name());
          }

      };
  };
  
  template <>
  struct choose_op<0>
  {
      template <class Left, class Right = Left>
      struct args
      {
          static inline void add(ExtensionClassBase*)
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
          static inline void add(ExtensionClassBase* target)
          {
              typedef define_operator<op_selector> def_op;
              add_method(target,
                         new typename def_op::template operator_function<Operand>(),
                         def_op::name());
          }

      };
  };
  
  template <>
  struct choose_unary_op<0>
  {
      template <class Operand>
      struct args
      {
          static inline void add(ExtensionClassBase*)
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
          static inline void add(ExtensionClassBase* target)
          {
              typedef define_operator<op_selector> def_op;
              add_method(target,
                         new typename def_op::template roperator_function<Right, Left>(),
                         def_op::rname());
          }

      };
  };
  
  template <>
  struct choose_rop<0>
  {
      template <class Left, class Right = Left>
      struct args
      {
          static inline void add(ExtensionClassBase*)
          {
          }

      };
  };
  
#define PY_DEFINE_BINARY_OPERATORS(id, oper) \
  template <> \
  struct define_operator<op_##id> \
  { \
      template <class left, class right = left> \
      struct operator_function : Function \
      { \
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const \
          {  \
              Tuple args(Ptr(arguments, Ptr::new_ref)); \
   \
              return PY_CONVERSION::to_python( \
                  PY_CONVERSION::from_python(args[0].get(), py::Type<left>()) oper \
                  PY_CONVERSION::from_python(args[1].get(), py::Type<right>()));  \
          } \
   \
          const char* description() const \
              { return "__" #id "__"; } \
   \
      }; \
      template <class right, class left> \
      struct roperator_function : Function \
      { \
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const \
          {  \
              Tuple args(Ptr(arguments, Ptr::new_ref)); \
   \
              return PY_CONVERSION::to_python( \
                  PY_CONVERSION::from_python(args[1].get(), py::Type<left>()) oper \
                  PY_CONVERSION::from_python(args[0].get(), py::Type<right>()));  \
          } \
   \
          const char* description() const \
              { return "__r" #id "__"; } \
   \
      }; \
       \
      static const char * name() { return "__" #id "__"; } \
      static const char * rname() { return "__r" #id "__"; } \
  }

#define PY_DEFINE_UNARY_OPERATORS(id, oper) \
  template <> \
  struct define_operator<op_##id> \
  { \
      template <class operand> \
      struct operator_function : Function \
      { \
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const \
          {  \
              Tuple args(Ptr(arguments, Ptr::new_ref)); \
   \
              return PY_CONVERSION::to_python( \
                  oper(PY_CONVERSION::from_python(args[0].get(), py::Type<operand>())));  \
          } \
   \
          const char* description() const \
              { return "__" #id "__"; } \
   \
      }; \
       \
      static const char * name() { return "__" #id "__"; } \
  }

#define PY_DEFINE_CONVERSION_OPERATORS(id, oper) \
  template <> \
  struct define_operator<op_##id> \
  { \
      template <class operand> \
      struct operator_function : Function \
      { \
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const \
          {  \
              Tuple args(Ptr(arguments, Ptr::new_ref)); \
   \
              return PY_CONVERSION::to_python( \
                  oper(PY_CONVERSION::from_python(args[0].get(), py::Type<operand>())));  \
          } \
   \
          const char* description() const \
              { return "__" #id "_"; } \
   \
      }; \
       \
      static const char * name() { return "__" #id "_"; } \
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

  PY_DEFINE_CONVERSION_OPERATORS(int, int);
  PY_DEFINE_CONVERSION_OPERATORS(long, long);
  PY_DEFINE_CONVERSION_OPERATORS(float, double);

#undef PY_DEFINE_BINARY_OPERATORS
#undef PY_DEFINE_UNARY_OPERATORS
#undef PY_DEFINE_CONVERSION_OPERATORS

  template <>
  struct define_operator<op_pow>
  {
      template <class left, class right = left>
      struct operator_function : Function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              Tuple args(Ptr(arguments, Ptr::new_ref));

              if(args.size() == 3 && args[2]->ob_type != Py_None->ob_type)
              {
                  PyErr_SetString(PyExc_TypeError, "expected 2 arguments, got 3");
                  throw ArgumentError();
              }

              return PY_CONVERSION::to_python(
                  pow(PY_CONVERSION::from_python(args[0].get(), py::Type<left>()),
                   PY_CONVERSION::from_python(args[1].get(), py::Type<right>()))); 
          }

          const char* description() const
              { return "__pow__"; }

      };

      template <class right, class left>
      struct roperator_function : Function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              Tuple args(Ptr(arguments, Ptr::new_ref));

              if(args.size() == 3 && args[2]->ob_type != Py_None->ob_type)
              {
                  PyErr_SetString(PyExc_TypeError, "expected 2 arguments, got 3");
                  throw ArgumentError();
              }

              return PY_CONVERSION::to_python(
                  pow(PY_CONVERSION::from_python(args[1].get(), py::Type<left>()),
                   PY_CONVERSION::from_python(args[0].get(), py::Type<right>()))); 
          }

          const char* description() const
              { return "__rpow__"; }

      };

      static const char * name() { return "__pow__"; }
      static const char * rname() { return "__rpow__"; }
  };

  template <>
  struct define_operator<op_divmod>
  {
      template <class left, class right = left>
      struct operator_function : Function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              Tuple args(Ptr(arguments, Ptr::new_ref));
              PyObject * res = PyTuple_New(2);

              PyTuple_SET_ITEM(res, 0,
                PY_CONVERSION::to_python(
                   PY_CONVERSION::from_python(args[0].get(), py::Type<left>()) /
                   PY_CONVERSION::from_python(args[1].get(), py::Type<right>()))); 
              PyTuple_SET_ITEM(res, 1,
                PY_CONVERSION::to_python(
                   PY_CONVERSION::from_python(args[0].get(), py::Type<left>()) %
                   PY_CONVERSION::from_python(args[1].get(), py::Type<right>())));

              return res; 
          }

          const char* description() const
              { return "__divmod__"; }

      };

      template <class right, class left>
      struct roperator_function : Function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              Tuple args(Ptr(arguments, Ptr::new_ref));
              PyObject * res = PyTuple_New(2);

              PyTuple_SET_ITEM(res, 0,
                PY_CONVERSION::to_python(
                   PY_CONVERSION::from_python(args[1].get(), py::Type<left>()) /
                   PY_CONVERSION::from_python(args[0].get(), py::Type<right>()))); 
              PyTuple_SET_ITEM(res, 1,
                PY_CONVERSION::to_python(
                   PY_CONVERSION::from_python(args[1].get(), py::Type<left>()) %
                   PY_CONVERSION::from_python(args[0].get(), py::Type<right>())));

              return res; 
          }

          const char* description() const
              { return "__rdivmod__"; }

      };

      static const char * name() { return "__divmod__"; }
      static const char * rname() { return "__rdivmod__"; }
  };

  template <>
  struct define_operator<op_cmp>
  {
      template <class left, class right = left>
      struct operator_function : Function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              Tuple args(Ptr(arguments, Ptr::new_ref));

              return PY_CONVERSION::to_python(
                  (PY_CONVERSION::from_python(args[0].get(), py::Type<left>()) <
                   PY_CONVERSION::from_python(args[1].get(), py::Type<right>())) ?
                       - 1 :
                       (PY_CONVERSION::from_python(args[1].get(), py::Type<right>()) <
                       PY_CONVERSION::from_python(args[0].get(), py::Type<left>())) ?
                           1 :
                           0) ; 
          }

          const char* description() const
              { return "__cmp__"; }

      };

      template <class right, class left>
      struct roperator_function : Function
      {
          PyObject* do_call(PyObject* arguments, PyObject* /* keywords */) const
          { 
              Tuple args(Ptr(arguments, Ptr::new_ref));

              return PY_CONVERSION::to_python(
                  (PY_CONVERSION::from_python(args[1].get(), py::Type<left>()) <
                   PY_CONVERSION::from_python(args[0].get(), py::Type<right>())) ?
                       - 1 :
                       (PY_CONVERSION::from_python(args[0].get(), py::Type<right>()) <
                       PY_CONVERSION::from_python(args[1].get(), py::Type<left>())) ?
                           1 :
                           0) ; 
          }

          const char* description() const
              { return "__rcmp__"; }

      };

      static const char * name() { return "__cmp__"; }
      static const char * rname() { return "__rcmp__"; }
  };

  template <>
  struct define_operator<op_str>
  {
      template <class operand>
      struct operator_function : Function
      {
          PyObject* do_call(PyObject* arguments, PyObject*) const
          { 
              Tuple args(Ptr(arguments, Ptr::new_ref));

#if !defined(__GNUC__) || defined(__SGI_STL_PORT)
              std::ostringstream s;
#else
              std::strstream s;
#endif
              s << PY_CONVERSION::from_python(args[0].get(), py::Type<operand>());

#if !defined(__GNUC__) || defined(__SGI_STL_PORT)
              return PY_CONVERSION::to_python(s.str()); 
#else
              return PY_CONVERSION::to_python(const_cast<char const *>(s.str())); 
#endif
          }

          const char* description() const
              { return "__str__"; }

      };

      static const char * name() { return "__str__"; }
  };


} // namespace detail

} // namespace py

#endif /* OPERATORS_UK112000_H_ */
