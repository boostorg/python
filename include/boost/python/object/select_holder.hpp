// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef SELECT_HOLDER_DWA2002322_HPP
# define SELECT_HOLDER_DWA2002322_HPP

# include <boost/python/has_back_reference.hpp>
# include <boost/python/detail/not_specified.hpp>
# include <boost/python/detail/pointee.hpp>
# include <boost/python/detail/if_else.hpp>
# include <boost/python/object/value_holder.hpp>
# include <boost/python/object/pointer_holder.hpp>
# include <boost/type.hpp>
# include <boost/mpl/select_type.hpp>

namespace boost { namespace python { namespace objects {

namespace detail
{
  template <class T, class Held>
  struct select_value_holder
  {
      typedef typename mpl::select_type<
          (!is_same<T,Held>::value) | has_back_reference<T>::value
          , value_holder_back_reference<T,Held>
          , value_holder<T>
      >::type holder;

      static holder* get() { return 0; }
  };

  template <class T,class Ptr>
  struct select_pointer_holder
  {
      typedef typename python::detail::pointee<Ptr>::type pointee;
      
      typedef typename mpl::select_type<
          (!is_same<pointee,T>::value) | has_back_reference<T>::value
          , pointer_holder_back_reference<Ptr,T>
          , pointer_holder<Ptr,T>
      >::type holder;
      
      static holder* get() { return 0; }
  };
}

template <class T, class NotSpecified>
inline detail::select_value_holder<T,T> select_holder(python::detail::not_specified*, T* = 0, NotSpecified* = 0)
{
    return detail::select_value_holder<T,T>();
}

template <class T, class Held>
inline detail::select_value_holder<T, Held> select_holder(T*, Held* = 0)
{
    return detail::select_value_holder<T, Held>();
}


template <class T, class Ptr>
detail::select_pointer_holder<T,Ptr> select_holder(void*, Ptr* = 0, T* = 0)
{
    return detail::select_pointer_holder<T,Ptr>();
}

}}} // namespace boost::python::objects

#endif // SELECT_HOLDER_DWA2002322_HPP
