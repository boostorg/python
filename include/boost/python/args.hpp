// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARGS_DWA2002323_HPP
# define ARGS_DWA2002323_HPP
# include <boost/mpl/list.hpp>
# include <boost/preprocessor/enum_params_with_a_default.hpp>
# include <boost/preprocessor/enum_params.hpp>

namespace boost { namespace python { 

// A type list for specifying arguments
template < BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_LIMIT_LIST_SIZE, typename A, ::boost::mpl::aux::none) >
struct args : ::boost::mpl::list< BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_LIST_SIZE,A) >::type
{};

}} // namespace boost::python

#endif // ARGS_DWA2002323_HPP
