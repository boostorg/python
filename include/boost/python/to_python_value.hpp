// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_VALUE_DWA200221_HPP
# define TO_PYTHON_VALUE_DWA200221_HPP

# include <boost/type_traits/transform_traits.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/converter/builtin_converters.hpp>
# include <boost/python/converter/object_manager.hpp>
# include <boost/mpl/if.hpp>
# include <boost/type_traits/ice.hpp>
# include <boost/python/refcount.hpp>
# include <boost/python/tag.hpp>

namespace boost { namespace python { 

namespace detail
{
  template <class T>
  struct object_manager_to_python_value
  {
      typedef typename add_reference<
          typename add_const<T>::type
      >::type argument_type;
    
      static bool convertible();
      PyObject* operator()(argument_type) const;
  };

  
  template <class T>
  struct registry_to_python_value
  {
      typedef typename add_reference<
          typename add_const<T>::type
      >::type argument_type;
    
      static bool convertible();
      PyObject* operator()(argument_type) const;
  };
}

template <class T>
struct to_python_value
    : mpl::if_c<
          boost::type_traits::ice_or<
              converter::is_object_manager<T>::value
            , converter::is_reference_to_object_manager<T>::value
            >::value

        , detail::object_manager_to_python_value<T>
        , detail::registry_to_python_value<T>
      >::type
{
};

//
// implementation 
//
namespace detail
{
  template <class T>
  inline bool registry_to_python_value<T>::convertible()
  {
      return converter::registered<argument_type>::converters.to_python != 0;
  }

  template <class T>
  inline PyObject* registry_to_python_value<T>::operator()(argument_type x) const
  {
      return converter::registered<argument_type>::converters.to_python(&x);
  }

  template <class T>
  inline bool object_manager_to_python_value<T>::convertible()
  {
      return true;
  }

  template <class T>
  inline PyObject* object_manager_to_python_value<T>::operator()(argument_type x) const
  {
      return python::upcast<PyObject>(
          python::xincref(
              get_managed_object(x, tag))
          );
  }
}

}} // namespace boost::python

#endif // TO_PYTHON_VALUE_DWA200221_HPP
