// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CONVERT_DWA20011129_HPP
# define CONVERT_DWA20011129_HPP

# include <boost/python/converter/target.hpp>
# include <boost/python/converter/source.hpp>
# include <boost/python/converter/wrap.hpp>
# include <boost/python/converter/unwrap.hpp>

namespace boost { namespace python {

namespace detail
{
  template <class T>
  struct converter_gen
  {
      typedef T value_type;
      typedef typename converter::source<value_type>::type source_t;
      typedef converter::wrap_<source_t> wrap_t;
      typedef converter::wrap_more_<source_t> wrap_more_t;

      typedef typename converter::target<value_type>::type target_t;
      typedef converter::unwrap_<target_t> unwrap_t;
      typedef converter::unwrap_more_<target_t> unwrap_more_t;
  };
}

template <class T>
struct wrap : detail::converter_gen<T>::wrap_t
{
    typedef typename detail::converter_gen<T>::wrap_t base_t;
    typedef typename detail::converter_gen<T>::source_t source_t;
};

template <class T>
struct wrap_more : detail::converter_gen<T>::wrap_more_t
{
    typedef typename detail::converter_gen<T>::wrap_more_t base_t;
    typedef typename detail::converter_gen<T>::source_t source_t;
    wrap_more(converter::handle& prev);
};

template <class T>
struct unwrap : detail::converter_gen<T>::unwrap_t
{
    typedef typename detail::converter_gen<T>::unwrap_t base_t;
    unwrap(PyObject*);
};

template <class T>
struct unwrap_more : detail::converter_gen<T>::unwrap_more_t
{
    typedef typename detail::converter_gen<T>::unwrap_more_t base_t;
    unwrap_more(PyObject*, converter::handle& prev);
};

//
// implementations
//
template <class T>
inline wrap_more<T>::wrap_more(converter::handle& prev)
    : base_t(prev)
{
}

template <class T>
inline unwrap<T>::unwrap(PyObject* source)
    : base_t(source)
{
}

template <class T>
inline unwrap_more<T>::unwrap_more(PyObject* source, converter::handle& prev)
    : base_t(source, prev)
{
}

}} // namespace boost::python

#endif // CONVERT_DWA20011129_HPP
