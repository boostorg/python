//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

#ifndef TARGET_DWA20011119_HPP
# define TARGET_DWA20011119_HPP
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/object_traits.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/same_traits.hpp>

namespace boost { namespace python { namespace converter {

// target --
//
//    This type generator (see
//    ../../../more/generic_programming.html#type_generator) is used
//    to select the return type of the appropriate converter for
//    unwrapping a given type.

// Strategy:
//
// 1. reduce everything to a common, un-cv-qualified reference
//    type where possible. This will save on registering many different
//    converter types.
//
// 2. Treat built-in types specially: when unwrapping a value or
//    constant reference to one of these, use a value for the target
//    type. It will bind to a const reference if neccessary, and more
//    importantly, avoids having to dynamically allocate room for
//    an lvalue of types which can be cheaply copied.
//

// Target                Source
// int                   int
// int const&            int
// int&                  int&
// int volatile&         int volatile&
// int const volatile&   int const volatile&

// On compilers supporting partial specialization:
//
// Target                Source
// T                     T const&
// T&                    T&
// T const&              T const&
// T volatile            T&
// T const volatile&     T const&
// T*                    T*
// T const*              T const*
// T volatile            T*
// T const volatile*     T const*
// T cv*const&           same as T cv*
// T cv*&                T*& <- should this be legal?
// T cv*volatile&        T*& <- should this be legal?
// T cv*const volatile&  T*& <- should this be legal?

// On others:
//
// Target                Source
// T                     T&
// T cv&                 T cv&
// T cv*                 T cv*
// T cv*cv&              T cv*cv&

// As you can see, in order to handle the same range of types without
// partial specialization, more converters need to be registered.

template <class T>
struct target
{
    // Some pointer types are handled in a more sophisticated way on
    // compilers supporting partial specialization.
    BOOST_STATIC_CONSTANT(bool, use_identity = (::boost::is_scalar<T>::value));

    typedef typename mpl::select_type<
        use_identity
        , T
        , typename add_reference<
                typename add_const<
                        typename remove_volatile<T>::type
                >::type
          >::type
    >::type type;
};

// When partial specialization is not present, we'll simply need to
// register many more converters.
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template <class T>
struct target<T&>
{
    typedef typename remove_volatile<T>::type& type;
};

template <class T>
struct target<T const&>
{
    typedef typename boost::mpl::select_type<
        is_scalar<T>::value
        , typename remove_cv<T>::type
        , typename remove_volatile<T>::type const&
    >::type type;
};

template <class T>
struct target<T*>
{
    typedef typename remove_volatile<T>::type* type;
};

// Handle T*-cv for completeness. Function arguments in a signature
// are never actually cv-qualified, but who knows how these converters
// might be used, or whether compiler bugs lurk which make it seem
// otherwise?
template <class T>
struct target<T* const>
{
    typedef typename remove_volatile<T>::type* type;
};

template <class T>
struct target<T* volatile>
{
    typedef typename remove_volatile<T>::type* type;
};

template <class T>
struct target<T* const volatile>
{
    typedef typename remove_volatile<T>::type* type;
};

// non-const references to pointers should be handled by the
// specialization for T&, above.
template <class T>
struct target<T* const&>
{
    typedef typename remove_volatile<T>::type* type;
};
# endif

// Fortunately, we can handle T const& where T is an arithmetic type
// by explicit specialization. These specializations will cause value
// and const& arguments to be converted to values, rather than to
// references.
# define  BOOST_PYTHON_UNWRAP_VALUE(T)  \
template <>                             \
struct target<T>                        \
{                                       \
    typedef T type;                     \
};                                      \
template <>                             \
struct target<T const>                  \
{                                       \
    typedef T type;                     \
};                                      \
template <>                             \
struct target<T volatile>               \
{                                       \
    typedef T type;                     \
};                                      \
template <>                             \
struct target<T const volatile>         \
{                                       \
    typedef T type;                     \
};                                      \
template <>                             \
struct target<T const&>                 \
{                                       \
    typedef T type;                     \
}

BOOST_PYTHON_UNWRAP_VALUE(char);
BOOST_PYTHON_UNWRAP_VALUE(unsigned char);
BOOST_PYTHON_UNWRAP_VALUE(signed char);
BOOST_PYTHON_UNWRAP_VALUE(unsigned int);
BOOST_PYTHON_UNWRAP_VALUE(signed int);
BOOST_PYTHON_UNWRAP_VALUE(unsigned short);
BOOST_PYTHON_UNWRAP_VALUE(signed short);
BOOST_PYTHON_UNWRAP_VALUE(unsigned long);
BOOST_PYTHON_UNWRAP_VALUE(signed long);
BOOST_PYTHON_UNWRAP_VALUE(char const*);

}}} // namespace boost::python::converter

#endif // TARGET_DWA20011119_HPP
