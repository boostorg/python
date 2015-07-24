// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef REFERENT_STORAGE_DWA200278_HPP
# define REFERENT_STORAGE_DWA200278_HPP
# include <boost/mpl/if.hpp>
# include <cstddef>
# include <boost/align/align.hpp>
# include <boost/python/detail/alignment_of.hpp>
# include <boost/type_traits/aligned_storage.hpp>

namespace boost { namespace python { namespace detail {

  // Compute the size of T's referent. We wouldn't need this at all,
  // but sizeof() is broken in CodeWarriors <= 8.0
  template <class T> struct referent_size;
  
  
  template <class T>
  struct referent_size<T&>
  {
      BOOST_STATIC_CONSTANT(
          std::size_t, value = sizeof(T));
  };


// A metafunction returning a POD type which can store U, where T ==
// U&. If T is not a reference type, returns a POD which can store T.
template <class T>
struct referent_storage
{
    typedef typename ::boost::aligned_storage< ::boost::python::detail::referent_size<T>::value, alignment_of<T>::value>::type type;
    type storage;
};

}}} // namespace boost::python::detail

#endif // REFERENT_STORAGE_DWA200278_HPP
