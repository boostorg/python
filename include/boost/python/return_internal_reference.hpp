// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef RETURN_INTERNAL_REFERENCE_DWA2002131_HPP
# define RETURN_INTERNAL_REFERENCE_DWA2002131_HPP

# include <boost/python/default_call_policies.hpp>
# include <boost/type_traits/object_traits.hpp>
# include <boost/python/reference_existing_object.hpp>
# include <boost/python/to_python_indirect.hpp>
# include <boost/python/with_custodian_and_ward.hpp>

namespace boost { namespace python { 

namespace detail
{
  template <class T>
  struct return_internal_reference_requires_a_pointer_or_reference_return_type
# if defined(__GNUC__) && __GNUC__ >= 3 || defined(__EDG__)
  {}
# endif
  ;
}

struct internal_reference_to_python_generator
{
    template <class T>
    struct apply
    {
        typedef typename mpl::select_type<
            is_object<T>::value
            , detail::return_internal_reference_requires_a_pointer_or_reference_return_type<T>
            , to_python_indirect<T, detail::make_reference_holder>
        >::type type;
    };
};

template <std::size_t owner_arg = 1, class Base = default_call_policies>
struct return_internal_reference
    : with_custodian_and_ward_postcall<0, owner_arg, Base>
{
    typedef reference_existing_object result_converter;
};

}} // namespace boost::python

#endif // RETURN_INTERNAL_REFERENCE_DWA2002131_HPP
