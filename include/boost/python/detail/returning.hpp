//  (C) Copyright David Abrahams 2001,2002. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_returning.py

#ifndef RETURNING_DWA20011201_HPP
# define RETURNING_DWA20011201_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/config.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/arg_from_python.hpp>
# include <boost/mpl/apply.hpp>

# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/enum.hpp>
# include <boost/preprocessor/enum_shifted.hpp>
# include <boost/preprocessor/expr_if.hpp>
# include <boost/preprocessor/repeat_from_to.hpp>
# include <boost/preprocessor/cat.hpp>

namespace boost { namespace python { namespace detail {


// Calling C++ from Python
template <class R>
struct returning
{
    
# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/returning_non_void.hpp>
# endif 

# define BOOST_PYTHON_ARG_CONVERTIBLE(index,ignored)                    \
    arg_from_python<BOOST_PP_CAT(A,index)>                              \
    BOOST_PP_CAT(c,index)(PyTuple_GET_ITEM(args_, index));              \
    if (!BOOST_PP_CAT(c,index).convertible()) return 0;

# define BOOST_PYTHON_GET_ARG(index,ignored)            \
        BOOST_PP_CAT(c,index)(PyTuple_GET_ITEM(args_, index))

# define BOOST_PYTHON_RETURNING_NON_VOID_MF(args,cv)                            \
    template <class P, BOOST_PP_ENUM_PARAMS(args,class A)>                      \
    static PyObject* call(                                                      \
        BOOST_PYTHON_FN(A0::*pmf,1,args) cv()                                   \
        , PyObject* args_, PyObject*                                            \
        , P const* policies)                                                    \
    {                                                                           \
        /* check that each of the arguments is convertible */                   \
        /* self argument is special */                                          \
        arg_from_python<A0&> c0(PyTuple_GET_ITEM(args_, 0));                    \
        if (!c0.convertible()) return 0;                                        \
                                                                                \
        /* Unroll a loop for the rest of them */                                \
        BOOST_PP_REPEAT_FROM_TO(1,args,BOOST_PYTHON_ARG_CONVERTIBLE,nil)        \
                                                                                \
        /* find the result converter */                                         \
        typedef typename P::result_converter result_converter;                  \
        typename mpl::apply1<result_converter,R>::type cr;                      \
        if (!cr.convertible()) return 0;                                        \
                                                                                \
        if (!policies->precall(args_)) return 0;                                \
                                                                                \
        PyObject* result = cr(                                                  \
            ((BOOST_PYTHON_GET_ARG(0,nil)).*pmf)(                               \
                BOOST_PP_ENUM_SHIFTED(args,BOOST_PYTHON_GET_ARG,nil))           \
            );                                                                  \
                                                                                \
        return policies->postcall(args_, result);                               \
    }

// Generate a series for each cv-qualification
BOOST_PYTHON_REPEAT_MF_ALL_CV_2ND(BOOST_PYTHON_RETURNING_NON_VOID_MF)
    
# define BOOST_PYTHON_RETURNING_NON_VOID_FN(args,ignored)                               \
    template <class P BOOST_PP_COMMA_IF(args) BOOST_PP_ENUM_PARAMS(args,class A)>       \
    static PyObject* call(                                                              \
        BOOST_PYTHON_FN(*pf,0,args)                                                     \
        , PyObject* args_                                                               \
        , PyObject*                                                                     \
        , P const* policies)                                                            \
    {                                                                                   \
        /* check that each of the arguments is convertible */                           \
        BOOST_PP_REPEAT(args,BOOST_PYTHON_ARG_CONVERTIBLE,nil)                          \
                                                                                        \
        /* find the result converter */                                                 \
        typedef typename P::result_converter result_converter;                          \
        typename mpl::apply1<result_converter,R>::type cr;                              \
        if (!cr.convertible()) return 0;                                                \
                                                                                        \
        if (!policies->precall(args_)) return 0;                                        \
                                                                                        \
        PyObject* result = cr(                                                          \
            (*pf)(BOOST_PP_ENUM(args,BOOST_PYTHON_GET_ARG,nil))                         \
            );                                                                          \
                                                                                        \
        return policies->postcall(args_, result);                                       \
    }

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_RETURNING_NON_VOID_FN, nil)
};
                           
template <>
struct returning<void>
{
    typedef void R;

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/returning_void.hpp>
# endif 

#define BOOST_PYTHON_RETURNING_VOID_MF(args,cv)                         \
template<class P,BOOST_PP_ENUM_PARAMS(args,class A)>                    \
static PyObject*call(                                                   \
    BOOST_PYTHON_FN(A0::*pmf,1,args) cv()                               \
    , PyObject*args_                                                    \
    , PyObject*                                                         \
    , P const* policies)                                                \
{                                                                       \
    /* check that each of the arguments is convertible */               \
    /* self argument is special */                                      \
    arg_from_python<A0&>c0(PyTuple_GET_ITEM(args_,0));                  \
    if (!c0.convertible()) return 0;                                    \
                                                                        \
    /* Unroll a loop for the rest of them */                            \
    BOOST_PP_REPEAT_FROM_TO(1,args,BOOST_PYTHON_ARG_CONVERTIBLE,nil)    \
                                                                        \
    if (!policies->precall(args_)) return 0;                            \
                                                                        \
    ((c0(PyTuple_GET_ITEM(args_,0))).*pmf)(                             \
        BOOST_PP_ENUM_SHIFTED(args,BOOST_PYTHON_GET_ARG,nil)            \
        );                                                              \
                                                                        \
    return policies->postcall(args_,detail::none());                    \
}

//Generate a series for each cv-qualification
BOOST_PYTHON_REPEAT_MF_ALL_CV_2ND(BOOST_PYTHON_RETURNING_VOID_MF)
 
#define BOOST_PYTHON_RETURNING_VOID_FN(args,ignored)                            \
template<class P BOOST_PP_COMMA_IF(args) BOOST_PP_ENUM_PARAMS(args,class A)>    \
static PyObject*call(                                                           \
    BOOST_PYTHON_FN(*pf,0,args)                                                 \
    , PyObject*args_                                                            \
    , PyObject*                                                                 \
    , P const* policies)                                                        \
{                                                                               \
    /*check that each of the arguments is convertible*/                         \
    BOOST_PP_REPEAT(args,BOOST_PYTHON_ARG_CONVERTIBLE,nil)                      \
                                                                                \
    BOOST_PP_EXPR_IF(args,if (!policies->precall(args_)) return 0;)             \
                                                                                \
    (*pf)(BOOST_PP_ENUM(args,BOOST_PYTHON_GET_ARG,nil));                        \
                                                                                \
    return policies->postcall(args_,detail::none());                            \
}

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_RETURNING_VOID_FN,nil)

};

}}} // namespace boost::python::detail

#endif//RETURNING_DWA20011201_HPP

