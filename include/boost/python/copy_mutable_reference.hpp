// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef COPY_MUTABLE_REFERENCE_DWA2002131_HPP
# define COPY_MUTABLE_REFERENCE_DWA2002131_HPP
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/mpl/select_if.hpp>
# include <boost/python/to_python_value.hpp>

namespace boost { namespace python { 

namespace detail
{
  template <class R>
  struct copy_mutable_reference_expects_a_reference_to_non_const_return_type
# if defined(__GNUC__) && __GNUC__ >= 3 || defined(__EDG__)
  {}
# endif
  ;
}

template <class T> struct to_python_value;

struct copy_mutable_reference
{
    template <class T>
    struct apply
    {
        typedef typename mpl::select_if_c<
            detail::is_reference_to_non_const<T>::value
            , to_python_value<T>
            , detail::copy_mutable_reference_expects_a_reference_to_non_const_return_type<T>
        >::type type;
    };
};

}} // namespace boost::python

#endif // COPY_MUTABLE_REFERENCE_DWA2002131_HPP
