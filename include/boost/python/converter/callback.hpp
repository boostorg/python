// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLBACK_DWA2002228_HPP
# define CALLBACK_DWA2002228_HPP

# include <boost/python/converter/type_id.hpp>
# include <boost/python/converter/to_python_function.hpp>
# include <boost/python/converter/from_python.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/python/converter/callback_to_python_base.hpp>
# include <boost/python/converter/callback_from_python_base.hpp>
# include <boost/python/converter/builtin_converters.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{
  template <class T>
  struct pointer_callback_from_python
  {
      pointer_callback_from_python();
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct reference_callback_from_python
  {
      reference_callback_from_python();
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct rvalue_callback_from_python
  {
      rvalue_callback_from_python();
      T const& operator()(PyObject*);
   private:
      rvalue_data<T> m_data;
  };
  
  template <class T>
  struct select_callback_from_python
  {
      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
    
      BOOST_STATIC_CONSTANT(
          bool, ref = is_reference<T>::value);

      typedef typename mpl::select_type<
          ptr
          , pointer_callback_from_python<T>
          , typename mpl::select_type<
              ref
              , reference_callback_from_python<T>
              , rvalue_callback_from_python<T>
            >::type
          >::type type;
  };


  template <class T>
  struct reference_callback_to_python
  {
      
  };
}

template <class T>
struct callback_from_python
    : detail::select_callback_from_python<T>::type
{
};

template <class T>
struct callback_to_python : detail::callback_to_python_base
{
 public: // member functions
    // Throw an exception if the conversion can't succeed
    callback_to_python(T const&);
};

//
// Implementations
//
namespace detail
{
  template <class T>
  rvalue_callback_from_python<T>::rvalue_callback_from_python()
      : m_data(rvalue_from_python_chain<T>::value)
  {
      throw_if_not_registered(m_data.stage1);
  }
  
  template <class T>
  T const& rvalue_callback_from_python<T>::operator()(PyObject* obj)
  {
      return *(T*)convert_rvalue(obj, m_data.stage1, m_data.storage.bytes);
  }
}

template <class T>
callback_to_python<T>::callback_to_python(T const& x)
    : callback_to_python_base(&x, to_python_function<T>::value)
{
}

}}} // namespace boost::python::converter

#endif // CALLBACK_DWA2002228_HPP
