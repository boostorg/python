//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef PYPTR_DWA050400_H_
# define PYPTR_DWA050400_H_

# ifdef BOOST_PYTHON_V2

#  error obsolete 

# else

# include <boost/python/detail/config.hpp>
# include <boost/operators.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/cast.hpp>
# include <cassert>
# include <cstddef>
# include <boost/python/detail/signatures.hpp>
# include <boost/python/errors.hpp>
# include <boost/python/detail/cast.hpp>

#  include <boost/python/conversions.hpp>

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

template <class T, class Value, class Base = boost::detail::empty_base>
struct py_ptr_conversions : Base
{
    inline friend T from_python(PyObject* x, boost::python::type<const T&>)
        { return T(boost::python::downcast<Value>(x).get(), T::increment_count); }

    inline friend T from_python(PyObject* x, boost::python::type<T>)
        { return T(boost::python::downcast<Value>(x).get(), T::increment_count); }
    
    inline friend PyObject* to_python(T x)
        { return boost::python::as_object(x.release()); }
    
};

BOOST_PYTHON_END_CONVERSION_NAMESPACE

namespace boost { namespace python {

BOOST_PYTHON_IMPORT_CONVERSION(py_ptr_conversions);

template <class T>
class reference
    : public py_ptr_conversions<reference<T>, T>
{
public:
    typedef T value_type;
    
    reference(const reference& rhs)
        : m_p(rhs.m_p)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XINCREF(m_p);
    }

    reference() : m_p(0) {}
    
    // These are two ways of spelling the same thing, that we need to increment
    // the reference count on the pointer when we're initialized.
    enum increment_count_t { increment_count };

    enum allow_null { null_ok };
    
    template <class T2>
    explicit reference(T2* x)
        : m_p(expect_non_null(x))
    {
        assert(m_p->ob_refcnt > 0);
    }

    template <class T2>
    reference(T2* x, increment_count_t)
        : m_p(expect_non_null(x))
    {
        assert(m_p->ob_refcnt > 0);
        Py_INCREF(m_p);
    }
    
    template <class T2>
    reference(T2* x, allow_null)
        : m_p(x)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
    }

    template <class T2>
    reference(T2* x, allow_null, increment_count_t)
        : m_p(x)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XINCREF(m_p);
    }
    
    template <class T2>
    reference(T2* x, increment_count_t, allow_null)
        : m_p(x)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XINCREF(m_p);
    }
    
    reference& operator=(const reference& rhs)
    {
        assert(rhs.m_p == 0 || rhs.m_p->ob_refcnt > 0);
        Py_XINCREF(static_cast<PyObject*>(rhs.m_p));
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XDECREF(m_p);
        m_p = rhs.m_p;
        return *this;
    }
    
    ~reference()
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XDECREF(m_p);
    }
    
    T& operator*() const
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        return *m_p;
    }
    
    // MSVC doesn't like boost::dereferencable unless T has a default
    // constructor, so operator-> must be defined by hand :(
    T* operator->() const
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        return &**this;
    } 
    
    T* get() const
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        return m_p;
    }

    T* release()
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        T* p = m_p;
        m_p = 0;
        return p;
    }

    void reset()
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XDECREF(m_p);
        m_p = 0;
    }
    
    template <class T2>
    void reset(T2* x)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XDECREF(m_p);
        m_p = expect_non_null(x);
        assert(m_p == 0 || m_p->ob_refcnt > 0);
    }

    template <class T2>
    void reset(T2* x, increment_count_t)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XINCREF(x);
        Py_XDECREF(m_p);
        m_p = expect_non_null(x);
        assert(m_p->ob_refcnt > 0);
    }
    
    template <class T2>
    void reset(T2* x, allow_null)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XDECREF(m_p);
        m_p = x;
        assert(m_p == 0 || m_p->ob_refcnt > 0);
    }

    template <class T2>
    void reset(T2* x, allow_null, increment_count_t)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XINCREF(x);
        Py_XDECREF(m_p);
        m_p = x;
        assert(m_p == 0 || m_p->ob_refcnt > 0);
    }
    
    template <class T2>
    void reset(T2* x, increment_count_t, allow_null)
    {
        assert(m_p == 0 || m_p->ob_refcnt > 0);
        Py_XINCREF(x);
        Py_XDECREF(m_p);
        m_p = x;
        assert(m_p == 0 || m_p->ob_refcnt > 0);
    }
    
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
private:
    template<typename Y> friend class shared_ptr;
#endif

    inline PyObject* object() const
        {
            return as_object(m_p);
        }

    T* m_p;
};

typedef reference<PyObject> ref;

template <class T>
ref make_ref(const T& x)
{
    return ref(to_python(x));
}

}} // namespace boost::python

#endif // BOOST_PYTHON_V2

#endif // PYPTR_DWA050400_H_
