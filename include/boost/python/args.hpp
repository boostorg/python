// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARGS_DWA2002323_HPP
# define ARGS_DWA2002323_HPP
# include <boost/mpl/type_list.hpp>

namespace boost { namespace python { 

// A type list for specifying arguments
template < BOOST_MPL_LIST_DEFAULT_PARAMETERS(typename A, ::boost::mpl::null_argument) >
struct args : ::boost::mpl::type_list< BOOST_MPL_LIST_PARAMETERS(A) >::type
{};

}} // namespace boost::python

#endif // ARGS_DWA2002323_HPP
