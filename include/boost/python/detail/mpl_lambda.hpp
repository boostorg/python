// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MPL_LAMBDA_DWA2002122_HPP
# define MPL_LAMBDA_DWA2002122_HPP

# include <boost/mpl/aux_/lambda_support.hpp>

# if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
#   define BOOST_PYTHON_MPL_LAMBDA_SUPPORT(i,name,params)               \
            struct rebind;                                              \
        };                                                              \
    template <BOOST_PP_ENUM_PARAMS_Z(1, i, class X)>                    \
    struct name < BOOST_PP_ENUM_PARAMS_Z(1, i, X) >::rebind             \
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
