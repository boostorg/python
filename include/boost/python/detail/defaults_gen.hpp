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
#include <boost/config.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python { namespace detail {

template <typename DerivedT>
struct func_stubs_base {

    typedef DerivedT derived_t;

    DerivedT& derived()
    { return *static_cast<DerivedT*>(this); }

    DerivedT const& derived() const
    { return *static_cast<DerivedT const*>(this); }
};

}}} // namespace boost::python::detail

///////////////////////////////////////////////////////////////////////////////
//  Temporary BOOST_PP fix before the CVS stabalizes /*$$$ FIX ME $$$*/

#ifndef BOOST_PP_FIX_REPEAT_2ND
#define BOOST_PP_FIX_REPEAT_2ND(c, m, d) /* ... */ \
    BOOST_PP_CAT(BOOST_PP_R2_, c)(m, d)            \
    /**/
#endif

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_TYPEDEF_GEN(INDEX, DATA)                                       \
    typedef typename boost::mpl::at                                             \
    <                                                                           \
        BOOST_PP_ADD(INDEX, DATA),                                              \
        SigT                                                                    \
    >::type BOOST_PP_CAT(T, INDEX);                                             \

#define BPL_IMPL_ARGS_GEN(INDEX, DATA)                                          \
    BOOST_PP_CAT(T, INDEX) BOOST_PP_CAT(arg, INDEX)                             \

#define BPL_IMPL_FUNC_WRAPPER_GEN(INDEX, DATA)                                  \
    static RT BOOST_PP_CAT(func_, INDEX)                                        \
    (                                                                           \
        BOOST_PP_ENUM                                                           \
        (                                                                       \
            BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), INDEX),               \
            BPL_IMPL_ARGS_GEN,                                                  \
            BOOST_PP_EMPTY                                                      \
        )                                                                       \
    )                                                                           \
    {                                                                           \
        BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                         \
        BOOST_PP_TUPLE_ELEM(3, 0, DATA)                                         \
        (                                                                       \
            BOOST_PP_ENUM_PARAMS                                                \
            (                                                                   \
                BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), INDEX),           \
                arg                                                             \
            )                                                                   \
        );                                                                      \
    }                                                                           \

#define BPL_IMPL_GEN_FUNCTION(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS, RETURN)      \
    struct FSTUBS_NAME {                                                        \
                                                                                \
        BOOST_STATIC_CONSTANT(int, n_funcs = BOOST_PP_INC(N_DFLTS));            \
        BOOST_STATIC_CONSTANT(int, max_args = n_funcs);                         \
                                                                                \
        static char const*                                                      \
        name() { return BOOST_PP_STRINGIZE(FNAME); }                            \
                                                                                \
        template <typename SigT>                                                \
        struct gen {                                                            \
                                                                                \
            typedef typename boost::mpl::at<0, SigT>::type RT;                  \
                                                                                \
            BOOST_PP_FIX_REPEAT_2ND                                             \
            (                                                                   \
                BOOST_PP_INC(N_DFLTS),                                          \
                BPL_IMPL_TYPEDEF_GEN,                                           \
                1                                                               \
            )                                                                   \
                                                                                \
            BOOST_PP_FIX_REPEAT_2ND                                             \
            (                                                                   \
                BOOST_PP_INC(N_DFLTS),                                          \
                BPL_IMPL_FUNC_WRAPPER_GEN,                                      \
                (FNAME, BOOST_PP_SUB(N_ARGS, N_DFLTS), RETURN)                  \
            )                                                                   \
        };                                                                      \
    };                                                                          \

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_MEM_FUNC_WRAPPER_GEN(INDEX, DATA)                              \
    static RT BOOST_PP_CAT(func_, INDEX)                                        \
    (                                                                           \
        ClassT& obj,                                                            \
        BOOST_PP_ENUM                                                           \
        (                                                                       \
            BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), INDEX),               \
            BPL_IMPL_ARGS_GEN,                                                  \
            BOOST_PP_EMPTY                                                      \
        )                                                                       \
    )                                                                           \
    {                                                                           \
        BOOST_PP_TUPLE_ELEM(3, 2, DATA) obj.                                    \
        BOOST_PP_TUPLE_ELEM(3, 0, DATA)                                         \
        (                                                                       \
            BOOST_PP_ENUM_PARAMS                                                \
            (                                                                   \
                BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 1, DATA), INDEX),           \
                arg                                                             \
            )                                                                   \
        );                                                                      \
    }                                                                           \

