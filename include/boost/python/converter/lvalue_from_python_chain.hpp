// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef LVALUE_FROM_PYTHON_CHAIN_DWA200237_HPP
# define LVALUE_FROM_PYTHON_CHAIN_DWA200237_HPP

# include <boost/python/converter/pointer_type_id.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/type_traits/cv_traits.hpp>

namespace boost { namespace python { namespace converter { 

// Given T == U*cv&, T == U*, or T == U&, lvalue_from_python_chain<T>
// declares a "templated global reference" to the lvalue from_python
// converter chain for U. The optional bool second argument callback,
// when true, removes special treatment for T == U*cv& so that the
// converter for U* is found.
namespace detail
{
  template <class T>
  struct ptr_or_ptr_ref_lvalue_from_python_chain
  {
      static lvalue_from_python_registration*const& value;
  };
    
  template <class T>
  lvalue_from_python_registration*const&
  ptr_or_ptr_ref_lvalue_from_python_chain<T>::value
     = registry::lvalue_converters(pointer_type_id<T>());

  template <class T>
  struct ref_lvalue_from_python_chain
  {
      static lvalue_from_python_registration*const& value;
  };

  template <class T>
  lvalue_from_python_registration*const&
  ref_lvalue_from_python_chain<T>::value
     = registry::lvalue_converters(undecorated_type_id<T>());

  template <class T, bool callback>
  struct select_lvalue_from_python_chain
  {
      BOOST_STATIC_CONSTANT(
          bool, ptr
          = !callback && boost::python::detail::is_reference_to_pointer<T>::value
            || is_pointer<T>::value);

      typedef typename add_reference<typename add_cv<T>::type>::type normalized;

      typedef typename mpl::select_if_c<
          ptr
          , ptr_or_ptr_ref_lvalue_from_python_chain<normalized>
          , ref_lvalue_from_python_chain<normalized>
          >::type type;
  };
}

template <class T, bool callback = false>
struct lvalue_from_python_chain
    : detail::select_lvalue_from_python_chain<T,callback>::type
{
};

}}} // namespace boost::python::converter

#endif // LVALUE_FROM_PYTHON_CHAIN_DWA200237_HPP
