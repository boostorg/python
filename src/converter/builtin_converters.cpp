// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/detail/config.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <boost/python/converter/target.hpp>
#include <boost/python/converter/from_python.hpp>
#include <boost/python/reference.hpp>
#include <boost/cast.hpp>
//#include <boost/mpl/type_list.hpp>
#include <string>

namespace boost { namespace python { namespace converter {

namespace
{
  struct int_value_functions_base
  {
      static void* convertible(PyObject* obj)
      {
          PyNumberMethods* number_methods = obj->ob_type->tp_as_number;
      
          return number_methods && number_methods->nb_int
              ? &number_methods->nb_int : 0;
      }
  };
  
  template <class T>
  struct int_value_functions : int_value_functions_base
  {
      static T convert(PyObject* obj, from_python_data& data)
      {
          unaryfunc f = *static_cast<unaryfunc*>(data.stage1);
          ref int_object(f(obj));
          return numeric_cast<T>(PyInt_AsLong(int_object.get()));
      }
  };

  struct cstring_value_functions
  {
      static void* convertible(PyObject* obj)
      {
          return PyString_Check(obj) ? obj : 0;
      }
      
      static char const* convert(PyObject* obj, from_python_data&)
      {
          return PyString_AsString(obj);
      }
  };

  char constructed;
  
  struct string_cref_functions
  {
      typedef std::string const& result_type;
      
      static void* convertible(PyObject* obj)
      {
          return obj->ob_type->tp_str ? &obj->ob_type->tp_str : 0;
      }
      
      static std::string const& convert(
          PyObject* obj, from_python_data& data)
      {
          ref string_object((**static_cast<reprfunc*>(data.stage1))(obj));
          void* storage = get_storage<result_type>(data);
          std::string* p = new (storage) std::string(PyString_AsString(string_object.get()));
          
          // note that construction is successful.
          data.stage1 = &constructed; 
          return *p;
      }

      static void destroy(from_python_data& data)
      {
          if (data.stage1 == &constructed)
          {
              typedef std::string string_t;
              void* storage = get_storage<result_type>(data);
              ((string_t*)storage)->~string_t();
          }
      }
  };

  template <class T, class Base>
  struct rvalue_const_ref_functions : Base
  {
      static T const& convert(PyObject* obj, from_python_data& data)
      {
          void* storage = get_storage<T const&>(data);
          T* p = new (storage) T(Base::convert(obj,data));
          
          // note that construction is successful.
          data.stage1 = &constructed; 
          return *p;
      }
  };

  struct register_int_converters
  {
      template <class Ignored, class T>
      struct apply
      {
          typedef void type;
          
          static void execute()
          {
              typedef int_value_functions<T> value_functions;
              typedef rvalue_const_ref_functions<T,value_functions> cref_functions;
              
              static from_python_converter<T> value_from_python( 
                  value_functions::convertible 
                  , value_functions::convert);
              static from_python_converter<T const&> cref_from_python(
                  cref_functions::convertible
                  , cref_functions::convert);
          };
      };
  };
}  

#define REGISTER_INT_CONVERTERS(U) register_int_converters::apply<void,U>::execute()
#define REGISTER_INT_CONVERTERS2(U) REGISTER_INT_CONVERTERS(signed U); REGISTER_INT_CONVERTERS(unsigned U)  


void initialize_builtin_converters()
{
    REGISTER_INT_CONVERTERS2(char);
    REGISTER_INT_CONVERTERS2(short);
    REGISTER_INT_CONVERTERS2(int);
    REGISTER_INT_CONVERTERS2(long);
//    mpl::for_each<integral_types,void,register_int_converters>::execute();

    static from_python_converter<char const*> cstring_from_python(
        &cstring_value_functions::convertible
        , &cstring_value_functions::convert);

    static from_python_converter<char const*const&> cstring_cref_from_python(
        &rvalue_const_ref_functions<char const*,cstring_value_functions>::convertible
        , &rvalue_const_ref_functions<char const*, cstring_value_functions>::convert);

    static from_python_converter<std::string const&> string_cref_from_python(
        &string_cref_functions::convertible
        , &string_cref_functions::convert
        , &string_cref_functions::destroy);
}

}}} // namespace boost::python::converter
