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
      typedef typename converter::source<value_type>::type source;
      typedef converter::wrap_<source> wrap;
      typedef converter::wrap_more_<source> wrap_more;

      typedef typename converter::target<value_type>::type target;
      typedef converter::unwrap_<target> unwrap;
      typedef converter::unwrap_more_<target> unwrap_more;
  };
}

template <class T>
struct wrap : detail::converter_gen<T>::wrap
{
    typedef typename detail::converter_gen<T>::wrap base;
};

template <class T>
struct wrap_more : detail::converter_gen<T>::wrap_more
{
    typedef typename detail::converter_gen<T>::wrap_more base;
    wrap_more(converter::handle& prev);
};

template <class T>
struct unwrap : detail::converter_gen<T>::unwrap
{
    typedef typename detail::converter_gen<T>::unwrap base;
    unwrap(PyObject*);
};

template <class T>
struct unwrap_more : detail::converter_gen<T>::unwrap_more
{
    typedef typename detail::converter_gen<T>::unwrap_more base;
    unwrap_more(PyObject*, converter::handle& prev);
};

//
// implementations
//
template <class T>
inline wrap_more<T>::wrap_more(converter::handle& prev)
    : base(prev)
{
}

template <class T>
inline unwrap<T>::unwrap(PyObject* source)
    : base(source)
{
}

template <class T>
inline unwrap_more<T>::unwrap_more(PyObject* source, converter::handle& prev)
    : base(source, prev)
{
}

}} // namespace boost::python

#endif // CONVERT_DWA20011129_HPP
