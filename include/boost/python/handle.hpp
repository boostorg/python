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

namespace boost { namespace python { 

template <class T>
inline T* incref(T* p)
{
    Py_INCREF(python::upcast<PyObject>(p));
    return p;
}

template <class T>
inline T* xincref(T* p)
{
    Py_XINCREF(python::upcast<PyObject>(p));
    return p;
}

template <class T>
inline void decref(T* p)
{
    Py_DECREF(python::upcast<PyObject>(p));
}

template <class T>
inline void xdecref(T* p)
{
    Py_XDECREF(python::upcast<PyObject>(p));
}

template <class T> struct borrowed;
template <class T> struct null_ok;

template <class T>
inline borrowed<T>* borrow(T* p)
{
    return (borrowed<T>*)p;
}

template <class T>
inline null_ok<T>* allow_null(T* p)
{
    return (null_ok<T>*)p;
}

namespace detail
{
  template <class T>
  inline T* manage_ptr(borrowed<null_ok<T> >* p, int)
  {
      return python::xincref((T*)p);
  }
  
  template <class T>
  inline T* manage_ptr(null_ok<borrowed<T> >* p, int)
  {
      return python::xincref((T*)p);
  }
  
  template <class T>
  inline T* manage_ptr(borrowed<T>* p, long)
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

#if 0
  template <class T>
  struct handle_proxy
      : handle_proxy<typename base_type_traits<T>::type>
  {
      typedef typename base_type_traits<T>::type base_t;
      handle_proxy(PyObject* p)
          : handle_proxy<base_t>(p)
      {}
      operator T*() const { return python::downcast<T>(m_p); }
  };

  template <>
  struct handle_proxy<PyObject>
  {
      handle_proxy(PyObject* p) : m_p(p) {}
      operator PyObject*() const { return (PyObject*)m_p; }
   private:
      PyObject* m_p;
  };
#endif 
}

template <class T = PyObject>
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

}} // namespace boost::python


#endif // HANDLE_DWA200269_HPP
