///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEFAULTS_GEN_JDG20020807_HPP
#define DEFAULTS_GEN_JDG20020807_HPP

#include <boost/python/detail/preprocessor.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/tuple.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/config.hpp>
#include <boost/python/detail/type_list_utils.hpp>

namespace boost { namespace python { namespace detail {

///////////////////////////////////////////////////////////////////////////////
//
//  func_stubs_base is used as a base class for all function stubs.
//
///////////////////////////////////////////////////////////////////////////////
struct func_stubs_base {};

}}} // namespace boost::python::detail


///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_TYPEDEF_GEN(z, INDEX, DATA)                                    \
    typedef typename boost::python::detail::type_at                             \
    <                                                                           \
        BOOST_PP_ADD(INDEX, DATA),                                              \
        SigT                                                                    \
    >::type BOOST_PP_CAT(T, INDEX);                                             \

#define BPL_IMPL_FUNC_WRAPPER_GEN(z, index, DATA)                                       \
    static RT BOOST_PP_CAT(func_, index) (                                              \
        BOOST_PYTHON_BINARY_ENUM(                                                       \
            BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), index), T, arg)               \
        )                                                                               \
    {                                                                                   \
        BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                                 \
        BOOST_PP_TUPLE_ELEM(3, 0, DATA)                                                 \
        (                                                                               \
            BOOST_PP_ENUM_PARAMS(                                                       \
                BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), index),                   \
                arg                                                                     \
            )                                                                           \
        );                                                                              \
    }

#define BPL_IMPL_GEN_FUNCTION(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS, RETURN)      \
    struct FSTUBS_NAME {                                                        \
                                                                                \
        BOOST_STATIC_CONSTANT(int, n_funcs = BOOST_PP_INC(N_DFLTS));            \
        BOOST_STATIC_CONSTANT(int, max_args = n_funcs);                         \
                                                                                \
        template <typename SigT>                                                \
        struct gen {                                                            \
                                                                                \
            typedef typename boost::python::detail::type_at<0, SigT>::type RT;  \
                                                                                \
            BOOST_PP_REPEAT_2ND                                                 \
            (                                                                   \
                N_ARGS,                                                         \
                BPL_IMPL_TYPEDEF_GEN,                                           \
                1                                                               \
            )                                                                   \
                                                                                \
            BOOST_PP_REPEAT_2ND                                                 \
            (                                                                   \
                BOOST_PP_INC(N_DFLTS),                                          \
                BPL_IMPL_FUNC_WRAPPER_GEN,                                      \
                (FNAME, BOOST_PP_SUB(N_ARGS, N_DFLTS), RETURN)                  \
            )                                                                   \
        };                                                                      \
    };                                                                          \

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_MEM_FUNC_WRAPPER_GEN(z, index, DATA)                           \
    static RT BOOST_PP_CAT(func_, index) (                                      \
        ClassT& obj BOOST_PP_COMMA_IF(                                          \
            BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), index))               \
        BOOST_PYTHON_BINARY_ENUM(                                               \
            BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), index), T, arg)       \
        )                                                                       \
    {                                                                           \
        BOOST_PP_TUPLE_ELEM(3, 2, DATA) obj.BOOST_PP_TUPLE_ELEM(3, 0, DATA)(    \
            BOOST_PP_ENUM_PARAMS(                                               \
                BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), index), arg       \
            )                                                                   \
        );                                                                      \
    }

#define BPL_IMPL_GEN_MEM_FUNCTION(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS, RETURN)          \
    struct FSTUBS_NAME {                                                                \
                                                                                        \
        BOOST_STATIC_CONSTANT(int, n_funcs = BOOST_PP_INC(N_DFLTS));                    \
        BOOST_STATIC_CONSTANT(int, max_args = n_funcs + 1);                             \
                                                                                        \
        template <typename SigT>                                                        \
        struct gen {                                                                    \
                                                                                        \
            typedef typename boost::python::detail::type_at<0, SigT>::type RT;          \
            typedef typename boost::python::detail::type_at<1, SigT>::type ClassT;      \
                                                                                        \
            BOOST_PP_REPEAT_2ND                                                         \
            (                                                                           \
                N_ARGS,                                                                 \
                BPL_IMPL_TYPEDEF_GEN,                                                   \
                2                                                                       \
            )                                                                           \
                                                                                        \
            BOOST_PP_REPEAT_2ND                                                         \
            (                                                                           \
                BOOST_PP_INC(N_DFLTS),                                                  \
                BPL_IMPL_MEM_FUNC_WRAPPER_GEN,                                          \
                (FNAME, BOOST_PP_SUB(N_ARGS, N_DFLTS), RETURN)                          \
            )                                                                           \
        };                                                                              \
    };


///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_MSVC)

