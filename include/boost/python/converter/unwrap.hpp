#error obsolete 
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
# include <boost/python/converter/unwrapper_select.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/type.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct unwrapper;
struct BOOST_PYTHON_DECL body;

struct BOOST_PYTHON_DECL unwrap_base : handle
{
 public: // member functions
    inline unwrap_base(PyObject* source, std::pair<unwrapper_base*,void*>, handle& prev);
    inline unwrap_base(PyObject* source, std::pair<unwrapper_base*,void*>);
    inline PyObject* source() const;
    
    inline void*& data();
    
 protected:
    inline PyObject*& source();
        
 private: // data members
    PyObject* m_source;
    void* m_data;
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

 private:
    typedef typename unwrapper_select<T>::type unwrapper_t;
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
        
    void* can_convert(PyObject*) const
    {
        return &m_unwrapper;
    }
    
 protected: // constructor
    // this constructor is only for the use of unwrap_
    unwrap_more_(PyObject* source)
    : unwrap_base(source, m_unwrapper)

    {
    }
 private:
    static BOOST_PYTHON_DECL std::pair<unwrapper_base*,void*>& m_unwrapper;
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
inline unwrap_base::unwrap_base(
    PyObject* source, std::pair<unwrapper_base*,void*> unwrapper, handle& prev)
    : handle(unwrapper.first, prev)
    , m_source(source)
    , m_data(unwrapper.second)
{
}

inline unwrap_base::unwrap_base(PyObject* source, std::pair<unwrapper_base*,void*> unwrapper)
    : handle(unwrapper.first)
    , m_source(source)
    , m_data(unwrapper.second)
{
}

inline void*& unwrap_base::data()
{
    return m_data;
}

inline PyObject* unwrap_base::source() const
{
    return m_source;
}

inline PyObject*& unwrap_base::source()
{
    return m_source;
}

template <class T>
unwrap_more_<T>::unwrap_more_(PyObject* source, handle& prev)
    : unwrap_base(source,
                  registration<T>::unwrapper(source),
                  prev)
{
}

template <class T>
unwrap_more_<T>::unwrap_more_(PyObject* source)
    : unwrap_base(source, registration<T>::unwrapper(source))
{
}

template <class T>
inline unwrap_<T>::unwrap_(PyObject* source)
    : unwrap_more_<T>(source)
{
}

template <class T>
T unwrap_more_<T>::operator*()
{
    return static_cast<unwrapper<T>*>(
        get_body())->convert(this->source(), this->data(), boost::type<T>());
}

template <class T>
unwrap_<T>::~unwrap_()
{
    this->destroy();
}
    
}}} // namespace boost::python::converter

#endif // UNWRAP_BASE_DWA20011130_HPP
