// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef OBJECT_CORE_DWA2002615_HPP
# define OBJECT_CORE_DWA2002615_HPP
# include <boost/python/handle.hpp>
# include <boost/python/converter/arg_to_python.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/python/call.hpp>
# include <boost/preprocessor/max.hpp>
# include <boost/python/slice_nil.hpp>
# include <boost/python/detail/raw_pyobject.hpp>
# include <boost/python/refcount.hpp>
# include <boost/type.hpp>

namespace boost { namespace python { 

// Put this in an inner namespace so that the generalized operators won't take over
namespace api
{
  
// This file contains the definition of the object class and enough to
// construct/copy it, but not enough to do operations like
// attribute/item access or addition.

  template <class Policies> class proxy;
  
  struct const_attribute_policies;
  struct attribute_policies;
  struct const_item_policies;
  struct item_policies;
  struct const_slice_policies;
  struct slice_policies;

  typedef proxy<const_attribute_policies> const_object_attribute;
  typedef proxy<attribute_policies> object_attribute;
  typedef proxy<const_item_policies> const_object_item;
  typedef proxy<item_policies> object_item;
  typedef proxy<const_slice_policies> const_object_slice;
  typedef proxy<slice_policies> object_slice;

  //
  // is_proxy -- proxy type detection
  //
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <class T>
  struct is_proxy
  {
      BOOST_STATIC_CONSTANT(bool, value = false);
  };
  template <class T>
  struct is_proxy<proxy<T> >
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };
# else
  typedef char yes_proxy;
  typedef char (&no_proxy)[2];
  template <class T>
  yes_proxy is_proxy_helper(boost::type<proxy<T> >*);
  no_proxy is_proxy_helper(...);
  template <class T>
  struct is_proxy
  {
      BOOST_STATIC_CONSTANT(
          bool, value = (sizeof(is_proxy_helper((boost::type<T>*)0))
                         == sizeof(yes_proxy)));
  };
# endif 

  template <bool is_proxy>  struct object_initializer;
  
  // A way to turn a conrete type T into a type dependent on U. This
  // keeps conforming compilers from complaining about returning an
  // incomplete T from a template member function (which must be
  // defined in the class body to keep MSVC happy).
  template <class T, class U>
  struct dependent
  {
      typedef T type;
  };

  class object;
  typedef PyObject* (object::*bool_type)() const;
  
  template <class U>
  class object_operators
  {
   protected:
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1200
      typedef object const& object_cref;
# else 
      typedef object object_cref;
# endif
   public:
      // function call
      //
      object operator()() const;

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/object_call.hpp>
# endif

# define BOOST_PYTHON_OBJECT_CALL(nargs,ignored)                                                        \
      template <BOOST_PP_ENUM_PARAMS(nargs, class A)>                                                   \
      typename dependent<object,A0>::type                                                               \
      operator()(BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,const& a))) const                                  \
      {                                                                                                 \
          typedef typename dependent<object,A0>::type obj;                                              \
          U const& self = *static_cast<U const*>(this);                                                 \
          return call<obj>(converter::get_managed_object(self), BOOST_PP_ENUM_PARAMS(nargs, a));        \
      }

      BOOST_PP_REPEAT_FROM_TO_2ND(
          BOOST_PP_MAX(1, BOOST_PYTHON_ARITY_START), BOOST_PYTHON_ARITY_FINISH
          , BOOST_PYTHON_OBJECT_CALL, ignored)

      // truth value testing
      //
      operator bool_type() const;
      bool operator!() const; // needed for vc6

      // Attribute access
      //
      const_object_attribute attr(char const*) const;
      object_attribute attr(char const*);

      // item access
      //
      const_object_item operator[](object_cref) const;
      object_item operator[](object_cref);
    
      template <class T>
      const_object_item
      operator[](T const& key) const
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
          ;
# else 
      {
          return (*this)[object(key)];
      }
# endif 
    
      template <class T>
      object_item
      operator[](T const& key)
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
          ;
# else 
      {
          return (*this)[object(key)];
      }
# endif

      // slicing
      //
      const_object_slice slice(object_cref, object_cref) const;
      object_slice slice(object_cref, object_cref);

      const_object_slice slice(slice_nil, object_cref) const;
      object_slice slice(slice_nil, object_cref);
                             
      const_object_slice slice(object_cref, slice_nil) const;
      object_slice slice(object_cref, slice_nil);
                             
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
      template <class T, class V>
      const_object_slice
      slice(T const& start, V const& end) const;
    
      template <class T, class V>
      object_slice
      slice(T const& start, V const& end);

# else
      template <class T, class V>
      const_object_slice
      slice(T const& start, V const& end) const
      {
          return this->slice(
               slice_bound<T>::type(start)
              ,  slice_bound<V>::type(end));
      }
    
