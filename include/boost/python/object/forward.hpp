// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FORWARD_DWA20011215_HPP
# define FORWARD_DWA20011215_HPP

# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/object_traits.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/transform_traits.hpp>

namespace boost { namespace python { namespace objects { 

// A little metaprogram which selects the type to pass through an
// intermediate forwarding function when the destination argument type
// is T.
template <class T>
struct forward
{
    typedef typename mpl::select_type<
        is_scalar<T>::value | is_reference<T>::value
        , T
        , reference_wrapper<
                typename add_const<T>::type
          >
    >::type type;
};

}}} // namespace boost::python::objects

#endif // FORWARD_DWA20011215_HPP
