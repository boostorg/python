//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#ifndef SOURCE_DWA20011119_HPP
# define SOURCE_DWA20011119_HPP
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/mpl/select_type.hpp>

namespace boost { namespace python { namespace converter { 

// source --
//
//    This type generator (see
//    ../../../more/generic_programming.html#type_generator) is used
//    to select the argument type to use when converting T to a PyObject*

template <class T> struct source;

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// Since for some strange reason temporaries can't be bound to const
// volatile references (8.5.3/5 in the C++ standard), we cannot use a
// const volatile reference as the standard for values and references.
template <class T>
struct source
{
    typedef T const& type;
};

// This will handle the following:
//      T const volatile& -> T const volatile&
//      T volatile& -> T const volatile&
//      T const& -> T const&
//      T& -> T const&
template <class T>
struct source<T&>
{
    typedef T const& type;
};

template <class T>
struct source<T*>
{
    typedef T const* type;
};

template <class T>
struct source<T* const>
{
    typedef T const* type;
};

// Deal with references to pointers
template <class T>
struct source<T*&>
{
    typedef T const* type;
};

template <class T>
struct source<T* const&>
{
    typedef T const* type;
};
# else
template <class T>
struct source
{
    typedef typename add_reference<
        typename add_const<T>::type
    >::type type;
};
# endif

}}} // namespace boost::python::converter

#endif // SOURCE_DWA20011119_HPP
