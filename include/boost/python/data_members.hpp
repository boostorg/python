// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DATA_MEMBERS_DWA2002328_HPP
# define DATA_MEMBERS_DWA2002328_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/return_value_policy.hpp>
# include <boost/python/return_by_value.hpp>
# include <boost/python/return_internal_reference.hpp>
# include <boost/python/arg_from_python.hpp>

# include <boost/python/object/function_object.hpp>

# include <boost/python/converter/builtin_converters.hpp>

# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/not_specified.hpp>

# include <boost/type_traits/add_const.hpp>
# include <boost/type_traits/add_reference.hpp>
# include <boost/type_traits/is_member_pointer.hpp>

# include <boost/mpl/apply_if.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/vector/vector10.hpp>

# include <boost/bind.hpp>

# include <boost/detail/workaround.hpp>

namespace boost { namespace python { 

//
// This file defines the make_getter and make_setter function
// families, which are responsible for turning pointers, references,
// and pointers-to-data-members into callable Python objects which
// can be used for attribute access on wrapped classes.
//

namespace detail
{
  //
  // Raw Getter and Setter function generators.  These class templates
  // generate static functions which can be bound together with
  // policies and wrapped to generate the python callable objects
  // mentioned above.
  //

  //
  // Generates get and set functions for access through
  // pointers-to-data-members
  //
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

          PyObject* result = cr( (c0())->*pm );
        
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

          (c0()).*pm = c1();
        
          return policies.postcall(args_, detail::none());
      }
  };

  //
  // Generates get and set functions for access through ordinary
  // pointers.  These are generally used to wrap static data members,
  // but can also be used to expose namespace-scope data as class
  // attributes.
  //
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

          *p = c0();
        
          return policies.postcall(args_, detail::none());
      }
  };

  //
  // Helper metafunction for determining the default CallPolicy to use
  // for attribute access.  If T is a [reference to a] class type X
  // whose conversion to python would normally produce a new copy of X
  // in a wrapped X class instance (as opposed to types such as
  // std::string, which are converted to native Python types, and
  // smart pointer types which produce a wrapped class instance of the
  // pointee type), to-python conversions will attempt to produce an
  // object which refers to the original C++ object, rather than a
  // copy.  See default_member_getter_policy for rationale.
  // 
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

  // Metafunction computing the default CallPolicy to use for reading
  // data members
  //
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

  // Metafunction computing the default CallPolicy to use for reading
  // non-member data.
  template <class T>
  struct default_datum_getter_policy
    : mpl::if_<
          default_getter_by_ref<T>
        , return_value_policy<reference_existing_object>
        , return_value_policy<return_by_value>
      >
  {};

  //
  // make_getter helper function family -- These helpers to
  // boost::python::make_getter are used to dispatch behavior.  The
  // third argument is a workaround for a CWPro8 partial ordering bug
  // with pointers to data members.  It should be convertible to
  // mpl::true_ iff the first argument is a pointer-to-member, and
  // mpl::false_ otherwise.  The fourth argument is for compilers
  // which don't support partial ordering at all and should always be
  // passed 0L.
  //

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
  template <class D, class P>
  inline object make_getter(D& d, P& p, mpl::false_, ...);