#define BPL_IMPL_GEN_FUNCTION_STUB(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS)         \
    BPL_IMPL_GEN_FUNCTION                                                       \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _NV), N_ARGS, N_DFLTS, return)        \
    BPL_IMPL_GEN_FUNCTION                                                       \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _V), N_ARGS, N_DFLTS, ;)              \
    struct FSTUBS_NAME                                                          \
    : public boost::python::detail::func_stubs_base {                           \
                                                                                \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  nv_type;                        \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _V)   v_type;                         \
    };                                                                          \

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_GEN_MEM_FUNCTION_STUB(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS)     \
    BPL_IMPL_GEN_MEM_FUNCTION                                                   \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _NV), N_ARGS, N_DFLTS, return)        \
    BPL_IMPL_GEN_MEM_FUNCTION                                                   \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _V), N_ARGS, N_DFLTS, ;)              \
    struct FSTUBS_NAME                                                          \
    : public boost::python::detail::func_stubs_base {                           \
                                                                                \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  nv_type;                        \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _V)   v_type;                         \
    };                                                                          \

#else

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_GEN_FUNCTION_STUB(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS)         \
    BPL_IMPL_GEN_FUNCTION                                                       \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _NV), N_ARGS, N_DFLTS, return)        \
    struct FSTUBS_NAME                                                          \
    : public boost::python::detail::func_stubs_base {                           \
                                                                                \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  nv_type;                        \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  v_type;                         \
    };                                                                          \

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_GEN_MEM_FUNCTION_STUB(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS)     \
    BPL_IMPL_GEN_MEM_FUNCTION                                                   \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _NV), N_ARGS, N_DFLTS, return)        \
    struct FSTUBS_NAME                                                          \
    : public boost::python::detail::func_stubs_base {                           \
                                                                                \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  nv_type;                        \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  v_type;                         \
    };                                                                          \

#endif // defined(BOOST_MSVC)

///////////////////////////////////////////////////////////////////////////////
//
//  MAIN MACROS
//
//      Given GENERATOR_NAME, FNAME, MIN_ARGS and MAX_ARGS, These macros
//      generate function stubs that forward to a function or member function
//      named FNAME. MAX_ARGS is the arity of the function or member function
//      FNAME. FNAME can have default arguments. MIN_ARGS is the minimum
//      arity that FNAME can accept.
//
//      There are two versions:
//
//          1. BOOST_PYTHON_FUNCTION_OVERLOADS for free functions
//          2. BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS for member functions.
//
//      For instance, given a function:
//
//      int
//      foo(int a, char b = 1, unsigned c = 2, double d = 3)
//      {
//          return a + b + c + int(d);
//      }
//
//      The macro invocation:
//
//          BOOST_PYTHON_FUNCTION_OVERLOADS(foo_stubs, foo, 1, 4)
//
//      Generates this code:
//
//      struct foo_stubs_NV  {
//
//          static const int n_funcs = 4;
//          static const int max_args = n_funcs;
//
//          template <typename SigT>
//          struct gen {
//
//              typedef typename mpl::at_c<0, SigT>::type RT;
//              typedef typename mpl::at_c<1, SigT>::type T0;
//              typedef typename mpl::at_c<2, SigT>::type T1;
//              typedef typename mpl::at_c<3, SigT>::type T2;
//              typedef typename mpl::at_c<4, SigT>::type T3;
//
//              static RT func_0(T0 arg0)
//              { return foo(arg0); }
//
//              static RT func_1(T0 arg0, T1 arg1)
//              { return foo(arg0, arg1); }
//
//              static RT func_2(T0 arg0, T1 arg1, T2 arg2)
//              { return foo(arg0, arg1, arg2); }
//
//              static RT func_3(T0 arg0, T1 arg1, T2 arg2, T3 arg3)
//              { return foo(arg0, arg1, arg2, arg3); }
//          };
//      };
//
//      struct foo_stubs
//      :   public boost::python::detail::func_stubs_base {
//
//          typedef foo_stubs_NV    nv_type;
//          typedef foo_stubs_NV    v_type;
//      };
//
//      The typedefs nv_type and v_type are used to handle compilers that
//      do not support void returns. The example above typedefs nv_type
//      and v_type to foo_stubs_NV. On compilers that do not support
//      void returns, there are two versions: foo_stubs_NV and foo_stubs_V.
//      The "V" version is almost identical to the "NV" version except
//      for the return type (void) and the lack of the return keyword.
//
///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_FUNCTION_OVERLOADS(GENERATOR_NAME, FNAME, MIN_ARGS, MAX_ARGS)      \
    BPL_IMPL_GEN_FUNCTION_STUB                                                          \
    (                                                                                   \
        FNAME,                                                                          \
        GENERATOR_NAME,                                                                 \
        MAX_ARGS,                                                                       \
        BOOST_PP_SUB(MAX_ARGS, MIN_ARGS)                                                \
    )

#define BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(GENERATOR_NAME, FNAME, MIN_ARGS, MAX_ARGS)       \
    BPL_IMPL_GEN_MEM_FUNCTION_STUB                                                              \
    (                                                                                           \
        FNAME,                                                                                  \
        GENERATOR_NAME,                                                                         \
        MAX_ARGS,                                                                               \
        BOOST_PP_SUB(MAX_ARGS, MIN_ARGS)                                                        \
    )

// deprecated macro names (to be removed)
#define BOOST_PYTHON_FUNCTION_GENERATOR BOOST_PYTHON_FUNCTION_OVERLOADS
#define BOOST_PYTHON_MEM_FUN_GENERATOR BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS

///////////////////////////////////////////////////////////////////////////////
#endif // DEFAULTS_GEN_JDG20020807_HPP


