#if !defined(BOOST_PP_IS_ITERATING)

//  (C) Copyright David Abrahams 2001,2002. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_returning.py

# ifndef RETURNING_DWA20011201_HPP
#  define RETURNING_DWA20011201_HPP 

#  include <boost/config.hpp>

#  include <boost/python/arg_from_python.hpp>
#  include <boost/python/detail/wrap_python.hpp>
#  include <boost/python/detail/none.hpp>
#  include <boost/python/detail/preprocessor.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/inc.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#  include <boost/mpl/apply.hpp>

namespace boost { namespace python { namespace detail {

#  define BOOST_PYTHON_RETURNING_NON_VOID 0x0004
#  define BOOST_PYTHON_RETURNING_VOID 0x0008

template <class R>
struct returning
{
    // Specializations for function pointers
#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/returning.hpp>,     \
            BOOST_PYTHON_FUNCTION_POINTER | BOOST_PYTHON_RETURNING_NON_VOID))
#  include BOOST_PP_ITERATE()

    // Specializations for member function pointers
#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (4, (0, 3, <boost/python/detail/returning.hpp>,                          \
            BOOST_PYTHON_POINTER_TO_MEMBER | BOOST_PYTHON_RETURNING_NON_VOID))
#  include BOOST_PP_ITERATE()
};

template <>
struct returning<void>
{
    typedef void R;
    // Specializations for function pointers
#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/returning.hpp>,     \
            BOOST_PYTHON_FUNCTION_POINTER | BOOST_PYTHON_RETURNING_VOID))
#  include BOOST_PP_ITERATE()

    // Specializations for member function pointers
#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (4, (0, 3, <boost/python/detail/returning.hpp>,                          \
            BOOST_PYTHON_POINTER_TO_MEMBER | BOOST_PYTHON_RETURNING_VOID))
#  include BOOST_PP_ITERATE()
};

}}} // namespace boost::python::detail

#  undef BOOST_PYTHON_RETURNING_NON_VOID
#  undef BOOST_PYTHON_RETURNING_VOID

# endif // RETURNING_DWA20011201_HPP

// --------------- function pointers --------------- //
#elif BOOST_PP_ITERATION_DEPTH() == 1 && (BOOST_PP_ITERATION_FLAGS() & BOOST_PYTHON_FUNCTION_POINTER)
# line BOOST_PP_LINE(__LINE__, returning.hpp(function pointers))

# define N BOOST_PP_ITERATION()

# define BOOST_PYTHON_CALL_ARGS(z, n, _) \
    BOOST_PP_COMMA_IF(n) c##n(PyTuple_GET_ITEM(args_, n))
    
# define BOOST_PYTHON_CHECK_CONVERSION(z, n, _)             \
    arg_from_python<A##n> c##n(PyTuple_GET_ITEM(args_, n)); \
    if (!c##n.convertible())                                \
        return 0;

# if (BOOST_PP_ITERATION_FLAGS() & BOOST_PYTHON_RETURNING_NON_VOID)

    template<class P BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
    static PyObject* call(
        R (*pf)(BOOST_PP_ENUM_PARAMS_Z(1, N, A))
        , PyObject* args_
        , PyObject*, P const* policies)
    {
        // check that each of the arguments is convertible
        BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CHECK_CONVERSION, nil)

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename mpl::apply1<result_converter, R>::type cr;
        if (!cr.convertible() || !policies->precall(args_))
            return 0;
        PyObject* result = cr(
            (*pf)(BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CALL_ARGS, nil))
        );
        return policies->postcall(args_, result);
    }
# elif (BOOST_PP_ITERATION_FLAGS() & BOOST_PYTHON_RETURNING_VOID)

    template<class P BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
    static PyObject* call(
        R (*pf)(BOOST_PP_ENUM_PARAMS_Z(1, N, A))
        , PyObject* args_
        , PyObject*, P const* policies)
    {
        // check that each of the arguments is convertible
        BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CHECK_CONVERSION, nil)

        if (!policies->precall(args_))
            return 0;
        (*pf)(BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CALL_ARGS, nil));
        return policies->postcall(args_, detail::none());
    }
# endif // returning void / non-void

# undef N
# undef BOOST_PYTHON_CALL_ARGS
# undef BOOST_PYTHON_CHECK_CONVERSION

// --------------- pointers to members --------------- //
#elif BOOST_PP_ITERATION_DEPTH() == 1 && (BOOST_PP_ITERATION_FLAGS() & BOOST_PYTHON_POINTER_TO_MEMBER)

    // Outer iteration over cv-qualifications
# define BOOST_PP_ITERATION_PARAMS_2                                      \
    (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/returning.hpp>))
# include BOOST_PP_ITERATE()

#elif BOOST_PP_ITERATION_DEPTH() == 2 && BOOST_PP_RELATIVE_FLAGS(1) & BOOST_PYTHON_POINTER_TO_MEMBER
# line BOOST_PP_LINE(__LINE__, returning.hpp(pointers-to-members))

    // Inner iteration over arities
# define N BOOST_PP_ITERATION()
# define Q BOOST_PYTHON_CV_QUALIFIER(BOOST_PP_RELATIVE_ITERATION(1))

# define BOOST_PYTHON_CALL_ARGS(z, n, _)                                \
    BOOST_PP_COMMA_IF(n) c##n(PyTuple_GET_ITEM(args_, BOOST_PP_INC(n)))

# define BOOST_PYTHON_CHECK_CONVERSION(z, n, _)                                 \
    arg_from_python<A##n> c##n(PyTuple_GET_ITEM(args_, BOOST_PP_INC(n)));       \
    if (!c##n.convertible())                                                    \
        return 0;

# if (BOOST_PP_RELATIVE_FLAGS(1) & BOOST_PYTHON_RETURNING_NON_VOID)

    template<class P, class T BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
    static PyObject* call(
        R (T::*pmf)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)) Q
        , PyObject* args_
        , PyObject*, P const* policies)
    {
        // check that each of the arguments is convertible
        // self is special
        arg_from_python<T&> ct(PyTuple_GET_ITEM(args_, 0));
        if (!ct.convertible())
            return 0;
        
        // unroll a loop for the rest of them
        BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CHECK_CONVERSION, nil)

        // find the result converter
        typedef typename P::result_converter result_converter;
        typename mpl::apply1<result_converter, R>::type cr;
        if (!cr.convertible() || !policies->precall(args_))
            return 0;
        PyObject* result = cr(
            ((ct(PyTuple_GET_ITEM(args_, 0))).*pmf)(
                BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CALL_ARGS, nil))
        );
        return policies->postcall(args_, result);
    }
# elif (BOOST_PP_RELATIVE_FLAGS(1) & BOOST_PYTHON_RETURNING_VOID)

    template<class P, class T BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class A)>
    static PyObject* call(
        R (T::*pmf)(BOOST_PP_ENUM_PARAMS_Z(1, N, A)) Q
        , PyObject* args_
        , PyObject*, P const* policies)
    {
        // check that each of the arguments is convertible
        // self is special
        arg_from_python<T&> ct(PyTuple_GET_ITEM(args_, 0));
        if (!ct.convertible())
            return 0;

        // unroll a loop for the rest of them
        BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CHECK_CONVERSION, nil)

        if (!policies->precall(args_))
            return 0;

        ((ct(PyTuple_GET_ITEM(args_, 0))).*pmf)(
            BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_CALL_ARGS, nil));
        return policies->postcall(args_, detail::none());
    }
# endif

# undef N
# undef Q
# undef BOOST_PYTHON_CALL_ARGS
# undef BOOST_PYTHON_CHECK_CONVERSION

#endif
