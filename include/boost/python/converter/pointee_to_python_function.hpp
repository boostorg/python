// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef POINTEE_TO_PYTHON_FUNCTION_DWA2002128_HPP
# define POINTEE_TO_PYTHON_FUNCTION_DWA2002128_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/converter/to_python_function_type.hpp>
# include <boost/python/converter/pointer_type_id.hpp>

namespace boost { namespace python { namespace converter { 

// pointee_to_python_function --
//
// essentially a "templated global reference" which holds the
// converter for converting a type to Python by-value. We "normalize"
// T by adding "const volatile&" so that fewer global variables and
// associated static initializations are generated.
namespace detail
{
  template <class T>
  struct pointee_to_python_function_base
  {
      static to_python_function_t const& value;
  };
  
  template <class T>
  to_python_function_t const&
  pointee_to_python_function_base<T>::value
        = converter::registry::get_to_python_function(pointer_type_id<T>());
}

template <class T>
struct pointee_to_python_function
    : detail::pointee_to_python_function_base<
        typename add_reference<
          typename add_cv<T>::type
        >::type
      >
{
};

}}} // namespace boost::python::converter

#endif // POINTEE_TO_PYTHON_FUNCTION_DWA2002128_HPP
