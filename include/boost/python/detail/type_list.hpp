// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TYPE_LIST_DWA200222_HPP
# define TYPE_LIST_DWA200222_HPP
# include <boost/mpl/type_list.hpp>

namespace boost { namespace python { namespace detail { 

struct empty_list : boost::mpl::type_list<>::type {};

}}} // namespace boost::python::detail

#endif // TYPE_LIST_DWA200222_HPP
