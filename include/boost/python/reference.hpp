//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef PYPTR_DWA050400_H_
# define PYPTR_DWA050400_H_

# include <boost/python/detail/config.hpp>
# include <boost/operators.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/cast.hpp>
# include <cassert>
# include <boost/python/detail/signatures.hpp>
# include <boost/python/errors.hpp>
# include <boost/python/conversions.hpp>

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

template <class T, class Value, class Base>
struct py_ptr_conversions : Base
{
    inline friend T from_python(PyObject* x, boost::python::type<const T&>)
        { return T(boost::python::downcast<Value>(x).get(), T::increment_count); }

    inline friend T from_python(PyObject* x, boost::python::type<T>)
        { return T(boost::python::downcast<Value>(x).get(), T::increment_count); }
    
    inline friend PyObject* to_python(T x, boost::python::lookup_tag)
        { return boost::python::as_object(x.release()); }
    
};

BOOST_PYTHON_END_CONVERSION_NAMESPACE

namespace boost { namespace python {

template <class T>
class reference
	: public py_ptr_conversions<reference<T>, T,
       boost::dereferenceable<reference<T>, T*> > // supplies op->
{
public:
    typedef T value_type;
    
	reference(const reference& rhs)
		: m_p(rhs.m_p)
	{
		Py_XINCREF(object());
	}

#if !defined(BOOST_MSVC6_OR_EARLIER)
	template <class T2>
	reference(const reference<T2>& rhs)
		: m_p(rhs.object())
	{
		Py_XINCREF(object());
	}
#endif

	reference() : m_p(0) {}
    
    // These are two ways of spelling the same thing, that we need to increment
    // the reference count on the pointer when we're initialized.
	enum increment_count_t { increment_count };

    enum allow_null { null_ok };
    
    template <class T2>
    explicit reference(T2* x)
        : m_p(expect_non_null(x)) {}

    template <class T2>
    reference(T2* x, increment_count_t)
        : m_p(expect_non_null(x)) { Py_INCREF(object()); }
	
    template <class T2>
    reference(T2* x, allow_null)
        : m_p(x) {}

    template <class T2>
    reference(T2* x, allow_null, increment_count_t)
        : m_p(x) { Py_XINCREF(object()); }
	
    template <class T2>
    reference(T2* x, increment_count_t, allow_null)
        : m_p(x) { Py_XINCREF(object()); }
	
#if !defined(BOOST_MSVC6_OR_EARLIER)
	template <class T2>
	reference& operator=(const reference<T2>& rhs)
	{
		Py_XDECREF(object());
		m_p = rhs.m_p;
		Py_XINCREF(object());
		return *this;
	}
#endif

	reference& operator=(const reference& rhs)
	{
		Py_XINCREF(static_cast<PyObject*>(rhs.m_p));
		Py_XDECREF(object());
		m_p = rhs.m_p;
		return *this;
	}
    
	~reference()
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
    void reset(T2* x, increment_count_t)
        { Py_XDECREF(m_p); m_p = expect_non_null(x); Py_INCREF(object()); }
	
    template <class T2>
    void reset(T2* x, allow_null)
        { Py_XDECREF(m_p); m_p = x;}

    template <class T2>
    void reset(T2* x, allow_null, increment_count_t)
        { Py_XDECREF(m_p); m_p = x; Py_XINCREF(object()); }
	
    template <class T2>
    void reset(T2* x, increment_count_t, allow_null)
        { Py_XDECREF(m_p); m_p = x; Py_XINCREF(object()); }
	
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
private:
    template<typename Y> friend class shared_ptr;
#endif

    inline PyObject* object() const
        { return as_object(m_p); }

	T* m_p;
};

typedef reference<PyObject> ref;

template <class T>
ref make_ref(const T& x)
{
    return ref(to_python(x, lookup_tag()));
}

}} // namespace boost::python

#endif // PYPTR_DWA050400_H_
