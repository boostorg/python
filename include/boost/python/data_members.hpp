// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DATA_MEMBERS_DWA2002328_HPP
# define DATA_MEMBERS_DWA2002328_HPP

# include <boost/python/return_value_policy.hpp>
# include <boost/python/return_by_value.hpp>
# include <boost/python/return_internal_reference.hpp>
# include <boost/python/arg_from_python.hpp>

# include <boost/python/object/function_object.hpp>

# include <boost/python/converter/builtin_converters.hpp>

# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/not_specified.hpp>

# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/add_const.hpp>
# include <boost/type_traits/add_reference.hpp>
# include <boost/type_traits/is_same.hpp>

# include <boost/mpl/apply_if.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/identity.hpp>

# include <boost/bind.hpp>

namespace boost { namespace python { 

namespace detail
{
  template <class Data, class Class, class Policies>
  struct member
  {
      static PyObject* get(Data Class::*pm, PyObject* args_, PyObject*, Policies const& policies)
      {
          arg_from_python<Class*> c0(PyTuple_GET_ITEM(args_, 0));
          if (!c0.convertible()) return 0;

          // find the result converter
          typedef typename Policies::result_converter result_converter;
          typedef typename boost::add_reference<Data>::type source;
          typename mpl::apply1<result_converter,source>::type cr;
        
          if (!policies.precall(args_)) return 0;

          PyObject* result = cr( (c0(PyTuple_GET_ITEM(args_, 0)))->*pm );
        
          return policies.postcall(args_, result);
      }
  
      static PyObject* set(Data Class::*pm, PyObject* args_, PyObject*, Policies const& policies)
      {
          // check that each of the arguments is convertible
          arg_from_python<Class&> c0(PyTuple_GET_ITEM(args_, 0));
          if (!c0.convertible()) return 0;

          typedef typename add_const<Data>::type target1;
          typedef typename add_reference<target1>::type target;
          arg_from_python<target> c1(PyTuple_GET_ITEM(args_, 1));
      
          if (!c1.convertible()) return 0;

          if (!policies.precall(args_)) return 0;

          (c0(PyTuple_GET_ITEM(args_, 0))).*pm = c1(PyTuple_GET_ITEM(args_, 1));
        
          return policies.postcall(args_, detail::none());
      }
  };

  template <class Data, class Policies>
  struct datum
  {
      static PyObject* get(Data *p, PyObject* args_, PyObject*, Policies const& policies)
      {
          // find the result converter
          typedef typename Policies::result_converter result_converter;
          typedef typename boost::add_reference<Data>::type source;
          typename mpl::apply1<result_converter,source>::type cr;
        
          if (!policies.precall(args_)) return 0;

          PyObject* result = cr( *p );
        
          return policies.postcall(args_, result);
      }
  
      static PyObject* set(Data* p, PyObject* args_, PyObject*, Policies const& policies)
      {
          // check that each of the arguments is convertible
          typedef typename add_const<Data>::type target1;
          typedef typename add_reference<target1>::type target;
          arg_from_python<target> c0(PyTuple_GET_ITEM(args_, 0));
      
          if (!c0.convertible()) return 0;

          if (!policies.precall(args_)) return 0;

          *p = c0(PyTuple_GET_ITEM(args_, 0));
        
          return policies.postcall(args_, detail::none());
      }
  };

  template <class T>
  struct default_getter_by_ref
      : mpl::and_<
          mpl::bool_<
              to_python_value<
                  typename add_reference<typename add_const<T>::type>::type
              >::uses_registry
          >
        , is_reference_to_class<
              typename add_reference<typename add_const<T>::type>::type
          >
       >
  {
  };

  // If it's a regular class type (not an object manager or other
  // type for which we have to_python specializations, use
  // return_internal_reference so that we can do things like
  //    x.y.z =  1
  // and get the right result.
  template <class T>
  struct default_member_getter_policy
      : mpl::if_<
            default_getter_by_ref<T>
          , return_internal_reference<>
          , return_value_policy<return_by_value>
        >
  {};

  template <class T>
  struct default_datum_getter_policy
      : mpl::if_<
            default_getter_by_ref<T>
          , return_value_policy<reference_existing_object>
          , return_value_policy<return_by_value>
        >
  {};

  template <class D, class Policies>
  inline object make_getter(D* p, Policies const& policies, int)
  {
      return objects::function_object(
              ::boost::bind(
                  &detail::datum<D,Policies>::get, p, _1, _2
                  , policies)
          , 0);
  }

  template <class D>
  inline object make_getter(D* p, not_specified, long)
  {
      typedef typename default_datum_getter_policy<D>::type policies;
      return make_getter(p, policies(), 0L);
  }

  template <class C, class D, class Policies>
  inline object make_getter(D C::*pm, Policies const& policies, int)
  {
    return objects::function_object(
            ::boost::bind(
                &detail::member<D,C,Policies>::get, pm, _1, _2
                , policies)
        , 1);
  }
      
  template <class C, class D>
  inline object make_getter(D C::*pm, not_specified, long)
  {
      typedef typename default_member_getter_policy<D>::type policies;
      return make_getter(pm, policies(), 0L);
  }
      
  template <class D, class Policies>
  inline object make_getter(D& d, Policies const& policies, ...)
  {
      return detail::make_getter(&d, policies, 0L);
  }

  template <class D, class Policies>
  inline object make_setter(D* p, Policies const& policies, long)
  {
      return objects::function_object(
          ::boost::bind(
              &detail::datum<D,Policies>::set, p, _1, _2
              , policies)
          , 1);
  }

  template <class C, class D, class Policies>
  inline object make_setter(D C::*pm, Policies const& policies, long)
  {
      return objects::function_object(
          ::boost::bind(
              &detail::member<D,C,Policies>::set, pm, _1, _2
              , policies)
          , 2);
  }

  template <class D, class Policies>
  inline object make_setter(D& x, Policies const& policies, ...)
  {
      return detail::make_setter(&x, policies, 0L);
  }
}

template <class D, class Policies>
inline object make_getter(D& d, Policies const& policies)
{
    return detail::make_getter(d, policies, 0L);
}

template <class D>
inline object make_getter(D& x)
{
    return detail::make_getter(x, detail::not_specified(), 0L);
}
  
template <class D, class Policies>
inline object make_setter(D& x, Policies const& policies)
{
    return detail::make_setter(x, policies, 0L);
}

template <class D>
inline object make_setter(D& x)
{
    return detail::make_setter(x, default_call_policies(), 0L);
}

}} // namespace boost::python

#endif // DATA_MEMBERS_DWA2002328_HPP
