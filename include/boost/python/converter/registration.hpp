// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef REGISTRATION_DWA20011130_HPP
# define REGISTRATION_DWA20011130_HPP
# include <boost/config.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/export.hpp>
# ifdef BOOST_PYTHON_TRACE
#  include <iostream>
# endif 

namespace boost { namespace python { namespace converter { 

struct BOOST_PYTHON_EXPORT wrapper_base;
struct BOOST_PYTHON_EXPORT unwrapper_base;

// This class is really sort of a "templated namespace". It manages a
// static data member which refers to the registry entry for T. This
// reference is acquired once to reduce the burden of multiple
// dictionary lookups at runtime.
template <class T>
struct registration
{
 public: // member functions
    // Return a converter which can convert the given Python object to
    // T, or 0 if no such converter exists
    static unwrapper_base* unwrapper(PyObject*);

    // Return a converter which can convert T to a Python object, or 0
    // if no such converter exists
    static wrapper_base* wrapper();

 private: // helper functions
    static registry::entry* entry();
    static registry::entry* find_entry();
    
 private: // data members
    static registry::entry* m_registry_entry;
};

// because this is static POD data it will be initialized to zero
template <class T>
registry::entry* registration<T>::m_registry_entry;

template <class T>
registry::entry* registration<T>::find_entry()
{
    return registry::find(type_id<T>());
}

template <class T>
inline registry::entry* registration<T>::entry()
{
    if (!m_registry_entry)
        m_registry_entry = find_entry();
    return m_registry_entry;
}

template <class T>
unwrapper_base* registration<T>::unwrapper(PyObject* p)
{
# ifdef BOOST_PYTHON_TRACE
    std::cout << "retrieving unwrapper for " << type_id<T>() << std::endl;
# endif 
    return entry()->unwrapper(p);
}

template <class T>
wrapper_base* registration<T>::wrapper()
{
# ifdef BOOST_PYTHON_TRACE
    std::cout << "retrieving wrapper for " << type_id<T>() << std::endl;
# endif 
    return entry()->wrapper();
}

}}} // namespace boost::python::converter

#endif // REGISTRATION_DWA20011130_HPP
