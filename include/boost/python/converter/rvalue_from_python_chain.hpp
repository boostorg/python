// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef RVALUE_FROM_PYTHON_CHAIN_DWA200237_HPP
# define RVALUE_FROM_PYTHON_CHAIN_DWA200237_HPP
# include <boost/python/converter/registry.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{
  template <class T>
  struct rvalue_from_python_chain_impl
  {
      static rvalue_from_python_registration*const& value;
  };

  template <class T>
  rvalue_from_python_registration*const& rvalue_from_python_chain_impl<T>::value
      = registry::rvalue_converters(undecorated_type_id<T>());
}

template <class T>
struct rvalue_from_python_chain
    : detail::rvalue_from_python_chain_impl<
        typename add_reference<
          typename add_cv<T>::type
        >::type
      >
{
};

}}} // namespace boost::python::converter

#endif // RVALUE_FROM_PYTHON_CHAIN_DWA200237_HPP
