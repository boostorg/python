// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef THIS_ARG_FROM_PYTHON_DWA20021122_HPP
# define THIS_ARG_FROM_PYTHON_DWA20021122_HPP

# include <boost/python/arg_from_python.hpp>

# include <boost/python/detail/not_specified.hpp>

# include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace python { namespace detail {

  template <class T, class Wrap = not_specified>
  struct this_ptr_arg_from_python : converter::arg_lvalue_from_python_base
  {
      this_ptr_arg_from_python(PyObject* x)
          : converter::arg_lvalue_from_python_base(
              converter::get_lvalue_from_python(x, converter::registered<T>::converters))
      {}

      typedef T* result_type;
      T* operator()() const
      {
          return static_cast<T*>(this->result());
      }
      
      bool use_default() const
      {
          return dynamic_cast<Wrap*>((*this)());
      }
  };
  
  template <class T, class Wrap = not_specified>
  struct this_ref_arg_from_python : this_ptr_arg_from_python<T,Wrap>
  {
      typedef this_ptr_arg_from_python<T,Wrap> base;
      this_ref_arg_from_python(PyObject* x) : base(x) {}
      typedef T& result_type;
      
      result_type operator()() const
      {
          return *this->base::operator()();
      }
  };

  // An MPL metafunction class which returns a `this' converter
  // appropriate for ArgType, where the target of the member function is
  // a class of type T.
  template <class T, class Wrap = not_specified>
  struct gen_this_from_python
  {
      // Note: there will almost always be an compile-time error if the
      // argument type is neither a reference nor a pointer, since T*
      // will be extracted in that case and passed on to the wrapped
      // function.
      template <class ArgType> struct apply
      {
          BOOST_STATIC_CONSTANT(
              bool, use_ptr
              = is_pointer<ArgType>::value
              || boost::python::detail::is_reference_to_pointer<ArgType>::value
                 && boost::python::detail::is_reference_to_const<ArgType>::value
                 && !boost::python::detail::is_reference_to_volatile<ArgType>::value);
          
          typedef typename mpl::if_c<
              use_ptr
              , this_ptr_arg_from_python<T,Wrap>
              , this_ref_arg_from_python<T,Wrap>
          >::type type;
      };
  };

  // An MPL iterator which iterates over a sequence whose first element
  // is gen_this_from_python<T> and the remainder of which is an endless
  // sequence of gen_arg_from_python
  template <class T, class Wrap = not_specified>
  struct method_args_from_python
  {
      typedef gen_this_from_python<T,Wrap> type;
      typedef args_from_python next;
  };

template <class VirtualFunction, class Default>
struct defaulted_virtual_fn
{
    defaulted_virtual_fn(VirtualFunction dispatch, Default const& default_impl)
        : dispatch(dispatch), default_impl(default_impl) {};
    
    VirtualFunction dispatch;
    Default default_impl;
};



# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct is_defaulted_virtual_fn
{ BOOST_STATIC_CONSTANT(bool, value = false); };

template <class T,class U>
struct is_defaulted_virtual_fn<defaulted_virtual_fn<T,U> >
{ BOOST_STATIC_CONSTANT(bool, value = true); };
# else
template <class T>
struct is_defaulted_virtual_fn
{
    template <class T, class U>
    static char helper(defaulted_virtual_fn<T,U>* x);
    static char (& helper(...)) [2];

    BOOST_STATIC_CONSTANT(bool, value = sizeof(helper((T*)0)) == 1);
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_defaulted_virtual_fn,(T))
};
# endif

}}} // namespace boost::python::detail

#endif // THIS_ARG_FROM_PYTHON_DWA20021122_HPP
