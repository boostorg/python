//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef PYPTR_DWA050400_H_
# define PYPTR_DWA050400_H_

# include "pyconfig.h"
# include <boost/operators.hpp>
# include "wrap_python.h"
# include "cast.h"
# include <cassert>
# include "signatures.h"
# include "errors.h"

namespace py {


#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
}
#endif

template <class T, class Base>
struct PyPtrConversions : Base
{
    inline friend T from_python(PyObject* x, py::Type<const T&>)
        { return T(py::Downcast<typename T::value_type>(x).get(), T::new_ref); }

    inline friend T from_python(PyObject* x, py::Type<T>)
        { return T(py::Downcast<typename T::value_type>(x).get(), T::new_ref); }
    
    inline friend PyObject* to_python(T x)
        { return py::as_object(x.release()); }
    
};

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
namespace py {
using ::PyPtrConversions;
#endif

template <class T>
class PyPtr
	: public PyPtrConversions<PyPtr<T>,
       boost::dereferenceable<PyPtr<T>, T*> > // supplies op->
{
public:
    typedef T value_type;
    
	PyPtr(const PyPtr& rhs)
		: m_p(rhs.m_p)
	{
		Py_XINCREF(object());
	}

#if !defined(PY_MSVC6_OR_EARLIER)
	template <class T2>
	PyPtr(const PyPtr<T2>& rhs)
		: m_p(rhs.object())
	{
		Py_XINCREF(object());
	}
#endif

	PyPtr() : m_p(0) {}
    
    // These are two ways of spelling the same thing, that we need to increment
    // the reference count on the pointer when we're initialized.
	enum NewRef { new_ref, borrowed = new_ref };

    enum AllowNull { null_ok };
    
    template <class T2>
    explicit PyPtr(T2* x)
        : m_p(expect_non_null(x)) {}

    template <class T2>
    PyPtr(T2* x, NewRef)
        : m_p(expect_non_null(x)) { Py_INCREF(object()); }
	
    template <class T2>
    PyPtr(T2* x, AllowNull)
        : m_p(x) {}

    template <class T2>
    PyPtr(T2* x, AllowNull, NewRef)
        : m_p(x) { Py_XINCREF(object()); }
	
    template <class T2>
    PyPtr(T2* x, NewRef, AllowNull)
        : m_p(x) { Py_XINCREF(object()); }
	
#if !defined(PY_MSVC6_OR_EARLIER)
	template <class T2>
	PyPtr& operator=(const PyPtr<T2>& rhs)
	{
		Py_XDECREF(object());
		m_p = rhs.m_p;
		Py_XINCREF(object());
		return *this;
	}
#endif

	PyPtr& operator=(const PyPtr& rhs)
	{
		Py_XINCREF(static_cast<PyObject*>(rhs.m_p));
		Py_XDECREF(object());
		m_p = rhs.m_p;
		return *this;
	}
    
	~PyPtr()
	{
		Py_XDECREF(m_p);
	}
	
	T& operator*() const { return *m_p; }
    
	T* get() const { return m_p; }

	T* release()
	{
		T* p = m_p;
		m_p = 0;
		return p;
	}

    void reset()
        { Py_XDECREF(m_p); m_p = 0; }
    
    template <class T2>
    void reset(T2* x)
        { Py_XDECREF(m_p); m_p = expect_non_null(x);}

    template <class T2>
    void reset(T2* x, NewRef)
        { Py_XDECREF(m_p); m_p = expect_non_null(x); Py_INCREF(object()); }
	
    template <class T2>
    void reset(T2* x, AllowNull)
        { Py_XDECREF(m_p); m_p = x;}

    template <class T2>
    void reset(T2* x, AllowNull, NewRef)
        { Py_XDECREF(m_p); m_p = x; Py_XINCREF(object()); }
	
    template <class T2>
    void reset(T2* x, NewRef, AllowNull)
        { Py_XDECREF(m_p); m_p = x; Py_XINCREF(object()); }
	
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
private:
    template<typename Y> friend class shared_ptr;
#endif

    inline PyObject* object() const
        { return as_object(m_p); }

	T* m_p;
};

typedef PyPtr<PyObject> Ptr;

template <class T>
Ptr make_ptr(const T& x)
{
    return Ptr(to_python(x));
}

}

#endif // PYPTR_DWA050400_H_
