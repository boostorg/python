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

  //
  // object_handle -- get the handle to construct the object with,
  // based on whether T is a proxy or not
  //
  template <bool = false>
  struct object_handle
  {
      template <class T>
      static handle<> get(T const& x)
      {
          return handle<>(
              python::borrowed(
                  python::allow_null( // null check is already done
                      converter::arg_to_python<T>(x).get())
                  )
              );
      }
  };
      
  template <>
  struct object_handle<true>
  {
      template <class Policies>
      static handle<> get(proxy<Policies> const& x)
      {
          return x.operator object().ptr();
      }
  };
      
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
  typedef handle<> const& (object::*bool_type)() const;
  
  template <class U>
  class object_operators
  {
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1200
      typedef object const& self_cref;
# else 
      typedef object self_cref;
# endif

     // there appears to be a codegen bug here. We prevent the early
     // destruction of a temporary in CWPro8 by binding a named
     // object instead.
# if __MWERKS__ != 0x3000 
    typedef object const& object_cref;
# else
    typedef object const object_cref;
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
      const_object_item operator[](self_cref) const;
      object_item operator[](self_cref);
    
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
      const_object_slice slice(self_cref, self_cref) const;
      object_slice slice(self_cref, self_cref);

      const_object_slice slice(slice_nil, self_cref) const;
      object_slice slice(slice_nil, self_cref);
                             
      const_object_slice slice(self_cref, slice_nil) const;
      object_slice slice(self_cref, slice_nil);
                             
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


# if BOOST_MSVC == 1200
      // For whatever reason, VC6 generates incorrect code unless we
      // define this
      object_operators& operator=(object_operators const&) { return *this; }
# endif
  };

  class object : public object_operators<object>
  {
   public:
# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
      // copy constructor without NULL checking, for efficiency
      object(object const&);
# endif
    
      // explicit conversion from any C++ object to Python
      template <class T>
      explicit object(T const& x)
          : m_ptr(object_handle<is_proxy<T>::value>::get(x))
      {
      }

      // capture this case explicitly to handle string
      // literals. Otherwise, they get deduced as char[N]const& above
      // and conversion fails at runtime.
      explicit object(char const* x)
          : m_ptr(object_handle<>::get(x))
      {
      }
    
      // Throw error_already_set() if the handle is null.
      explicit object(handle<> const&);
        
      // Underlying object access
      handle<> const& ptr() const;

   public: // implementation detail -- for internal use only
      object(null_ok<detail::borrowed<PyObject> >*);
      object(detail::borrowed<null_ok<PyObject> >*);
      object(detail::borrowed<PyObject>*);
      class new_pyobject_reference;
      object(new_pyobject_reference*);

   private:
      handle<> m_ptr;
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
    : m_ptr(python::borrowed(x.get()))
{}

# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
// copy constructor without NULL checking, for efficiency
inline object::object(object const& rhs)
    : m_ptr(python::allow_null(python::borrowed(rhs.m_ptr.get())))
{}
# endif 

inline object::object(null_ok<detail::borrowed<PyObject> >* p)
    : m_ptr(p)
{}

inline object::object(detail::borrowed<null_ok<PyObject> >* p)
    : m_ptr(p)
{}

inline object::object(detail::borrowed<PyObject>* p)
    : m_ptr(p)
{}

inline object::object(object::new_pyobject_reference* p)
    : m_ptr((PyObject*)p)
{}

inline handle<> const& object::ptr() const
{
    return m_ptr;
}

//
// Converter speciaization implementations
//
inline arg_from_python<object>::arg_from_python(PyObject*)
{}

inline bool arg_from_python<object>::convertible() const
{
    return true;
}

inline object arg_from_python<object>::operator()(PyObject* x) const
{
    return object(python::borrowed(python::allow_null(x)));
}

inline arg_from_python<object const&>::arg_from_python(PyObject*)
    : arg_from_python<object>(0)
{}

inline arg_from_python<object&>::arg_from_python(PyObject* x)
    : m_result(python::allow_null(python::borrowed(x)))
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
      return object((object::new_pyobject_reference*)x);
  }

  inline PyObject* get_managed_object(object const& x)
  {
      return x.ptr().get();
  }
}

}} // namespace boost::python

#endif // OBJECT_CORE_DWA2002615_HPP
