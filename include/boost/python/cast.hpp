// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CAST_DWA200269_HPP
# define CAST_DWA200269_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/type.hpp>
# include <boost/python/base_type_traits.hpp>
# include <boost/python/detail/convertible.hpp>

namespace boost { namespace python { 

namespace detail
{
  template <class Target>
  inline Target* upcast(Target* p, yes_convertible)
  {
      return p;
  }

  template <class Target, class Source>
  inline Target* upcast(Source* p, no_convertible, boost::type<Target>* = 0)
  {
      typedef typename base_type_traits<Source>::type base;
      return detail::upcast<Target>((base*)p, convertible<Target*>::check((base*)0));
  }


  template <class Target, class Source>
  inline Target* downcast(Source* p, yes_convertible)
  {
      return static_cast<Target*>(p);
  }

  template <class Target, class Source>
  inline Target* downcast(Source* p, no_convertible, boost::type<Target>* = 0)
  {
      typedef typename base_type_traits<Source>::type base;
      return (Target*)detail::downcast<base>(p, convertible<Source*>::check((base*)0));
  }

  template <class T>
  inline void assert_castable(boost::type<T>* = 0)
  {
      typedef char must_be_a_complete_type[sizeof(T)];
  }
}

template <class Target, class Source>
inline Target* upcast(Source* x, Target* = 0)
{
    detail::assert_castable<Source>();
    detail::assert_castable<Target>();
    return detail::upcast<Target>(x, detail::convertible<Target*>::check(x));
}

template <class Target, class Source>
inline Target* downcast(Source* x, Target* = 0)
{
    detail::assert_castable<Source>();
    detail::assert_castable<Target>();
    return detail::downcast<Target>(x, detail::convertible<Source*>::check((Target*)0));
}

}} // namespace boost::python

#endif // CAST_DWA200269_HPP