      template <class T, class V>
      object_slice
      slice(T const& start, V const& end)
      {
          return this->slice(
              slice_bound<T>::type(start)
              , slice_bound<V>::type(end));
      }
# endif
   private:
     // there is a confirmed CWPro8 codegen bug here. We prevent the
     // early destruction of a temporary by binding a named object
     // instead.
# if __MWERKS__ != 0x3000 
    typedef object const& object_cref2;
# else
    typedef object const object_cref2;
# endif
  };

  class object : public object_operators<object>
  {
   public:
# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
      // copy constructor without NULL checking, for efficiency. This
      // confuses VC6/7 so object_initializer also handles this case.
      object(object const&);
# endif
    
      // explicit conversion from any C++ object to Python
      template <class T>
      explicit object(T const& x)
          : m_ptr(object_initializer<is_proxy<T>::value>::get(
                      x, detail::convertible<object const*>::check(&x)))
      {
      }

      // Throw error_already_set() if the handle is null.
      explicit object(handle<> const&);
        
      // Underlying object access -- returns a borrowed reference
      PyObject* ptr() const;

   public: // implementation detail -- for internal use only
      explicit object(detail::borrowed_reference);
      explicit object(detail::new_reference);

   private:
      PyObject* m_ptr;
  };

  //
  // object_initializer -- get the handle to construct the object with,
  // based on whether T is a proxy or derived from object
  //
  template <bool is_proxy = false>
  struct object_initializer
  {
      static PyObject*
      get(object const& x, detail::yes_convertible)
      {
          return python::incref(x.ptr());
      }
      
      template <class T>
      static PyObject*
      get(T const& x, detail::no_convertible)
      {
          return python::incref(converter::arg_to_python<T>(x).get());
      }
  };
      
  template <>
  struct object_initializer<true>
  {
      template <class Policies>
      static PyObject* 
      get(proxy<Policies> const& x, detail::no_convertible)
      {
          return python::incref(x.operator object().ptr());
      }
  };
}
using api::object;

//
// Converter Specializations
//
template <class T> struct arg_from_python;

template <>
struct arg_from_python<object>
{
    typedef object result_type;
    
    arg_from_python(PyObject*);
    bool convertible() const;
    object operator()(PyObject* x) const;
};

template <>
struct arg_from_python<object const&>
    : arg_from_python<object>
{
    arg_from_python(PyObject*);
};

template <>
struct arg_from_python<object&>
{
    typedef object& result_type;
    
    arg_from_python(PyObject*);
    bool convertible() const;
    object& operator()(PyObject* x) const;
 private:
    mutable object m_result;
};

namespace converter
{
  template <class T> struct is_object_manager;

  template <>
  struct is_object_manager<object>
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };

  template <class T> struct return_from_python;
  template <>
  struct return_from_python<object>
  {
      typedef object result_type;
      result_type operator()(PyObject* x) const;
  };
}

//
// implementation
//

inline object::object(handle<> const& x)
    : m_ptr(incref(expect_non_null(x.get())))
{}

# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
// copy constructor without NULL checking, for efficiency
inline object::object(object const& rhs)
    : m_ptr(incref(rhs.m_ptr))
{}
# endif 

inline object::object(detail::borrowed_reference p)
    : m_ptr(incref((PyObject*)p))
{}


inline object::object(detail::new_reference p)
    : m_ptr(expect_non_null((PyObject*)p))
{}

inline PyObject* object::ptr() const
{
    return m_ptr;
}

//
// Converter specialization implementations
//
inline arg_from_python<object>::arg_from_python(PyObject*)
{}

inline bool arg_from_python<object>::convertible() const
{
    return true;
}

inline object arg_from_python<object>::operator()(PyObject* x) const
{
    return object(detail::borrowed_reference(x));
}

inline arg_from_python<object const&>::arg_from_python(PyObject*)
    : arg_from_python<object>(0)
{}

inline arg_from_python<object&>::arg_from_python(PyObject* x)
    : m_result(detail::borrowed_reference(x))
{}

inline bool arg_from_python<object&>::convertible() const
{
    return true;
}

inline object& arg_from_python<object&>::operator()(PyObject* x) const
{
    return m_result;
}

namespace converter
{
  inline object
  return_from_python<object>::operator()(PyObject* x) const
  {
      return object(python::detail::new_reference(x));
  }

  inline PyObject* get_managed_object(object const& x)
  {
      return x.ptr();
  }
}

}} // namespace boost::python

#endif // OBJECT_CORE_DWA2002615_HPP
