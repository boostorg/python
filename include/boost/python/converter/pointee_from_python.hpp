// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef POINTEE_FROM_PYTHON_DWA2002710_HPP
# define POINTEE_FROM_PYTHON_DWA2002710_HPP
# include <boost/python/converter/from_python.hpp>
# include <boost/python/converter/pointer_type_id.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>

namespace boost { namespace python { namespace converter { 

struct from_python_registration;

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct pointee_from_python
    : from_python<
        typename remove_pointer<
           typename remove_cv<
              typename remove_reference<T>::type
           >::type
        >::type
    >
{
};
# else
namespace detail
{
  template <class T>
  struct pointee_from_python_base
  {
      static from_python_registration const& converters;
  };
}

template <class T>
struct pointee_from_python
    : detail::pointee_from_python_base<
        typename add_reference<
           typename add_cv<T>::type
        >::type
    >
{
};

//
// implementations
//
namespace detail
{
  template <class T>
  from_python_registration const& pointee_from_python_base<T>::converters
     = registry::from_python_converters(pointer_type_id<T>());
}

# endif 
}}} // namespace boost::python::converter

#endif // POINTEE_FROM_PYTHON_DWA2002710_HPP
