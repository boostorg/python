// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MPL_LAMBDA_DWA2002122_HPP
# define MPL_LAMBDA_DWA2002122_HPP

# include <boost/mpl/aux_/lambda_support.hpp>

# if 0 // defined(BOOST_MSVC) && BOOST_MSVC <= 1300
   // This approach fails, unfortunately

#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/comma_if.hpp>

#   define BOOST_PYTHON_LAMBDA_SUPPORT_FORMAL_ARG(R,class_,i,param)     \
    BOOST_PP_COMMA_IF(i) class_ param                                   \
    /**/

#   define BOOST_PYTHON_LAMBDA_SUPPORT_ACTUAL_ARG(R,_,i,param)          \
    BOOST_PP_COMMA_IF(i) param                                          \
    /**/

#   define BOOST_PYTHON_MPL_LAMBDA_SUPPORT(i,name,params)               \
            struct rebind;                                              \
        };                                                              \
    template <                                                          \
        BOOST_PP_LIST_FOR_EACH_I_R(                                     \
              1                                                         \
            , BOOST_PYTHON_LAMBDA_SUPPORT_FORMAL_ARG                    \
            , class                                                     \
            , BOOST_PP_TUPLE_TO_LIST(i,params)                          \
            )                                                           \
        >                                                               \
    struct name <                                                       \
        BOOST_PP_LIST_FOR_EACH_I_R(                                     \
              1                                                         \
            , BOOST_PYTHON_LAMBDA_SUPPORT_ACTUAL_ARG                    \
            , class                                                     \
            , BOOST_PP_TUPLE_TO_LIST(i,params)                          \
            )                                                           \
    >::rebind                                                           \
    {                                                                   \
        BOOST_STATIC_CONSTANT(int, arity = i);                          \
        BOOST_PP_LIST_FOR_EACH_I_R(                                     \
              1                                                         \
            , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC             \
            , typedef                                                   \
            , BOOST_PP_TUPLE_TO_LIST(i,params)                          \
            )                                                           \
                                                                        \
        template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply      \
                : name< BOOST_MPL_PP_PARAMS(i,U) >                      \
        {                                                               \
        };                                                              \
    /**/
#  else
#   define BOOST_PYTHON_MPL_LAMBDA_SUPPORT BOOST_MPL_AUX_LAMBDA_SUPPORT
#  endif 

#endif // MPL_LAMBDA_DWA2002122_HPP
