// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef UNWRAP_BASE_DWA20011130_HPP
# define UNWRAP_BASE_DWA20011130_HPP

# include <boost/python/converter/unwrapper_base.hpp>
# include <boost/python/converter/unwrapper.hpp>
# include <boost/python/converter/handle.hpp>
# include <boost/python/converter/registration.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/export.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct unwrapper;
struct BOOST_PYTHON_EXPORT body;

struct BOOST_PYTHON_EXPORT unwrap_base : handle
{
 public: // member functions
    inline unwrap_base(PyObject* source, body*, handle& prev);
    inline unwrap_base(PyObject* source, body*);
    inline PyObject* source() const;

 private: // data members
    PyObject* m_source;
};

// These converters will be used by the function wrappers. They don't
// manage any resources, but are instead linked into a chain which is
// managed by an instance of unwrap_ or wrap_.
template <class T>
struct unwrap_more_ : unwrap_base
{
 public: // member functions
    // Construction
    unwrap_more_(PyObject* source, handle& prev);

    // invoke the conversion or throw an exception if unsuccessful
    T operator*();

 protected: // constructor
    // this constructor is only for the use of unwrap_
    unwrap_more_(PyObject* source);

 private: // helper functions
    // Return the unwrapper which will convert the given Python object
    // to T, or 0 if no such converter exists
    static unwrapper_base* lookup(PyObject*);

 private:
    // unspecified storage which may be allocated by the unwrapper to
    // do value conversions.
    mutable void* m_storage;
    friend class unwrapper<T>;
};

// specialization for PyObject*
template <>
struct unwrap_more_<PyObject*>
    : unwrap_base
{
 public: // member functions
    // Construction
    unwrap_more_(PyObject* source, handle& prev)
        : unwrap_base(source, m_unwrapper, prev)
    {
    }


    // invoke the conversion or throw an exception if unsuccessful
    PyObject* operator*()
    {
        return source();
    }
        
    bool convertible(PyObject*) const
    {
        return true;
    }
    
 protected: // constructor
    // this constructor is only for the use of unwrap_
    unwrap_more_(PyObject* source)
    : unwrap_base(source, m_unwrapper)

    {
    }
 private:
    static BOOST_PYTHON_EXPORT unwrapper_base* m_unwrapper;
};

template <class T>
struct unwrap_ : unwrap_more_<T>
{
    unwrap_(PyObject* source);
    ~unwrap_();
};

//
// implementations
//
inline unwrap_base::unwrap_base(PyObject* source, body* body, handle& prev)
    : handle(body, prev)
    , m_source(source)
{
}

inline unwrap_base::unwrap_base(PyObject* source, body* body)
    : handle(body)
    , m_source(source)
{
}

inline PyObject* unwrap_base::source() const
{
    return m_source;
}

template <class T>
inline unwrapper_base* unwrap_more_<T>::lookup(PyObject* source)
{
    // Find the converters registered for T and get a unwrapper
    // appropriate for the source object
    return registration<T>::unwrapper(source);
}

template <class T>
unwrap_more_<T>::unwrap_more_(PyObject* source, handle& prev)
    : unwrap_base(source, lookup(source), prev)
    , m_storage(0)
{
}

template <class T>
unwrap_more_<T>::unwrap_more_(PyObject* source)
    : unwrap_base(source, lookup(source))
    , m_storage(0)
{
}

# if 0
template <>
inline unwrap_more_<PyObject*>::unwrap_more_(PyObject* source, handle& prev)
    : unwrap_base(source, m_unwrapper, prev)
{
}

template <>
inline unwrap_more_<PyObject*>::unwrap_more_(PyObject* source)
    : unwrap_base(source, m_unwrapper)

{
}

template <>
inline PyObject* unwrap_more_<PyObject*>::operator*()
{
    return source();
}

template <>
inline bool unwrap_more_<PyObject*>::convertible(PyObject*) const
{
    return true;
}
# endif 
template <class T>
inline unwrap_<T>::unwrap_(PyObject* source)
    : unwrap_more_<T>(source)
{
}

template <class T>
T unwrap_more_<T>::operator*()
{
    return static_cast<unwrapper<T>*>(
        get_body())->do_conversion(this);
}

template <class T>
unwrap_<T>::~unwrap_()
{
    destroy();
}
    
}}} // namespace boost::python::converter

#endif // UNWRAP_BASE_DWA20011130_HPP
