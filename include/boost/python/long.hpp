// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef LONG_DWA2002627_HPP
# define LONG_DWA2002627_HPP

# include <boost/python/object.hpp>
# include <boost/python/converter/pytype_arg_from_python.hpp>
# include <boost/python/converter/pytype_result_from_python.hpp>

namespace boost { namespace python { 

class long_ : public object
{
 public:
    BOOST_PYTHON_DECL long_(); // new long_
    explicit BOOST_PYTHON_DECL long_(object_cref rhs);

    template <class T>
    explicit long_(T const& rhs)
        : object(long_::call(object(rhs)))
    {
    }

    explicit BOOST_PYTHON_DECL long_(object_cref rhs, object_cref base);

    template <class T, class U>
    explicit long_(T const& rhs, U const& base)
        : object(long_::call(object(rhs), object(base)))
    {
    }
 public: // implementation detail -- for internal use only
    explicit inline long_(detail::borrowed_reference);
    explicit inline long_(detail::new_reference);
    
 private:
    static BOOST_PYTHON_DECL detail::new_reference call(object const&);
    static BOOST_PYTHON_DECL detail::new_reference call(object const&, object const&);
};

//
// Converter Specializations
//
template <class T> struct arg_from_python;

template <>
struct arg_from_python<long_>
    : converter::pytype_wrapper_value_arg_from_python<long_, &PyLong_Type>
{
    typedef converter::pytype_wrapper_value_arg_from_python<long_, &PyLong_Type> base;
    typedef long_ result_type;
    
    arg_from_python(PyObject* p) : base(p) {}
};

template <>
struct arg_from_python<long_ const&>
    : arg_from_python<long_>
{
    arg_from_python(PyObject* p)
        : arg_from_python<long_>(p) {}
};

template <>
struct arg_from_python<long_&>
    : converter::pytype_wrapper_ref_arg_from_python<long_, &PyLong_Type>
{
    typedef converter::pytype_wrapper_ref_arg_from_python<long_, &PyLong_Type> base;
    typedef long_ result_type;
    
    arg_from_python(PyObject* p)
        : base(p) {}
};

namespace converter
{
  template <class T> struct is_object_manager;

  template <>
  struct is_object_manager<long_>
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };

  template <class T> struct return_from_python;
  template <>
  struct return_from_python<long_>
  {
      typedef long_ result_type;
      
      result_type operator()(PyObject* x) const
      {
          return long_((pytype_result_from_python)(&PyLong_Type, x));
      }
  };
}

//
// long_ implementation
//
inline long_::long_(detail::borrowed_reference p)
    : object(p)
{}

inline long_::long_(detail::new_reference p)
    : object(p)
{}

}} // namespace boost::python

#endif // LONG_DWA2002627_HPP
