// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_DWA2002127_HPP
# define TO_PYTHON_DWA2002127_HPP

# include <boost/python/detail/config.hpp>
# include <boost/python/converter/body.hpp>
# include <boost/python/converter/registration.hpp>
# include <boost/python/converter/source_holder.hpp>
# include <boost/python/converter/to_python_function.hpp>
# include <boost/python/converter/builtin_to_python_converters.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct to_python_lookup;

struct BOOST_PYTHON_DECL to_python_converter_base : body
{
    to_python_converter_base(type_id_t, to_python_function_base); // registers
    ~to_python_converter_base();         // unregisters
    
//    inline type_id_t key() const;
    inline to_python_function_base converter() const;
 private:
//    type_id_t m_key;
    to_python_function_base m_convert;
};

template <class T>
struct to_python_converter : to_python_converter_base
{
 public: // types
    typedef typename to_python_function<T>::type converter_t;
    
 public: // member functions
    to_python_converter(converter_t);
    converter_t converter() const;

 private: // data members
    converter_t m_convert;
};

// -------------------------------------------------------------------------

//struct to_python_base {};

template <class T>
struct to_python_lookup //: to_python_base
{
 public: // member functions
    to_python_lookup();
    bool convertible() const;
    PyObject* operator()(T) const;
 private:
    typename to_python_function<T>::type m_convert;
};

//
// implementations
//
# if 0
inline type_id_t
to_python_converter_base::key() const
{
    return m_key;
}
# endif

inline to_python_function_base
to_python_converter_base::converter() const
{
    return m_convert;
}

template <class T>
to_python_converter<T>::to_python_converter(converter_t convert)
    : to_python_converter_base(
        type_id<T>(), reinterpret_cast<to_python_function_base>(convert))
{
}

template <class T>
inline typename to_python_function<T>::type
to_python_converter<T>::converter() const
{
    return reinterpret_cast<converter_t>(
        this->to_python_converter_base::converter());
}

template <class T>
inline to_python_lookup<T>::to_python_lookup()
    : m_convert(
        registration<T>::get_to_python())
{
}

template <class T>
inline bool
to_python_lookup<T>::convertible() const
{
    return m_converter != 0;
}

template <class T>
inline PyObject*
to_python_lookup<T>::operator()(T x) const
{
    return m_convert ? m_convert(x) : 0;
}

}}} // namespace boost::python::converter

#endif // TO_PYTHON_DWA2002127_HPP
