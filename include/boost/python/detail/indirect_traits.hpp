// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef INDIRECT_TRAITS_DWA2002131_HPP
# define INDIRECT_TRAITS_DWA2002131_HPP
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/mpl/select_type.hpp>

namespace boost { namespace python { namespace detail { 

#  ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct is_reference_to_const
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_reference_to_const<T const&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class T>
struct is_reference_to_non_const
{
    BOOST_STATIC_CONSTANT(
        bool, value = (
            ::boost::type_traits::ice_and<
            ::boost::is_reference<T>::value
            , ::boost::type_traits::ice_not<
                ::boost::python::detail::is_reference_to_const<T>::value>::value
            >::value)
        );
};

template <class T>
struct is_reference_to_volatile
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_reference_to_volatile<T volatile&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class T>
struct is_reference_to_pointer
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_reference_to_pointer<T*&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class T>
struct is_reference_to_pointer<T* const&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class T>
struct is_reference_to_pointer<T* volatile&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class T>
struct is_reference_to_pointer<T* const volatile&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};
#  else

typedef char (&inner_yes_type)[3];
typedef char (&inner_no_type)[2];
typedef char (&outer_no_type)[1];

template <typename V>
struct is_const_help
{
    typedef typename mpl::select_type<
        is_const<V>::value
        , inner_yes_type
        , inner_no_type
        >::type type;
};

template <typename V>
struct is_volatile_help
{
    typedef typename mpl::select_type<
        is_volatile<V>::value
        , inner_yes_type
        , inner_no_type
        >::type type;
};

template <typename V>
struct is_pointer_help
{
    typedef typename mpl::select_type<
        is_pointer<V>::value
        , inner_yes_type
        , inner_no_type
        >::type type;
};

template <typename V>
typename is_const_help<V>::type reference_to_const_helper(V&);    
outer_no_type
reference_to_const_helper(...);

template <class T>
struct is_reference_to_const
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = (is_reference<T>::value
           && sizeof(reference_to_const_helper(t)) == sizeof(inner_yes_type)));
};

template <class T>
struct is_reference_to_non_const
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = (is_reference<T>::value
           && sizeof(reference_to_const_helper(t)) == sizeof(inner_no_type)));
};

template <typename V>
typename is_volatile_help<V>::type reference_to_volatile_helper(V&);
outer_no_type reference_to_volatile_helper(...);

template <class T>
struct is_reference_to_volatile
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = (is_reference<T>::value
           && sizeof(reference_to_volatile_helper(t)) == sizeof(inner_yes_type)));
};


template <typename V>
typename is_pointer_help<V>::type reference_to_pointer_helper(V&);
outer_no_type reference_to_pointer_helper(...);

template <class T>
struct is_reference_to_pointer
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = (is_reference<T>::value
           && sizeof(reference_to_pointer_helper(t)) == sizeof(inner_yes_type))
        );
};
#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION 

}}} // namespace boost::python::detail

#endif // INDIRECT_TRAITS_DWA2002131_HPP
