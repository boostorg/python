///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef SIGNATURE_JDG20020813_HPP
#define SIGNATURE_JDG20020813_HPP

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/mpl/type_list.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python {

template <typename T>
struct signature {};

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//  Temporary BOOST_PP fix before the CVS stabalizes /*$$$ FIX ME $$$*/

#ifndef BOOST_PP_FIX_REPEAT_2ND
#define BOOST_PP_FIX_REPEAT_2ND(c, m, d) /* ... */ \
    BOOST_PP_CAT(BOOST_PP_R2_, c)(m, d)            \
    /**/
#endif

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_TEMPLATE_GEN(INDEX, DATA)  typename BOOST_PP_CAT(T, INDEX)

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_GET_FUNCTION_SIGNATURE(INDEX, DATA)                            \
                                                                                \
    template                                                                    \
    <                                                                           \
        typename RT BOOST_PP_COMMA_IF(INDEX)                                    \
        BOOST_PP_ENUM                                                           \
        (                                                                       \
            INDEX,                                                              \
            BPL_IMPL_TEMPLATE_GEN,                                              \
            BOOST_PP_EMPTY                                                      \
        )                                                                       \
    >                                                                           \
    inline boost::mpl::type_list                                                \
    <                                                                           \
        RT BOOST_PP_COMMA_IF(INDEX) BOOST_PP_ENUM_PARAMS(INDEX, T)              \
    >                                                                           \
    get_signature(signature<RT(*)(BOOST_PP_ENUM_PARAMS(INDEX, T))>)             \
    {                                                                           \
        return boost::mpl::type_list                                            \
            <RT BOOST_PP_COMMA_IF(INDEX) BOOST_PP_ENUM_PARAMS(INDEX, T)>();     \
    }                                                                           \

///////////////////////////////////////////////////////////////////////////////
#define BPL_IMPL_GET_MEMBER_FUNCTION_SIGNATURE(INDEX, DATA)                     \
                                                                                \
    template                                                                    \
    <                                                                           \
        typename RT, typename ClassT BOOST_PP_COMMA_IF(INDEX)                   \
        BOOST_PP_ENUM                                                           \
        (                                                                       \
            INDEX,                                                              \
            BPL_IMPL_TEMPLATE_GEN,                                              \
            BOOST_PP_EMPTY                                                      \
        )                                                                       \
    >                                                                           \
    inline boost::mpl::type_list                                                \
    <                                                                           \
        RT, ClassT BOOST_PP_COMMA_IF(INDEX) BOOST_PP_ENUM_PARAMS(INDEX, T)      \
    >                                                                           \
    get_signature(signature<RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(INDEX, T))>)     \
    {                                                                           \
        return boost::mpl::type_list                                            \
            <RT, ClassT BOOST_PP_COMMA_IF(INDEX) BOOST_PP_ENUM_PARAMS(INDEX, T)>\
            ();                                                                 \
    }                                                                           \

///////////////////////////////////////////////////////////////////////////////

BOOST_PP_FIX_REPEAT_2ND                                                         \
(                                                                               \
    BOOST_PP_SUB(BOOST_PYTHON_MAX_ARITY, 1),                                    \
    BPL_IMPL_GET_FUNCTION_SIGNATURE, BOOST_PP_EMPTY                             \
)

BOOST_PP_FIX_REPEAT_2ND                                                         \
(                                                                               \
    BOOST_PP_SUB(BOOST_PYTHON_MAX_ARITY, 2),                                    \
    BPL_IMPL_GET_MEMBER_FUNCTION_SIGNATURE, BOOST_PP_EMPTY                      \
)

#undef BPL_IMPL_GET_FUNCTION_SIGNATURE
#undef BPL_IMPL_GET_MEMBER_FUNCTION_SIGNATURE
#undef BPL_IMPL_TEMPLATE_GEN

}

}} // namespace boost::python

///////////////////////////////////////////////////////////////////////////////
#endif // SIGNATURE_JDG20020813_HPP


