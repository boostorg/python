//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef CAST_DWA052500_H_
# define CAST_DWA052500_H_

# include "wrap_python.h"
# include <boost/operators.hpp>

namespace py {

// The default way of converting a PyObject* or PyTypeObject* to a T*
template <class T>
struct DowncastTraits
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

// Convert a pointer to any type derived from PyObject or PyTypeObject to a PyObject*
inline PyObject* as_object(PyObject* p) { return p; }
inline PyObject* as_object(PyTypeObject* p) { return reinterpret_cast<PyObject*>(p); }

// If I didn't have to support stupid MSVC6 we could just use a simple template function:
// template <class T> T* downcast(PyObject*).
template <class T>
struct Downcast : boost::dereferenceable<Downcast<T>, T*>
{
    Downcast(PyObject* p)
        : m_p(DowncastTraits<T>::cast(as_base_object((T*)0, p)))
        {}
    
    Downcast(const PyObject* p)
        : m_p(DowncastTraits<T>::cast(as_base_object((const T*)0, p)))
        {}
    
    Downcast(PyTypeObject* p)
        : m_p(DowncastTraits<T>::cast(p))
        {}
    
    Downcast(const PyTypeObject* p)
        : m_p(DowncastTraits<T>::cast(p))
        {}
    
    operator T*() const { return m_p; }
    T* get() const { return m_p; }
    T& operator*() const { return *m_p; }
private:
    T* m_p;
};

}

#endif // CAST_DWA052500_H_
