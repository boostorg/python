// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef LVALUE_FROM_PYTHON_DWA2002130_HPP
# define LVALUE_FROM_PYTHON_DWA2002130_HPP

# include <boost/python/converter/from_python.hpp>
# include <boost/python/type_from_python.hpp>

namespace boost { namespace python { 

// Utility which produces a member extractor function on platforms
// other than VC6.
template <class Class, class Member, Member (Class::*mp)>
struct get_member
{
    static Member& execute(Class& c)
    {
        return c.*mp;
    }
};

namespace detail
{
  template <class Class>
  struct extract_identity
  {
      static Class& execute(Class& c)
      {
          return c;
      }
  };
}

template <
    PyTypeObject const* python_type
    , class Value
    , class PythonObject = Value
    , class Extract = detail::extract_identity<Value>
    >
class lvalue_from_python
{
    typedef type_from_python<python_type> convertible_t;
 public:
    
    lvalue_from_python()
        : m_mutable_converter(
            &convertible_t::convertible, convert_mutable)
        
        , m_const_converter(
            &convertible_t::convertible, convert_const)

        , m_mutable_pointer_converter(
            &convertible_t::convertible, convert_mutable_pointer)
        
        , m_const_pointer_converter(
            &convertible_t::convertible, convert_const_pointer)
    {}
    
 private:
    static Value& convert_mutable(PyObject* op, converter::from_python_data&)
    {
        return Extract::execute(*(PythonObject*)op);
    }
    
    static Value const& convert_const(PyObject* op, converter::from_python_data&)
    {
        return Extract::execute(*(PythonObject*)op);
    }
    
    static Value* convert_mutable_pointer(PyObject* op, converter::from_python_data&)
    {
        return &Extract::execute(*(PythonObject*)op);
    }
    
    static Value const* convert_const_pointer(PyObject* op, converter::from_python_data&)
    {
        return &Extract::execute(*(PythonObject*)op);
    }
    
    typedef converter::from_python_converter<Value&> mutable_converter;
    typedef converter::from_python_converter<Value const&> const_converter;
    typedef converter::from_python_converter<Value*> mutable_pointer_converter;
    typedef converter::from_python_converter<Value const*> const_pointer_converter;
    
    mutable_converter m_mutable_converter;
    const_converter m_const_converter;
    mutable_pointer_converter m_mutable_pointer_converter;
    const_pointer_converter m_const_pointer_converter;
};

}} // namespace boost::python

#endif // LVALUE_FROM_PYTHON_DWA2002130_HPP
