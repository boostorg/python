// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARG_TO_PYTHON_DWA200265_HPP
# define ARG_TO_PYTHON_DWA200265_HPP

# include <boost/python/ptr.hpp>
# include <boost/python/converter/to_python_function.hpp>
# include <boost/python/converter/pointee_to_python_function.hpp>
# include <boost/python/converter/arg_to_python_base.hpp>
# include <boost/python/to_python_indirect.hpp>
// Bring in specializations
# include <boost/python/converter/builtin_converters.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{
  BOOST_PYTHON_DECL void throw_no_class_registered();

  template <class T>
  struct reference_arg_to_python : handle<>
  {
      reference_arg_to_python(T& x);
   private:
      static PyObject* get_object(T& x);
  };

  template <class T>
  struct value_arg_to_python : arg_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      value_arg_to_python(T const&);
  };

  template <class Ptr>
  struct pointer_deep_arg_to_python : arg_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      pointer_deep_arg_to_python(Ptr);
  };

  template <class Ptr>
  struct pointer_shallow_arg_to_python : handle<>
  {
      // Throw an exception if the conversion can't succeed
      pointer_shallow_arg_to_python(Ptr);
   private:
      static PyObject* get_object(Ptr p);
  };

  template <class T>
  struct select_arg_to_python
  {
      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
      
      BOOST_STATIC_CONSTANT(
          bool, ref_wrapper = is_reference_wrapper<T>::value);

      BOOST_STATIC_CONSTANT(
          bool, ptr_wrapper = is_pointer_wrapper<T>::value);

      typedef typename unwrap_reference<T>::type unwrapped_referent;
      typedef typename unwrap_pointer<T>::type unwrapped_ptr;

      typedef typename mpl::select_type<
          ptr
          , pointer_deep_arg_to_python<T>
          , typename mpl::select_type<
              ptr_wrapper
              , pointer_shallow_arg_to_python<unwrapped_ptr>
              , typename mpl::select_type<
                  ref_wrapper
                  , reference_arg_to_python<unwrapped_referent>
                  , value_arg_to_python<T>
                >::type
            >::type
        >::type type;
  };
}

template <class T>
struct arg_to_python
    : detail::select_arg_to_python<T>::type
{
    typedef typename detail::select_arg_to_python<T>::type base;
 public: // member functions
    // Throw an exception if the conversion can't succeed
    arg_to_python(T const& x);
};

//
// Convenience macros for call<> and call_method<> code generation
//
# define BOOST_PYTHON_ARG_TO_PYTHON_GET(index,ignored)     \
    converter::arg_to_python<BOOST_PP_CAT(A,index)>(       \
        BOOST_PP_CAT(a,index)).get()

# define BOOST_PYTHON_ARG_STRING(nargs)                         \
    "(" BOOST_PP_REPEAT(nargs,BOOST_PYTHON_PROJECT_2ND,"O") ")"


//
// implementations
//
namespace detail
{
  template <class T>
  inline value_arg_to_python<T>::value_arg_to_python(T const& x)
      : arg_to_python_base(&x, to_python_function<T>::value)
  {
  }

  template <class Ptr>
  inline pointer_deep_arg_to_python<Ptr>::pointer_deep_arg_to_python(Ptr x)
      : arg_to_python_base(x, pointee_to_python_function<Ptr>::value)
  {
  }

  template <class T>
  inline PyObject* reference_arg_to_python<T>::get_object(T& x)
  {
      to_python_indirect<T&,python::detail::make_reference_holder> convert;
      if (!convert.convertible())
          throw_no_class_registered();
      return convert(x);
  }

  template <class T>
  inline reference_arg_to_python<T>::reference_arg_to_python(T& x)
      : handle<>(get_object(x))
  {
  }

  template <class Ptr>
  inline pointer_shallow_arg_to_python<Ptr>::pointer_shallow_arg_to_python(Ptr x)
      : handle<>(get_object(x))
  {}

  template <class Ptr>
  inline PyObject* pointer_shallow_arg_to_python<Ptr>::get_object(Ptr x)
  {
      to_python_indirect<Ptr,python::detail::make_reference_holder> convert;
      if (!convert.convertible())
          throw_no_class_registered();
      return x ? convert(x) : python::detail::none();
  }
}

template <class T>
inline arg_to_python<T>::arg_to_python(T const& x)
    : base(x)
{}

}}} // namespace boost::python::converter

#endif // ARG_TO_PYTHON_DWA200265_HPP
