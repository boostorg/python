// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DATA_MEMBERS_DWA2002328_HPP
# define DATA_MEMBERS_DWA2002328_HPP

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/python/return_value_policy.hpp>
# include <boost/python/copy_non_const_reference.hpp>
# include <boost/python/object/function_object.hpp>
# include <boost/python/arg_from_python.hpp>
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
          if (!cr.convertible()) return 0;
        
          if (!policies.precall(args_)) return 0;

          PyObject* result = cr( (c0(PyTuple_GET_ITEM(args_, 0)))->*pm );
        
          return policies.postcall(args_, result);
      }
  
      static PyObject* set(Data Class::*pm, PyObject* args_, PyObject*, Policies const& policies)
      {
          // check that each of the arguments is convertible
          arg_from_python<Class*> c0(PyTuple_GET_ITEM(args_, 0));
          if (!c0.convertible()) return 0;

          typedef typename add_const<Data>::type target1;
          typedef typename add_reference<target1>::type target;
          arg_from_python<target> c1(PyTuple_GET_ITEM(args_, 1));
      
          if (!c1.convertible()) return 0;

          if (!policies.precall(args_)) return 0;

          (c0(PyTuple_GET_ITEM(args_, 0)))->*pm = c1(PyTuple_GET_ITEM(args_, 1));
        
          return policies.postcall(args_, detail::none());
      }
  };
}

template <class C, class D>
object make_getter(D C::*pm)
{
    typedef return_value_policy<copy_non_const_reference> default_policy;
    
    return objects::function_object(
        ::boost::bind(
            &detail::member<D,C,default_policy>::get, pm, _1, _2
            , default_policy())
        , 1);
        
}

template <class C, class D, class Policies>
object make_getter(D C::*pm, Policies const& policies)
{
    return objects::function_object(
            ::boost::bind(
                &detail::member<D,C,Policies>::get, pm, _1, _2
                , policies)
        , 1);
}

template <class C, class D>
object make_setter(D C::*pm)
{
    return objects::function_object(
        ::boost::bind(
            &detail::member<D,C,default_call_policies>::set, pm, _1, _2
            , default_call_policies())
        , 2);
}

template <class C, class D, class Policies>
object make_setter(D C::*pm, Policies const& policies)
{
    return objects::function_object(
        ::boost::bind(
            &detail::member<D,C,Policies>::set, pm, _1, _2
            , policies)
        , 2);
}

    
}} // namespace boost::python

#endif // DATA_MEMBERS_DWA2002328_HPP
