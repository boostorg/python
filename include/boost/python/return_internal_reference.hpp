// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef RETURN_INTERNAL_REFERENCE_DWA2002131_HPP
# define RETURN_INTERNAL_REFERENCE_DWA2002131_HPP

# include <boost/python/default_call_policies.hpp>
# include <boost/type_traits/object_traits.hpp>

namespace boost { namespace python { 

namespace detail
{
  template <class T>
  struct return_internal_reference_requires_a_pointer_or_reference_return_type
# if defined(__GNUC__) && __GNUC__ >= 3 || defined(__EDG__)
  {}
# endif
  ;
};

struct internal_reference_to_python_generator
{
    template <class T>
    struct apply
    {
        typedef typename mpl::select_type<
            !is_object<T>::value
            , internal_reference_to_python<T>
            , detail::return_internal_reference_requires_a_pointer_or_reference_return_type
        >::type type;
    };
};

template <std::size_t owner_arg, class Base = default_call_policies>
struct return_internal_reference : Base
{
    typedef wrap_internal_reference<owner_arg> result_converter;
};

}} // namespace boost::python

#endif // RETURN_INTERNAL_REFERENCE_DWA2002131_HPP
