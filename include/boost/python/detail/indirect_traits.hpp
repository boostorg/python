// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef INDIRECT_TRAITS_DWA2002131_HPP
# define INDIRECT_TRAITS_DWA2002131_HPP
# include <boost/type_traits/is_function.hpp>
# include <boost/type_traits/detail/ice_and.hpp>
# include <boost/type_traits/is_reference.hpp>
# include <boost/type_traits/is_pointer.hpp>
# include <boost/type_traits/is_class.hpp>
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/is_volatile.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/type_traits/remove_pointer.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/bool_c.hpp>
# include <boost/mpl/aux_/lambda_support.hpp>

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

#   if defined(BOOST_MSVC) && _MSC_FULL_VER <= 13102140 // vc7.01 alpha workaround
template<class T>
struct is_reference_to_const<T const volatile&>
{
    static const bool value = true;
};
#   endif 

#   if 0 // Corresponding code doesn't work on MSVC yet
template <class T>
struct is_reference_to_function
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_reference_to_function<T&>
{
    BOOST_STATIC_CONSTANT(bool, value = is_function<T>::value);
};

template <class T>
struct is_reference_to_function<T const&>
{
    BOOST_STATIC_CONSTANT(bool, value = is_function<T>::value);
};

template <class T>
struct is_reference_to_function<T volatile&>
{
    BOOST_STATIC_CONSTANT(bool, value = is_function<T>::value);
};

template <class T>
struct is_reference_to_function<T const volatile&>
{
    BOOST_STATIC_CONSTANT(bool, value = is_function<T>::value);
};
#   endif

template <class T>
struct is_pointer_to_function
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_pointer_to_function<T*>
{
    // There's no such thing as a pointer-to-cv-function, so we don't need specializations for those
    BOOST_STATIC_CONSTANT(bool, value = is_function<T>::value);
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

#   if defined(BOOST_MSVC) && _MSC_FULL_VER <= 13102140 // vc7.01 alpha workaround
template <class T>
struct is_reference_to_volatile<T const volatile&>
{
    static const bool value = true;
};
#   endif 


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

template <class T>
struct is_reference_to_class
{
    BOOST_STATIC_CONSTANT(
        bool, value
        = (boost::type_traits::ice_and<
           is_reference<T>::value
           , is_class<
                typename remove_cv<
                    typename remove_reference<T>::type
                >::type
             >::value
         >::value)
        );
    typedef mpl::bool_c<value> type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_reference_to_class,(T))
};

template <class T>
struct is_pointer_to_class
{
    BOOST_STATIC_CONSTANT(
        bool, value
        = (boost::type_traits::ice_and<
           is_pointer<T>::value
           , is_class<
                typename remove_cv<
                    typename remove_pointer<T>::type
                >::type
             >::value
         >::value)
        );
};

#  else

typedef char (&inner_yes_type)[3];
typedef char (&inner_no_type)[2];
typedef char (&outer_no_type)[1];

template <typename V>
struct is_const_help
{
    typedef typename mpl::if_c<
        is_const<V>::value
        , inner_yes_type
        , inner_no_type
        >::type type;
};

template <typename V>
struct is_volatile_help
{
    typedef typename mpl::if_c<
        is_volatile<V>::value
        , inner_yes_type
        , inner_no_type
        >::type type;
};

template <typename V>
struct is_pointer_help
{
    typedef typename mpl::if_c<
        is_pointer<V>::value
        , inner_yes_type
        , inner_no_type
        >::type type;
};

template <typename V>
struct is_class_help
{
    typedef typename mpl::if_c<
        is_class<V>::value
        , inner_yes_type
        , inner_no_type
        >::type type;
};

#   if 0 // doesn't seem to work yet
template <class T>
struct is_reference_to_function
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = sizeof(::boost::type_traits::is_function_ptr_tester(t)) == sizeof(::boost::type_traits::yes_type));
#   endif

template <class T>
struct is_pointer_to_function
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = sizeof(::boost::type_traits::is_function_ptr_tester(t)) == sizeof(::boost::type_traits::yes_type));
};

struct false_helper1
{
    template <class T>
    struct apply
    {
        BOOST_STATIC_CONSTANT(bool, value = false);
    };
};

template <typename V>
typename is_const_help<V>::type reference_to_const_helper(V&);    
outer_no_type
reference_to_const_helper(...);

template <bool ref = true>
struct is_reference_to_const_helper1
{
    template <class T>
    struct apply
    {
        static T t;
        BOOST_STATIC_CONSTANT(
            bool, value
            = sizeof(reference_to_const_helper(t)) == sizeof(inner_yes_type));
    };
};

template <>
struct is_reference_to_const_helper1<false> : false_helper1
{
};


template <class T>
struct is_reference_to_const
    : is_reference_to_const_helper1<is_reference<T>::value>::template apply<T>
{
};



template <bool ref = true>
struct is_reference_to_non_const_helper1
{
    template <class T>
    struct apply
    {
        static T t;
        BOOST_STATIC_CONSTANT(
            bool, value
            = sizeof(reference_to_const_helper(t)) == sizeof(inner_no_type));
    };
};

template <>
struct is_reference_to_non_const_helper1<false> : false_helper1
{
};


template <class T>
struct is_reference_to_non_const
    : is_reference_to_non_const_helper1<is_reference<T>::value>::template apply<T>
{
};


template <typename V>
typename is_volatile_help<V>::type reference_to_volatile_helper(V&);    
outer_no_type
reference_to_volatile_helper(...);

template <bool ref = true>
struct is_reference_to_volatile_helper1
{
    template <class T>
    struct apply
    {
        static T t;
        BOOST_STATIC_CONSTANT(
            bool, value
            = sizeof(reference_to_volatile_helper(t)) == sizeof(inner_yes_type));
    };
};

template <>
struct is_reference_to_volatile_helper1<false> : false_helper1
{
};


template <class T>
struct is_reference_to_volatile
    : is_reference_to_volatile_helper1<is_reference<T>::value>::template apply<T>
{
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

template <typename V>
typename is_class_help<V>::type reference_to_class_helper(V const volatile&);
outer_no_type reference_to_class_helper(...);

template <class T>
struct is_reference_to_class
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = (is_reference<T>::value
           & (sizeof(reference_to_class_helper(t)) == sizeof(inner_yes_type)))
        );
    typedef mpl::bool_c<value> type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_reference_to_class,(T))
};

template <typename V>
typename is_class_help<V>::type pointer_to_class_helper(V const volatile*);
outer_no_type pointer_to_class_helper(...);

template <class T>
struct is_pointer_to_class
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = (is_pointer<T>::value
           && sizeof(pointer_to_class_helper(t)) == sizeof(inner_yes_type))
        );
};
#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION 

}}} // namespace boost::python::detail

#endif // INDIRECT_TRAITS_DWA2002131_HPP
