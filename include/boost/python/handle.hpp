// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef HANDLE_DWA200269_HPP
# define HANDLE_DWA200269_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/cast.hpp>
# include <boost/python/errors.hpp>
# include <boost/python/borrowed.hpp>
# include <boost/python/handle_fwd.hpp>
# include <boost/python/refcount.hpp>

namespace boost { namespace python { 

template <class T> struct null_ok;

template <class T>
inline null_ok<T>* allow_null(T* p)
{
    return (null_ok<T>*)p;
}

namespace detail
{
  template <class T>
  inline T* manage_ptr(detail::borrowed<null_ok<T> >* p, int)
  {
      return python::xincref((T*)p);
  }
  
  template <class T>
  inline T* manage_ptr(null_ok<detail::borrowed<T> >* p, int)
  {
      return python::xincref((T*)p);
  }
  
  template <class T>
  inline T* manage_ptr(detail::borrowed<T>* p, long)
  {
      return python::incref(expect_non_null((T*)p));
  }
  
  template <class T>
  inline T* manage_ptr(null_ok<T>* p, long)
  {
      return (T*)p;
  }
  
  template <class T>
  inline T* manage_ptr(T* p, ...)
  {
      return expect_non_null(p);
  }
}

template <class T>
class handle
{
    typedef T* (handle::*bool_type);
    
 public:
    handle();
    ~handle();

    template <class Y>
    handle(Y* p)
        : m_p(
            python::upcast<T>(
                detail::manage_ptr(p, 0)
                )
            )
    {
    }

    handle& operator=(handle const& r);

#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)

    template<typename Y>
    handle& operator=(handle<Y> const & r) // never throws
    {
        python::xdecref(m_p);
        m_p = python::xincref(python::upcast<T>(r.get()));
        return *this;
    }

#endif

    template <typename Y>
    handle(handle<Y> const& r)
        : m_p(python::xincref(python::upcast<T>(r.get())))
    {
    }
    
    handle(handle const& r)
        : m_p(python::xincref(r.m_p))
    {
    }
    
    T* operator-> () const;
    T& operator* () const;
    T* get() const;
    T* release();
    
    operator bool_type() const // never throws
    {
        return m_p ? &handle<T>::m_p : 0;
    }
    bool operator! () const; // never throws

 private: // data members
    T* m_p;
};

typedef handle<PyTypeObject> type_handle;

//
// Converter specializations
//
template <class T> struct arg_from_python;
template <>
struct arg_from_python<handle<> >
{
    typedef handle<> result_type;
    
    arg_from_python(PyObject*);
    bool convertible() const;
    handle<> operator()(PyObject* x) const;
};

template <>
struct arg_from_python<handle<> const&>
    : arg_from_python<handle<> >
{
    arg_from_python(PyObject*);
};

namespace converter
{
  template <class T> struct return_from_python;

  template <>
  struct return_from_python<handle<> >
  {
      typedef handle<> result_type;
      result_type operator()(PyObject* x) const;
  };
}

//
// Compile-time introspection
//
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template<typename T>
class is_handle
{
 public:
    BOOST_STATIC_CONSTANT(bool, value = false); 
};

template<typename T>
class is_handle<handle<T> >
{
 public:
    BOOST_STATIC_CONSTANT(bool, value = true);
};
# else
namespace detail
{
  typedef char (&yes_handle_t)[1];
  typedef char (&no_handle_t)[2];
      
  no_handle_t is_handle_test(...);

  template<typename T>
  yes_handle_t is_handle_test(boost::type< handle<T> >);
}

template<typename T>
class is_handle
{
 public:
    BOOST_STATIC_CONSTANT(
        bool, value = (
            sizeof(detail::is_handle_test(boost::type<T>()))
            == sizeof(detail::yes_handle_t)));
};
# endif

//
// implementations
//
template <class T>
inline handle<T>::handle()
    : m_p(0)
{
}

template <class T>
inline handle<T>::~handle()
{
    python::xdecref(m_p);
}

template <class T>
inline handle<T>& handle<T>::operator=(handle<T> const& r)
{
    python::xdecref(m_p);
    m_p = python::xincref(r.m_p);
    return *this;
}

template <class T>
inline T* handle<T>::operator->() const
{
    return m_p;
}

template <class T>
inline T& handle<T>::operator*() const
{
    return *m_p;
}

template <class T>
inline T* handle<T>::get() const
{
    return m_p;
}
    
template <class T>
inline bool handle<T>::operator!() const
{
    return m_p == 0;
}

template <class T>
inline T* handle<T>::release()
{
    T* result = m_p;
    m_p = 0;
    return result;
}

//
// Converter specialization implementation
//
inline arg_from_python<handle<> >::arg_from_python(PyObject*)
{}

inline bool arg_from_python<handle<> >::convertible() const
{
    return true;
}

inline handle<> arg_from_python<handle<> >::operator()(PyObject* x) const
{
    return handle<>(python::borrowed(python::allow_null(x)));
}

inline arg_from_python<handle<> const&>::arg_from_python(PyObject*)
    : arg_from_python<handle<> >(0)
{}

namespace converter
{
  inline handle<>
  return_from_python<handle<> >::operator()(PyObject* x) const
  {
      return handle<>(x);
  }
}

}} // namespace boost::python


#endif // HANDLE_DWA200269_HPP
