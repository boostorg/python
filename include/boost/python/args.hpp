// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARGS_DWA2002323_HPP
# define ARGS_DWA2002323_HPP
# include <boost/config.hpp>
# include <boost/mpl/type_list.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/preprocessor/enum_params.hpp>
# include <boost/preprocessor/enum_params_with_a_default.hpp>
# include <boost/preprocessor/comma_if.hpp>

# if !defined(__EDG_VERSION__) || __EDG_VERSION__ > 245
namespace boost { namespace python { 


// A type list for specifying arguments
template < BOOST_MPL_LIST_DEFAULT_PARAMETERS(typename A, boost::mpl::null_argument) >
struct args : boost::mpl::type_list< BOOST_MPL_LIST_PARAMETERS(A) >::type
{};

}} // namespace boost::python

# else // slow template instantiators need this other version with
       // explicit specializations of mpl::size<> and
       // mpl::at<>. Eventually, however, inheritance from mpl::list
       // *should* be eliminated and the two versions unified, just in
       // order to get true arity independence

namespace boost { namespace python { 

template < BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PYTHON_MAX_ARITY, class A, boost::mpl::null_argument) >
struct args
{};

}} // namespace boost::python

namespace boost { namespace mpl {

template <class T> struct size;
template <long N, class Seq> struct at;

#  ifndef BOOST_PYTHON_GENERATE_CODE
#   include <boost/python/preprocessed/args.hpp>
#  endif

#  define BOOST_PYTHON_ARGS_SIZE(index,ignored)                       \
template <BOOST_PP_ENUM_PARAMS(index, class A)>                                 \
struct size<boost::python::args<BOOST_PP_ENUM_PARAMS(index, A)> >               \
{                                                                               \
    BOOST_STATIC_CONSTANT(long, value = index);                                 \
};                                                                              \

BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_ARGS_SIZE, nil)
    
#  define BOOST_PYTHON_ARGS_AT(index,ignored)                       \
template <                                                                      \
    BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_PYTHON_ARITY_FINISH), class A)>     \
struct at<index, boost::python::args<                                           \
    BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_PYTHON_ARITY_FINISH), A)> >         \
{                                                                               \
    typedef BOOST_PP_CAT(A,index) type;                                         \
};                                                                              \

BOOST_PP_REPEAT_FROM_TO_2ND( 
    BOOST_PP_DEC(BOOST_PYTHON_ARITY_START), BOOST_PP_DEC(BOOST_PYTHON_ARITY_FINISH) 
    , BOOST_PYTHON_ARGS_AT, data)
    
}}
# endif 
#endif // ARGS_DWA2002323_HPP
