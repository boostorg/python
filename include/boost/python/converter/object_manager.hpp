// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef OBJECT_MANAGER_DWA2002614_HPP
# define OBJECT_MANAGER_DWA2002614_HPP

# include <boost/python/handle.hpp>
# include <boost/python/cast.hpp>
# include <boost/type_traits/object_traits.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/python/detail/indirect_traits.hpp>

namespace boost { namespace python { namespace api {

class object;

}}}

namespace boost { namespace python { namespace converter { 

template <class T>
struct is_object_manager
{
 private:
    BOOST_STATIC_CONSTANT(bool, hdl = is_handle<T>::value);
    BOOST_STATIC_CONSTANT(bool, borrowed = python::detail::is_borrowed_ptr<T>::value);
 public:
    BOOST_STATIC_CONSTANT(bool, value = (hdl | borrowed));
};

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct is_reference_to_object_manager
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_reference_to_object_manager<T&>
    : is_object_manager<T>
{
};

template <class T>
struct is_reference_to_object_manager<T const&>
    : is_object_manager<T>
{
};

template <class T>
struct is_reference_to_object_manager<T volatile&>
    : is_object_manager<T>
{
};

template <class T>
struct is_reference_to_object_manager<T const volatile&>
    : is_object_manager<T>
{
};
# else

namespace detail
{
  typedef char (&yes_reference_to_object_manager)[1];
  typedef char (&no_reference_to_object_manager)[2];

  template <class T>
  struct is_object_manager_help
      : mpl::select_type<
           is_object_manager<T>::value
           , yes_reference_to_object_manager
           , no_reference_to_object_manager>
  {
  };

  template <bool is_ref = false>
  struct is_reference_to_object_manager_helper
  {
      template <class T>
      struct apply
      {
          static int x;
          static no_reference_to_object_manager check(...);
      };
  };

  template <class U>
  typename is_object_manager_help<U>::type
  is_object_manager_helper(int*, double, double, U&);
  
  template <class U>
  typename is_object_manager_help<U>::type
  is_object_manager_helper(int*, int*, double, U const&);
  
  template <class U>
  typename is_object_manager_help<U>::type
  is_object_manager_helper(int*, double, int*, U volatile&);
  
  template <class U>
  typename is_object_manager_help<U>::type
  is_object_manager_helper(int*, int*, int*, U const volatile&);

  no_reference_to_object_manager is_object_manager_helper(...);
}

template <class T>
struct is_reference_to_object_manager
{
    typedef typename mpl::select_type<
        is_reference<T>::value, int*, double>::type r_t;
    typedef typename mpl::select_type<
        python::detail::is_reference_to_const<T>::value, int*, double>::type rc_t;
    typedef typename mpl::select_type<
        python::detail::is_reference_to_volatile<T>::value, int*, double>::type rv_t;
    
    typedef typename mpl::select_type<is_reference<T>::value, T, int>::type value_t;

    static value_t sample_object;
    
    BOOST_STATIC_CONSTANT(
        bool, value
        = (sizeof(detail::is_object_manager_helper(r_t(),rc_t(),rv_t(),sample_object))
           == sizeof(detail::yes_reference_to_object_manager)
          )
        );
};
# endif 

template <class T>
inline T* get_managed_object(handle<T> const& h)
{
    return h.get();
}
    
template <class T>
inline T* get_managed_object(python::detail::borrowed<T> const volatile* p)
{
    return (T*)p;
}

// forward declaration needed because name lookup is bound by the
// definition context.
PyObject* get_managed_object(python::api::object const&);

}}} // namespace boost::python::converter

#endif // OBJECT_MANAGER_DWA2002614_HPP
