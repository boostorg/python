// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef SELECT_HOLDER_DWA2002322_HPP
# define SELECT_HOLDER_DWA2002322_HPP

# include <boost/python/has_back_reference.hpp>
# include <boost/python/detail/not_specified.hpp>
# include <boost/python/pointee.hpp>
# include <boost/python/object/value_holder.hpp>
# include <boost/python/object/pointer_holder.hpp>
# include <boost/python/object/find_instance.hpp>
# include <boost/type.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/mpl/bool_t.hpp>

namespace boost { namespace python { namespace objects {

namespace detail
{
  template <class T, class Held>
  struct select_value_holder
  {
      BOOST_STATIC_CONSTANT(bool, selector = (!is_same<T,Held>::value) | has_back_reference<T>::value);
  
      typedef typename mpl::select_type<
          selector
          , value_holder_back_reference<T,Held>
          , value_holder<T>
      >::type type;

      static inline void register_()
      {
          select_value_holder::register_(mpl::bool_t<selector>());
      }

      static type* get() { return 0; }
      
   private:
      static inline void register_(mpl::bool_t<true>)
      {
          python::detail::force_instantiate(instance_finder<Held>::registration);
      }

      static inline void register_(mpl::bool_t<false>)
      {
      }
  };

  template <class T,class Ptr>
  struct select_pointer_holder
  {
      typedef typename python::pointee<Ptr>::type pointee;
      BOOST_STATIC_CONSTANT(bool, selector = (!is_same<T,pointee>::value) | has_back_reference<T>::value);
      
      typedef typename mpl::select_type<
          selector
          , pointer_holder_back_reference<Ptr,T>
          , pointer_holder<Ptr,T>
      >::type type;
      
      static inline void register_()
      {
          select_pointer_holder::register_(mpl::bool_t<selector>());
      }

      static type* get() { return 0; }
      
   private:
      static inline void register_(mpl::bool_t<true>)
      {
          // not implemented at least until we solve the back
          // reference issue mentioned in pointer_holder.hpp.
          //
          //    python::detail::force_instantiate(
          //          class_wrapper<Pointer,pointer_holder_back_reference<Pointer,Value> >());
          
          python::detail::force_instantiate(instance_finder<Ptr>::registration);
          python::detail::force_instantiate(instance_finder<pointee>::registration);
      }

      struct construct_from_pointer
      {
          static type* execute(PyObject*, Ptr x)
          {
              return new type(x);
          }
      };
      
      static inline void register_(mpl::bool_t<false>)
      {
          python::detail::force_instantiate(
              objects::class_wrapper<
                Ptr
                , type
                , construct_from_pointer>());
    
          python::detail::force_instantiate(
              instance_finder<Ptr>::registration);
      }
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