#endif

  // Handle non-member pointers with policies
  template <class D, class Policies>
  inline object make_getter(D* d, Policies const& policies, mpl::false_, int)
  {
      return objects::function_object(
          objects::py_function(
              ::boost::bind(
                  &detail::datum<D,Policies>::get, d, _1, _2
                  , policies)
            , mpl::vector1<D>()
          )
      );
  }
  
  // Handle non-member pointers without policies
  template <class D>
  inline object make_getter(D* d, not_specified, mpl::false_, long)
  {
      typedef typename default_datum_getter_policy<D>::type policies;
      return detail::make_getter(d, policies(), mpl::false_(), 0);
  }

  // Handle pointers-to-members with policies
  template <class C, class D, class Policies>
  inline object make_getter(D C::*pm, Policies const& policies, mpl::true_, int)
  {
    return objects::function_object(
        objects::py_function(
            ::boost::bind(
                &detail::member<D,C,Policies>::get, pm, _1, _2
                , policies)
          , mpl::vector2<D, C const*>()
        )
    );
  }
      
  // Handle pointers-to-members without policies
  template <class C, class D>
  inline object make_getter(D C::*pm, not_specified, mpl::true_, long)
  {
      typedef typename default_member_getter_policy<D>::type policies;
      return detail::make_getter(pm, policies(), mpl::true_(), 0);
  }

  // Handle references
  template <class D, class P>
  inline object make_getter(D& d, P& p, mpl::false_, ...)
  {
      // Just dispatch to the handler for pointer types.
      return detail::make_getter(&d, p, mpl::false_(), 0L);
  }

  //
  // make_setter helper function family -- These helpers to
  // boost::python::make_setter are used to dispatch behavior.  The
  // third argument is for compilers which don't support partial
  // ordering at all and should always be passed 0.
  //

  
  // Handle non-member pointers
  template <class D, class Policies>
  inline object make_setter(D* p, Policies const& policies, mpl::false_, int)
  {
      return objects::function_object(
          objects::py_function(
              ::boost::bind(
                  &detail::datum<D,Policies>::set, p, _1, _2
                  , policies)
              , mpl::vector2<void, D const&>()
          )
      );
  }

  // Handle pointers-to-members
  template <class C, class D, class Policies>
  inline object make_setter(D C::*pm, Policies const& policies, mpl::true_, int)
  {
      return objects::function_object(
          objects::py_function(
              ::boost::bind(
                  &detail::member<D,C,Policies>::set, pm, _1, _2
                  , policies)
            , mpl::vector3<void, C*, D const&>()
          )
      );
  }

  // Handle references
  template <class D, class Policies>
  inline object make_setter(D& x, Policies const& policies, mpl::false_, ...)
  {
      return detail::make_setter(&x, policies, mpl::false_(), 0L);
  }
}

//
// make_getter function family -- build a callable object which
// retrieves data through the first argument and is appropriate for
// use as the `get' function in Python properties .  The second,
// policies argument, is optional.  We need both D& and D const&
// overloads in order be able to handle rvalues.
//
template <class D, class Policies>
inline object make_getter(D& d, Policies const& policies)
{
    return detail::make_getter(d, policies, is_member_pointer<D>(), 0L);
}

template <class D, class Policies>
inline object make_getter(D const& d, Policies const& policies)
{
    return detail::make_getter(d, policies, is_member_pointer<D>(), 0L);
}

template <class D>
inline object make_getter(D& x)
{
    detail::not_specified policy;
    return detail::make_getter(x, policy, is_member_pointer<D>(), 0L);
}

#  if !BOOST_WORKAROUND(__EDG_VERSION__, <= 238) && !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
template <class D>
inline object make_getter(D const& d)
{
    detail::not_specified policy;
    return detail::make_getter(d, policy, is_member_pointer<D>(), 0L);
}
#  endif

//
// make_setter function family -- build a callable object which
// writes data through the first argument and is appropriate for
// use as the `set' function in Python properties .  The second,
// policies argument, is optional.  We need both D& and D const&
// overloads in order be able to handle rvalues.
//
template <class D, class Policies>
inline object make_setter(D& x, Policies const& policies)
{
    return detail::make_setter(x, policies, is_member_pointer<D>(), 0);
}

template <class D, class Policies>
inline object make_setter(D const& x, Policies const& policies)
{
    return detail::make_setter(x, policies, is_member_pointer<D>(), 0);
}

template <class D>
inline object make_setter(D& x)
{
    return detail::make_setter(x, default_call_policies(), is_member_pointer<D>(), 0);
}

# if !(BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || BOOST_WORKAROUND(__EDG_VERSION__, <= 238))
template <class D>
inline object make_setter(D const& x)
{
    return detail::make_setter(x, default_call_policies(), is_member_pointer<D>(), 0);
}
# endif

}} // namespace boost::python

#endif // DATA_MEMBERS_DWA2002328_HPP
