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

  typedef proxy<const_attribute_policies> const_object_attribute;
  typedef proxy<attribute_policies> object_attribute;
  typedef proxy<const_item_policies> const_object_item;
  typedef proxy<item_policies> object_item;

  class object
  {
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1200
      typedef object const& self_cref;
# else 
      typedef object self_cref;
# endif
      
   public:
# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
      // copy constructor without NULL checking, for efficiency
      object(object const&);
# endif
    
      // explicit conversion from any C++ object to Python
      template <class T>
      explicit object(T const& x)
          : m_ptr(
              python::borrowed(
                  python::allow_null( // null check is already done
                      converter::arg_to_python<T>(x).get())
                  )
              )
      {
      }

      // capture this case explicitly to handle string
      // literals. Otherwise, they get deduced as char[N]const& above
      // and conversion fails at runtime.
      explicit object(char const* x)
          : m_ptr(
              python::borrowed(
                  python::allow_null( // null check is already done
                      converter::arg_to_python<char const*>(x).get())
                  )
              )
      {
      }
    
      // Throw error_already_set() if the handle is null.
      explicit object(handle<> const&);
    
      // Attribute access via x.attr("attribute_name")
      const_object_attribute attr(char const*) const;
      object_attribute attr(char const*);

      object operator()() const
      {
          return object(call<handle<> >(m_ptr.get()));
      }

# ifndef BOOST_PYTHON_GENERATE_CODE
#  include <boost/python/preprocessed/object_call.hpp>
# endif

# define BOOST_PYTHON_OBJECT_CALL(nargs,ignored)                                        \
      template <BOOST_PP_ENUM_PARAMS(nargs, class A)>                                   \
      object operator()(BOOST_PYTHON_ENUM_PARAMS2(nargs, (A,const& a))) const           \
      {                                                                                 \
          return object(call<handle<> >(&**this, BOOST_PP_ENUM_PARAMS(nargs, a)));      \
      }

      BOOST_PYTHON_REPEAT_ARITY_2ND(BOOST_PYTHON_OBJECT_CALL, ignored)

      // truth value testing
      typedef handle<> (object::*bool_type);
      operator bool_type() const;
      bool operator!() const; // needed for vc6

      // item access
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

inline object::operator object::bool_type() const
{
    return PyObject_IsTrue(m_ptr.get()) ? &object::m_ptr : 0;
}

inline bool object::operator!() const
{
    return !PyObject_IsTrue(m_ptr.get());
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
