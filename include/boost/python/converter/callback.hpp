// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLBACK_DWA2002228_HPP
# define CALLBACK_DWA2002228_HPP

# include <boost/python/converter/type_id.hpp>
# include <boost/python/converter/to_python_function.hpp>
# include <boost/python/converter/pointee_to_python_function.hpp>
# include <boost/python/converter/from_python.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/python/converter/callback_to_python_base.hpp>
# include <boost/python/converter/callback_from_python_base.hpp>
# include <boost/python/converter/builtin_converters.hpp>
# include <boost/python/to_python_indirect.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/ptr.hpp>

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
  struct reference_callback_to_python : callback_to_python_holder
  {
      reference_callback_to_python(T& x);
   private:
      static PyObject* get_object(T& x);
  };

  template <class T>
  struct value_callback_to_python : callback_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      value_callback_to_python(T const&);
  };

  template <class Ptr>
  struct pointer_deep_callback_to_python : callback_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      pointer_deep_callback_to_python(Ptr);
  };

  template <class Ptr>
  struct pointer_shallow_callback_to_python : callback_to_python_holder
  {
      // Throw an exception if the conversion can't succeed
      pointer_shallow_callback_to_python(Ptr);
   private:
      static PyObject* get_object(Ptr p);
  };

  template <class T>
  struct select_callback_to_python
  {
      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
      
      BOOST_STATIC_CONSTANT(
          bool, ref_wrapper = is_reference_wrapper<T>::value);

      BOOST_STATIC_CONSTANT(
          bool, ptr_wrapper = is_pointer_wrapper<T>::value);

      typedef typename unwrap_reference<T>::type unwrapped_referent;
      typedef typename unwrap_pointer<T>::type unwrapped_ptr;

      typedef typename mpl::select_type<
          ptr
          , pointer_deep_callback_to_python<T>
          , typename mpl::select_type<
              ptr_wrapper
              , pointer_shallow_callback_to_python<unwrapped_ptr>
              , typename mpl::select_type<
                  ref_wrapper
                  , reference_callback_to_python<unwrapped_referent>
                  , value_callback_to_python<T>
                >::type
            >::type
        >::type type;
  };
}

template <class T>
struct callback_from_python
    : detail::select_callback_from_python<T>::type
{
};

template <class T>
struct callback_to_python
    : detail::select_callback_to_python<T>::type
{
    typedef typename detail::select_callback_to_python<T>::type base;
 public: // member functions
    // Throw an exception if the conversion can't succeed
    callback_to_python(T const& x);
};

//
// Implementations
//
namespace detail
{
  template <class T>
  inline rvalue_callback_from_python<T>::rvalue_callback_from_python()
      : m_data(rvalue_from_python_chain<T>::value)
  {
      throw_if_not_registered(m_data.stage1);
  }
  
  template <class T>
  inline T const& rvalue_callback_from_python<T>::operator()(PyObject* obj)
  {
      return *(T*)convert_rvalue(obj, m_data.stage1, m_data.storage.bytes);
  }

  BOOST_PYTHON_DECL void throw_no_class_registered();

  template <class T>
  inline reference_callback_from_python<T>::reference_callback_from_python()
  {
      detail::throw_if_not_registered(lvalue_from_python_chain<T,true>::value);
  }
  
  template <class T>
  inline T reference_callback_from_python<T>::operator()(PyObject* obj) const
  {
      return python::detail::void_ptr_to_reference(
          callback_convert_reference(obj, lvalue_from_python_chain<T,true>::value)
          , (T(*)())0);
  }

  template <class T>
  inline pointer_callback_from_python<T>::pointer_callback_from_python()
  {
      detail::throw_if_not_registered(lvalue_from_python_chain<T,true>::value);
  }
  
  template <class T>
  inline T pointer_callback_from_python<T>::operator()(PyObject* obj) const
  {
      return T(callback_convert_pointer(obj, lvalue_from_python_chain<T,true>::value));
  }

  template <class T>
  inline value_callback_to_python<T>::value_callback_to_python(T const& x)
      : callback_to_python_base(&x, to_python_function<T>::value)
  {
  }

  template <class Ptr>
  inline pointer_deep_callback_to_python<Ptr>::pointer_deep_callback_to_python(Ptr x)
      : callback_to_python_base(x, pointee_to_python_function<Ptr>::value)
  {
  }

  template <class T>
  inline PyObject* reference_callback_to_python<T>::get_object(T& x)
  {
      to_python_indirect<T&,python::detail::make_reference_holder> convert;
      if (!convert.convertible())
          throw_no_class_registered();
      return convert(x);
  }

  template <class T>
  inline reference_callback_to_python<T>::reference_callback_to_python(T& x)
      : callback_to_python_holder(get_object(x))
  {
  }

  template <class Ptr>
  inline pointer_shallow_callback_to_python<Ptr>::pointer_shallow_callback_to_python(Ptr x)
      : callback_to_python_holder(get_object(x))
  {}

  template <class Ptr>
  inline PyObject* pointer_shallow_callback_to_python<Ptr>::get_object(Ptr x)
  {
      to_python_indirect<Ptr,python::detail::make_reference_holder> convert;
      if (!convert.convertible())
          throw_no_class_registered();
      return x ? convert(x) : python::detail::none();
  }
}

template <class T>
inline callback_to_python<T>::callback_to_python(T const& x)
    : base(x)
{}

}}} // namespace boost::python::converter

#endif // CALLBACK_DWA2002228_HPP
