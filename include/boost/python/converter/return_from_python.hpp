// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef RETURN_FROM_PYTHON_DWA200265_HPP
# define RETURN_FROM_PYTHON_DWA200265_HPP

# include <boost/python/converter/callback_from_python_base.hpp>
# include <boost/python/converter/from_python_data.hpp>
# include <boost/python/converter/rvalue_from_python_chain.hpp>
# include <boost/python/converter/lvalue_from_python_chain.hpp>
# include <boost/python/detail/void_ptr.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{
  template <class T>
  struct return_pointer_from_python
  {
      return_pointer_from_python();
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct return_reference_from_python
  {
      return_reference_from_python();
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct return_rvalue_from_python
  {
      return_rvalue_from_python();
      T const& operator()(PyObject*);
   private:
      rvalue_data<T> m_data;
  };
  
  template <class T>
  struct select_return_from_python
  {
      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
    
      BOOST_STATIC_CONSTANT(
          bool, ref = is_reference<T>::value);

      typedef typename mpl::select_type<
          ptr
          , return_pointer_from_python<T>
          , typename mpl::select_type<
              ref
              , return_reference_from_python<T>
              , return_rvalue_from_python<T>
            >::type
          >::type type;
  };
}

template <class T>
struct return_from_python
    : detail::select_return_from_python<T>::type
{
    typedef T result_type;
};

struct void_result
{
 private: 
    void_result() {}
    void operator=(void_result const&);
    
    friend struct return_from_python<void>;
};

// Specialization as a convenience for call and call_method
template <>
struct return_from_python<void>
{
    typedef void_result result_type;
    result_type operator()(PyObject* x) const
    {
        Py_DECREF(expect_non_null(x));
        return result_type();
    }
};

//
// Implementations
//
namespace detail
{
  template <class T>
  inline return_rvalue_from_python<T>::return_rvalue_from_python()
      : m_data(rvalue_from_python_chain<T>::value)
  {
      throw_if_not_registered(m_data.stage1);
  }
  
  template <class T>
  inline T const& return_rvalue_from_python<T>::operator()(PyObject* obj)
  {
      return *(T*)convert_rvalue(obj, m_data.stage1, m_data.storage.bytes);
  }

  template <class T>
  inline return_reference_from_python<T>::return_reference_from_python()
  {
      detail::throw_if_not_registered(lvalue_from_python_chain<T,true>::value);
  }
  
  template <class T>
  inline T return_reference_from_python<T>::operator()(PyObject* obj) const
  {
      return python::detail::void_ptr_to_reference(
          callback_convert_reference(obj, lvalue_from_python_chain<T,true>::value)
          , (T(*)())0);
  }

  template <class T>
  inline return_pointer_from_python<T>::return_pointer_from_python()
  {
      detail::throw_if_not_registered(lvalue_from_python_chain<T,true>::value);
  }
  
  template <class T>
  inline T return_pointer_from_python<T>::operator()(PyObject* obj) const
  {
      return T(callback_convert_pointer(obj, lvalue_from_python_chain<T,true>::value));
  }
}
  
}}} // namespace boost::python::converter

#endif // RETURN_FROM_PYTHON_DWA200265_HPP
