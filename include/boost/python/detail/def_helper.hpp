// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DEF_HELPER_DWA200287_HPP
# define DEF_HELPER_DWA200287_HPP

# include <boost/type_traits/ice.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/python/detail/string_literal.hpp>

namespace boost { namespace python { namespace detail { 

//
// def_helper<T> --
//
//      A helper for def() functions which determines how to interpret
//      an argument of type T which could be either CallPolicies or a
//      string literal representing a docstring.
//
//      Generates two static functions:
//
//        get_policy(x), where x is of type T, returns a policies
//        object: either a reference to x or default_call_policies()
//        if x is a string literal.
//
//        get_doc(x, s), where s convertible to char const*, returns x
//        if x is a string literal, s otherwise.

template <bool is_string = false>
struct def_helper_impl
{
    template <class P>
    static P const&
    get_policy(P const& x) { return x; }

    template <class P1, class P2>
    static P1 const&
    get_policy(P1 const& x, P2 const&) { return x; } // select left
      
    template <class P>
    static char const*
    get_doc(P const&, char const* doc) { return doc; } // select right
};

template <>
struct def_helper_impl<true>
{
    static python::default_call_policies
    get_policy(char const*)
    { return default_call_policies(); }

    template <class P1, class P2>
    static P2 const&
    get_policy(P1 const&, P2 const& y) { return y; } // select right

    template <class P>
    static char const*
    get_doc(char const* doc, P const&) // select left
    { return doc; }
};
  
template <class T>
struct def_helper
    : def_helper_impl<
    type_traits::ice_or<
    is_string_literal<T const>::value
    , is_same<T, char const*>::value
    , is_same<T, char*>::value
>::value
>
{};

}}} // namespace boost::python::detail

#endif // DEF_HELPER_DWA200287_HPP
