#error obsolete
// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TYPE_LIST_UTILS_JDG20020826_HPP
# define TYPE_LIST_UTILS_JDG20020826_HPP


#  ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost { namespace python { namespace detail {

template< typename T >
struct is_list_arg
{
    enum { value = true };
};

template<>
struct is_list_arg<mpl::void_>
{
    enum { value = false };
};

}}}
#  endif 
#endif // TYPE_LIST_UTILS_JDG20020826_HPP
