//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef CAST_DWA052500_H_
# define CAST_DWA052500_H_

# include <boost/python/detail/wrap_python.hpp>
# include <boost/operators.hpp>

namespace boost { namespace python {

namespace detail {
  // The default way of converting a PyObject* or PyTypeObject* to a T*
  template <class T>
  struct downcast_traits
  {
      template <class U>
      static T* cast(U* p) { return static_cast<T*>(p); }
  };

  inline PyTypeObject* as_base_object(const PyTypeObject*, PyObject* p)
  {
      return reinterpret_cast<PyTypeObject*>(p);
  }

  inline PyObject* as_base_object(const PyObject*, PyObject* p)
  {
      return p;
  }

  inline const PyTypeObject* as_base_object(const PyTypeObject*, const PyObject* p)
  {
      return reinterpret_cast<const PyTypeObject*>(p);
  }

  inline const PyObject* as_base_object(const PyObject*, const PyObject* p)
  {
      return p;
  }
} // namespace detail

// Convert a pointer to any type derived from PyObject or PyTypeObject to a PyObject*
inline PyObject* as_object(PyObject* p) { return p; }
inline PyObject* as_object(PyTypeObject* p) { return reinterpret_cast<PyObject*>(p); }

// If I didn't have to support stupid MSVC6 we could just use a simple template function:
// template <class T> T* downcast(PyObject*).
template <class T>
struct downcast
{
    downcast(PyObject* p)
        : m_p(detail::downcast_traits<T>::cast(detail::as_base_object((T*)0, p)))
        {}
    
    downcast(const PyObject* p)
        : m_p(detail::downcast_traits<T>::cast(detail::as_base_object((const T*)0, p)))
        {}
    
    downcast(PyTypeObject* p)
        : m_p(detail::downcast_traits<T>::cast(p))
        {}
    
    downcast(const PyTypeObject* p)
        : m_p(detail::downcast_traits<T>::cast(p))
        {}
    
    operator T*() const { return m_p; }

    // MSVC doesn't like boost::dereferencable unless T has a default
    // constructor, so operator-> must be defined by hand :(
    T* operator->() const { return &**this; }
    
    T* get() const { return m_p; }
    T& operator*() const { return *m_p; }
 private:
    T* m_p;
};

}} // namespace boost::python

#endif // CAST_DWA052500_H_
