// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_FWD_DWA200222_HPP
# define CLASS_FWD_DWA200222_HPP
# include <boost/python/detail/not_specified.hpp>
# include <boost/python/args.hpp>
# include <boost/python/bases.hpp>

namespace boost { namespace python { 

namespace detail
{
  struct empty_list;
}

template <
    class T // class being wrapped
    , class X1 = detail::not_specified
    , class X2 = detail::not_specified
    , class X3 = detail::not_specified
    >
class class_;

}} // namespace boost::python

#endif // CLASS_FWD_DWA200222_HPP
