// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BACK_REFERENCE_DWA2002510_HPP
# define BACK_REFERENCE_DWA2002510_HPP

# include <boost/python/reference.hpp>

namespace boost { namespace python { 

template <class T>
struct back_reference
{
 public:
    typedef T type;
    
    back_reference(PyObject*, T);
    ref reference() const;
    T get() const;
 private:
    ref m_reference;
    T m_value;
};

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template<typename T>
class is_back_reference
{
 public:
    BOOST_STATIC_CONSTANT(bool, value = false); 
};

template<typename T>
class is_back_reference<back_reference<T> >
{
 public:
    BOOST_STATIC_CONSTANT(bool, value = true);
};

# else // no partial specialization

}} // namespace boost::python

#include <boost/type.hpp>

namespace boost { namespace python {

namespace detail
{
  typedef char (&yes_back_reference_t)[1];
  typedef char (&no_back_reference_t)[2];
      
  no_back_reference_t is_back_reference_test(...);

  template<typename T>
  yes_back_reference_t is_back_reference_test(type< back_reference<T> >);
}

template<typename T>
class is_back_reference
{
 public:
    BOOST_STATIC_CONSTANT(
        bool, value = (
            sizeof(detail::is_back_reference_test(type<T>()))
            == sizeof(detail::yes_back_reference_t)));
};

# endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//
// implementations
//
template <class T>
back_reference<T>::back_reference(PyObject* p, T x)
    : m_reference(p, ref::increment_count)
      , m_value(x)
{
}

template <class T>
ref back_reference<T>::reference() const
{
    return m_reference;
}

template <class T>
T back_reference<T>::get() const
{
    return m_value;
}

}} // namespace boost::python

#endif // BACK_REFERENCE_DWA2002510_HPP
