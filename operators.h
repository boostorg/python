#ifndef OPERATORS_UK112000_H_
#define OPERATORS_UK112000_H_

#include "functions.h"
#include <strstream>

namespace py
{

namespace detail
{

    template <>
    struct define_operator<0>
    {
        template <class left, class right = left>
        struct operator_function : Function
        {
            PyObject* do_call(PyObject* arguments, PyObject* keywords) const
            { 
                PyErr_SetString(PyExc_TypeError, "operator not implemented");
                throw ErrorAlreadySet();
            }

            const char* description() const
                { return "__error__"; }

        };
        template <class left, class right = left>
        struct roperator_function : Function
        {
            PyObject* do_call(PyObject* arguments, PyObject* keywords) const
            { 
                PyErr_SetString(PyExc_TypeError, "operator not implemented");
                throw ErrorAlreadySet();
            }

            const char* description() const
                { return "__error__"; }

        };

        static const char * name() { return "__error__"; }
        static const char * rname() { return "__error__"; }
    };

#define py_define_binary_operators(id, oper) \
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
    
#define py_define_unary_operators(id, oper) \
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
    
#define py_define_conversion_operators(id, oper) \
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
    
    py_define_binary_operators(add, +);
    py_define_binary_operators(sub, -);
    py_define_binary_operators(mul, *);
    py_define_binary_operators(div, /);
    py_define_binary_operators(mod, %);
    py_define_binary_operators(lshift, <<);
    py_define_binary_operators(rshift, >>);
    py_define_binary_operators(and, &);
    py_define_binary_operators(xor, ^);
    py_define_binary_operators(or, |);

    py_define_unary_operators(neg, -);
    py_define_unary_operators(pos, +);
    py_define_unary_operators(abs, abs);
    py_define_unary_operators(invert, ~);

    py_define_conversion_operators(int, int);
    py_define_conversion_operators(long, long);
    py_define_conversion_operators(float, double);

#undef py_define_binary_operators
#undef py_define_unary_operators
#undef py_define_conversion_operators
    
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
            PyObject* do_call(PyObject* arguments, PyObject* keywords) const
            { 
                Tuple args(Ptr(arguments, Ptr::new_ref));

                std::strstream s;
                s << PY_CONVERSION::from_python(args[0].get(), py::Type<operand>());

                return PY_CONVERSION::to_python(const_cast<char const *>(s.str())); 
            }

            const char* description() const
                { return "__str__"; }

        };

        static const char * name() { return "__str__"; }
    };


} // namespace detail

} // namespace py

#endif /* OPERATORS_UK112000_H_ */