#define BPL_IMPL_GEN_MEM_FUNCTION(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS, RETURN)  \
    struct FSTUBS_NAME {                                                        \
                                                                                \
        BOOST_STATIC_CONSTANT(int, n_funcs = BOOST_PP_INC(N_DFLTS));            \
        BOOST_STATIC_CONSTANT(int, max_args = n_funcs + 1);                     \
                                                                                \
        static char const*                                                      \
        name() { return BOOST_PP_STRINGIZE(FNAME); }                            \
                                                                                \
        template <typename SigT>                                                \
        struct gen {                                                            \
                                                                                \
            typedef typename boost::mpl::at<0, SigT>::type RT;                  \
            typedef typename boost::mpl::at<1, SigT>::type ClassT;              \
                                                                                \
            BOOST_PP_FIX_REPEAT_2ND                                             \
            (                                                                   \
                BOOST_PP_INC(N_DFLTS),                                          \
                BPL_IMPL_TYPEDEF_GEN,                                           \
                2                                                               \
            )                                                                   \
                                                                                \
            BOOST_PP_FIX_REPEAT_2ND                                             \
            (                                                                   \
                BOOST_PP_INC(N_DFLTS),                                          \
                BPL_IMPL_MEM_FUNC_WRAPPER_GEN,                                  \
                (FNAME, BOOST_PP_SUB(N_ARGS, N_DFLTS), RETURN)                  \
            )                                                                   \
        };                                                                      \
    };                                                                          \
                                                                                \

///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_MSVC)

#define BPL_IMPL_GEN_FUNCTION_STUB(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS)         \
    BPL_IMPL_GEN_FUNCTION                                                       \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _NV), N_ARGS, N_DFLTS, return)        \
    BPL_IMPL_GEN_FUNCTION                                                       \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _V), N_ARGS, N_DFLTS, ;)              \
    struct FSTUBS_NAME                                                          \
    : public boost::python::detail::func_stubs_base<FSTUBS_NAME> {              \
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
    : public boost::python::detail::func_stubs_base<FSTUBS_NAME> {              \
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
    : public boost::python::detail::func_stubs_base<FSTUBS_NAME> {              \
                                                                                \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  nv_type;                        \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  v_type;                         \
    };                                                                          \

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_GEN_MEM_FUNCTION_STUB(FNAME, FSTUBS_NAME, N_ARGS, N_DFLTS)     \
    BPL_IMPL_GEN_MEM_FUNCTION                                                   \
        (FNAME, BOOST_PP_CAT(FSTUBS_NAME, _NV), N_ARGS, N_DFLTS, return)        \
    struct FSTUBS_NAME                                                          \
    : public boost::python::detail::func_stubs_base<FSTUBS_NAME> {              \
                                                                                \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  nv_type;                        \
        typedef BOOST_PP_CAT(FSTUBS_NAME, _NV)  v_type;                         \
    };                                                                          \

#endif // defined(BOOST_MSVC)

///////////////////////////////////////////////////////////////////////////////
//
//  MAIN MACROS
//
///////////////////////////////////////////////////////////////////////////////
#define BOOST_PYTHON_FUNCTION_GEN(GENERATOR_NAME, FNAME, MIN_ARGS, MAX_ARGS)    \
    BPL_IMPL_GEN_FUNCTION_STUB                                                  \
    (                                                                           \
        FNAME,                                                                  \
        GENERATOR_NAME,                                                         \
        MAX_ARGS,                                                               \
        BOOST_PP_SUB(MAX_ARGS, MIN_ARGS)                                        \
    )                                                                           \

#define BOOST_PYTHON_MEMBER_FUNCTION_GEN(GENERATOR_NAME, FNAME, MIN_ARGS, MAX_ARGS)\
    BPL_IMPL_GEN_MEM_FUNCTION_STUB                                              \
    (                                                                           \
        FNAME,                                                                  \
        GENERATOR_NAME,                                                         \
        MAX_ARGS,                                                               \
        BOOST_PP_SUB(MAX_ARGS, MIN_ARGS)                                        \
    )                                                                           \

///////////////////////////////////////////////////////////////////////////////
#endif // DEFAULTS_GEN_JDG20020807_HPP


