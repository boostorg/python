// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef WRAP_DWA2001127_HPP
# define WRAP_DWA2001127_HPP
# include <boost/python/converter/registration.hpp>
# include <boost/python/converter/handle.hpp>
# include <boost/python/converter/body.hpp>
# include <boost/python/converter/wrapper.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/converter/source_holder.hpp>
# include <cassert>

namespace boost { namespace python { namespace converter { 

struct BOOST_PYTHON_DECL wrapper_base;

template <class T> struct wrapper;

struct wrap_base : handle
{
 public: // member functions
    wrap_base(body*, handle& prev);
    wrap_base(body*);
    PyObject* release();
    
 public: // accessor, really only for wrappers
    PyObject*& target() const;
    
 protected:
    void hold_result(PyObject*) const;
    
 private: 
    mutable PyObject* m_target;
};

template <class T>
struct wrap_more_ : wrap_base
{
 protected:
    typedef T source_t;
    
 public: // member functions
    wrap_more_(handle& prev);

    PyObject* operator()(source_t) const;

 protected: // constructor for wrap_<T>, below
    wrap_more_();
    
 private: // helper functions
    static wrapper_base* lookup();
    
 private:
    friend class wrapper<T>;
};

template <class T>
struct wrap_ : wrap_more_<T>
{
    typedef typename wrap_more_<T>::source_t source_t;
 public: // member functions
    wrap_();
    ~wrap_();
};

//
// implementations
//

inline wrap_base::wrap_base(body* body, handle& prev)
    : handle(body, prev),
      m_target(0)
{
}

inline wrap_base::wrap_base(body* body)
    : handle(body),
      m_target(0)
{
}

inline PyObject*& wrap_base::target() const
{
    return m_target;
}

inline void wrap_base::hold_result(PyObject* p) const
{
    assert(m_target == 0);
    m_target = p;
}

inline PyObject* wrap_base::release()
{
    PyObject* result = m_target;
    m_target = 0;
    return result;
}

template <class T>
inline wrapper_base* wrap_more_<T>::lookup()
{
    // Find the converters registered for T and get a wrapper
    // appropriate for the source object
    return registration<T>::wrapper();
}

template <class T>
inline wrap_more_<T>::wrap_more_(handle& prev)
    : wrap_base(lookup(), prev)
{
    
}

template <class T>
PyObject* wrap_more_<T>::operator()(source_t x) const
{
    return static_cast<wrapper<T>*>(
        get_body())->do_conversion(*this, source_holder<T>(x));
}

template <class T>
wrap_more_<T>::wrap_more_()
    : wrap_base(lookup())
{
}

template <class T>
wrap_<T>::wrap_()
    : wrap_more_<T>()
{
}

template <class T>
wrap_<T>::~wrap_()
{
    destroy();
}

}}} // namespace boost::python::converter

#endif // WRAP_DWA2001127_HPP
