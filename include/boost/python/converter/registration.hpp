// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef REGISTRATION_DWA20011130_HPP
# define REGISTRATION_DWA20011130_HPP
# include <boost/python/detail/config.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/mpl/pop_front.hpp>
# include <boost/mpl/for_each.hpp>
# include <boost/mpl/front.hpp>
# include <utility>
# ifdef BOOST_PYTHON_TRACE
#  include <iostream>
# endif 

namespace boost { namespace python { namespace converter { 

template <class T> struct from_python_converter;
template <class T> struct target;
template <class T> struct source;

// This class is really sort of a "templated namespace". It manages a
// static data member which refers to the registry entry for T. This
// reference is acquired once to reduce the burden of multiple
// dictionary lookups at runtime.
template <class T>
struct registration
{
 public: // member functions
    // Return a converter which can convert the given Python object to
    // T, or 0 if no such converter exists. Fill in data with
    // the result of the converter's check function
    static from_python_converter<T> const* get_from_python(PyObject*, void*& data);

    // Return a converter which can convert T to a Python object, or 0
    // if no such converter exists
    static to_python_function<T>::type get_to_python();

    static registry::entry* find_entry();
 private: // helper functions
    static registry::entry* entry();
    static registry::entry* known_entry();
    
 private: // data members
    static registry::entry* m_registry_entry;
};

namespace detail
{
  // An MPL BinaryMetaFunction class which initializes the
  // registration entry for the target type of its 2nd argument.
  struct setup_target_registration
  {
      template <class Ignored, class T> struct apply
      {
          typedef T type;
          static void execute()
          {
              typedef typename target<T>::type target_t;
              registration<target_t>::find_entry();
          }
      };
  };

  template <class T>
  struct find_return_value_entry
  {
      static void execute() { registration<T>::find_entry(); }
  };

  template <>
  struct find_return_value_entry<void>
  {
      static void execute() {}
  };
  
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1200
  template <>
  struct find_return_value_entry<void const>
  {
      static void execute() {}
  };
# endif 
}

template <class Sequence>
void acquire_registrations(Sequence signature)
{
    typedef typename mpl::pop_front<Sequence>::sequence args;
    typedef typename mpl::front<Sequence>::type return_type;
    
    mpl::for_each<args, void, detail::setup_target_registration>::execute();
    
    typedef typename source<return_type>::type return_source_type;
    detail::find_return_value_entry<return_source_type>::execute();
}
  

// because this is static POD data it will be initialized to zero
template <class T>
registry::entry* registration<T>::m_registry_entry;

template <class T>
registry::entry* registration<T>::find_entry()
{
    return m_registry_entry = registry::find(type_id<T>());
}

template <class T>
inline registry::entry* registration<T>::entry()
{
    if (!m_registry_entry)
        find_entry();
    return m_registry_entry;
}

template <class T>
inline registry::entry* registration<T>::known_entry()
{
    assert(m_registry_entry != 0);
    return m_registry_entry;
}

template <class T>
from_python_converter<T> const* registration<T>::get_from_python(PyObject* p, void*& data)
{
    return static_cast<from_python_converter<T> const*>(
        known_entry()->get_from_python(p, data)
        );
}

template <class T>
typename to_python_function<T>::type registration<T>::get_to_python()
{
# ifdef BOOST_PYTHON_TRACE
    std::cout << "retrieving wrapper for " << type_id<T>() << std::endl;
# endif 
    return reinterpret_cast<to_python_function<T>::type>(
        known_entry()->get_to_python());
}

}}} // namespace boost::python::converter

#endif // REGISTRATION_DWA20011130_HPP
