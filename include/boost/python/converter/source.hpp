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

template <class T>
struct source
{
    BOOST_STATIC_CONSTANT(bool, use_identity = (::boost::is_pointer<T>::value));

    typedef typename mpl::select_type<
        use_identity
        , T
        , typename add_reference<
                typename add_const<T>::type
          >::type
    >::type type;
};

}}} // namespace boost::python::converter

#endif // SOURCE_DWA20011119_HPP
