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
# include <boost/python/object/make_instance.hpp>
# include <boost/python/object/instance.hpp>
# include <boost/type.hpp>
# include <boost/mpl/if.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/type_traits/alignment_traits.hpp>
# include <boost/mpl/bool_c.hpp>
# include <cstddef>

namespace boost { namespace python { namespace objects {

namespace detail
{
  template <class T, class Held>
  struct select_value_holder
  {
      BOOST_STATIC_CONSTANT(bool, selector = (!is_same<T,Held>::value) | has_back_reference<T>::value);
  
      typedef typename mpl::if_c<
          selector
          , value_holder_back_reference<T,Held>
          , value_holder<T>
      >::type type;

      static inline void register_()
      {
          select_value_holder::register_(mpl::bool_c<selector>());
      }

      static type* get() { return 0; }
      
   private:
      static inline void register_(mpl::bool_c<true>)
      {
          python::detail::force_instantiate(instance_finder<Held>::registration);
      }

      static inline void register_(mpl::bool_c<false>)
      {
      }
  };

  template <class T,class Ptr>
  struct select_pointer_holder
  {
      typedef typename python::pointee<Ptr>::type pointee;
      BOOST_STATIC_CONSTANT(bool, selector = (!is_same<T,pointee>::value) | has_back_reference<T>::value);
      
      typedef typename mpl::if_c<
          selector
          , pointer_holder_back_reference<Ptr,T>
          , pointer_holder<Ptr,T>
      >::type type;
      
      static inline void register_()
      {
          select_pointer_holder::register_(mpl::bool_c<selector>());
      }

      static type* get() { return 0; }
      
   private:
      static inline void register_(mpl::bool_c<true>)
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
      
      static inline void register_(mpl::bool_c<false>)
      {
          python::detail::force_instantiate(
              objects::class_wrapper<
                Ptr
                , type
                , make_instance<T,type> >());
    
          python::detail::force_instantiate(
              instance_finder<Ptr>::registration);
      }
  };
}

template <class T, class Held>
struct select_holder
{
    static inline std::size_t additional_size()
    {
        return additional_size_helper(execute((Held*)0));
    }
        
    static inline detail::select_value_holder<T,T>
    execute(python::detail::not_specified*)
    {
        return detail::select_value_holder<T,T>();
    }

    static inline detail::select_value_holder<T, Held>
    execute(T*)
    {
        return detail::select_value_holder<T, Held>();
    }

    static inline detail::select_pointer_holder<T,Held>
    execute(void*)
    {
        return detail::select_pointer_holder<T,Held>();
    }
    
 private:
    template <class Selector>
    static inline std::size_t additional_size_helper(Selector const&)
    {
        typedef typename Selector::type holder;
        return additional_instance_size<holder>::value;
    }
};

}}} // namespace boost::python::objects

#endif // SELECT_HOLDER_DWA2002322_HPP
