// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_DWA2002710_HPP
# define FROM_PYTHON_DWA2002710_HPP
# include <boost/python/type_id.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>

namespace boost { namespace python { namespace converter { 

struct from_python_registration;

namespace detail
{
  template <class T>
  struct from_python_base
  {
      static from_python_registration const& converters;
  };
}

template <class T>
struct from_python
    : detail::from_python_base<
        typename add_reference<
           typename add_cv<T>::type
        >::type
    >
{
};

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
// collapses a few more types to the same static instance
template <class T>
struct from_python<T&> : from_python<T> {};
# endif

//
// implementations
//
namespace detail
{
  template <class T>
  from_python_registration const& from_python_base<T>::converters
     = registry::from_python_converters(type_id<T>());
}
}}} // namespace boost::python::converter

#endif // FROM_PYTHON_DWA2002710_HPP
