// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARGS_DWA2002323_HPP
# define ARGS_DWA2002323_HPP
#  include <boost/config.hpp>
#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/python/detail/type_list.hpp>
#  include <boost/preprocessor/enum_params.hpp>

namespace boost { namespace python {

enum no_init_t { no_init };

namespace detail
{
  template <class Args>
  struct args_base {};
}
}}

namespace boost { namespace python {

// A type list for specifying arguments
template < BOOST_PYTHON_ENUM_WITH_DEFAULT(BOOST_PYTHON_MAX_ARITY, typename A, mpl::void_) >
struct args : detail::args_base<args<BOOST_PP_ENUM_PARAMS_Z(1, BOOST_PYTHON_MAX_ARITY, A)> >
      , detail::type_list< BOOST_PP_ENUM_PARAMS_Z(1, BOOST_PYTHON_MAX_ARITY, A) >::type
{};

}} // namespace boost::python


# endif // ARGS_DWA2002323_HPP
