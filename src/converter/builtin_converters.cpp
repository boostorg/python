// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/detail/config.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <boost/python/converter/target.hpp>
#include <boost/python/value_from_python.hpp>
#include <boost/python/converter/from_python_data.hpp>
#include <boost/python/reference.hpp>
#include <boost/cast.hpp>
//#include <boost/mpl/type_list.hpp>
#include <string>

namespace boost { namespace python { namespace converter {

namespace
{
  // Only an object which we know is holding a char const* can be
  // converted to one
  struct convertible_to_cstring
  {
      static unaryfunc* execute(PyObject* obj)
      {
          return PyString_Check(obj) ? &obj->ob_type->tp_str : 0;
      }
  };

  struct extract_cstring
  {
      static char const* execute(PyObject* obj)
      {
          return PyString_AsString(obj);
      }
  };

  // Any object which can be converted to a Python string can also be
  // converted to a C++ string, since the latter owns its bytes.
  struct convertible_to_string
  {
      static unaryfunc* execute(PyObject* obj)
      {
          return obj->ob_type->tp_str ? &obj->ob_type->tp_str : 0;
      }
  };
  
  // Transform a function returning a unaryfunc* into one that returns a void*
  template <class F>
  struct return_void_ptr
  {
      static void* execute(PyObject* p) { return F::execute(p); }
  };
  
  template <
      class T                   // The target type
      , class Convertible       // returns a pointer to a unaryfunc producing an object
      , class TExtract          // ...from which TExtract extracts T's constructor argument
      >
  struct tp_scalar_from_python
      : from_python_converter<T>
  {
   private:
      typedef return_void_ptr<Convertible> convertible_fn;
      
   public:
      tp_scalar_from_python()
          : from_python_converter<T>(
              &convertible_fn::execute
              , convert)
      {}
      
      static T convert(PyObject* obj, from_python_data& data)
      {
          unaryfunc converter = *(unaryfunc*)data.stage1;
          ref converted(converter(obj));
          return TExtract::execute(converted.get());
      }
  };

  // Extract a reference to T using the functions in the source
  // object's type slots
  template <
      class T                   // The target type
      , class Convertible       // returns a pointer to a unaryfunc producing an object
      , class TExtract          // ...from which TExtract extracts T's constructor argument
      >
  struct tp_cref_from_python
      : value_from_python<T, tp_cref_from_python<T,Convertible,TExtract> >
  {
   private:
      typedef value_from_python<T, tp_cref_from_python<T,Convertible,TExtract> > base;
      
   public:
      tp_cref_from_python()
          : base(&return_void_ptr<Convertible>::execute)
      {}
      
      static T const& convert(PyObject* obj, from_python_data& data)
      {
          unaryfunc converter = *(unaryfunc*)data.stage1;
          
          void* storage = get_storage(data);
          
          ref converted(converter(obj));
              
          T* const p = new (storage) T(TExtract::execute(converted.get()));
          
          // note that construction is successful.
          data.stage1 = p;
          
          return *p;
      }
  };

  struct convertible_to_int
  {
      static unaryfunc* execute(PyObject* obj)
      {
          PyNumberMethods* number_methods = obj->ob_type->tp_as_number;
          if (number_methods == 0)
              return 0;

          // For floating types, return the float conversion slot to avoid
          // creating a new object. We'll handle that in
          // py_int_or_float_as_long, below
          if (PyObject_TypeCheck(obj, &PyFloat_Type) && number_methods->nb_float)
              return &number_methods->nb_float;
      
          return number_methods && number_methods->nb_int
              ? &number_methods->nb_int : 0;
      }
  };

  struct py_int_or_float_as_long
  {
      static long execute(PyObject* obj)
      {
          if (PyObject_TypeCheck(obj, &PyFloat_Type))
          {
              return numeric_cast<long>(PyFloat_AS_DOUBLE(obj));
          }
          else
          {
              return PyInt_AS_LONG(obj);
          }
      }
  };

  struct convertible_to_double
  {
      static unaryfunc* execute(PyObject* obj)
      {
          PyNumberMethods* number_methods = obj->ob_type->tp_as_number;
          if (number_methods == 0)
              return 0;

          // For integer types, return the tp_int conversion slot to avoid
          // creating a new object. We'll handle that in
          // py_float_or_int_as_double, below
          if (PyObject_TypeCheck(obj, &PyInt_Type) && number_methods->nb_int)
              return &number_methods->nb_int;
      
          return number_methods && number_methods->nb_float
              ? &number_methods->nb_float : 0;
      }
  };

  struct py_float_or_int_as_double
  {
      static double execute(PyObject* obj)
      {
          if (PyObject_TypeCheck(obj, &PyInt_Type))
          {
              return PyInt_AS_LONG(obj);
          }
          else
          {
              return PyFloat_AS_DOUBLE(obj);
          }
      }
  };

  template <class T, class Convertible, class Convert>
  struct scalar_from_python
  {
      tp_cref_from_python<T,Convertible,Convert> cref_converter;
      tp_scalar_from_python<T,Convertible,Convert> value_converter;
  };
  
  template <class T>
  void register_int_converters(T* = 0)
  {
      static scalar_from_python<T, convertible_to_int, py_int_or_float_as_long> x;
  }
}    

#define REGISTER_INT_CONVERTERS(U) register_int_converters<U>()
#define REGISTER_INT_CONVERTERS2(U) REGISTER_INT_CONVERTERS(signed U); REGISTER_INT_CONVERTERS(unsigned U)  

void initialize_builtin_converters()
{
    REGISTER_INT_CONVERTERS2(char);
    REGISTER_INT_CONVERTERS2(short);
    REGISTER_INT_CONVERTERS2(int);
    REGISTER_INT_CONVERTERS2(long);

    static scalar_from_python<
        float,convertible_to_double,py_float_or_int_as_double> float_from_python;
    
    static scalar_from_python<
        double,convertible_to_double,py_float_or_int_as_double> double_from_python;
    
    static scalar_from_python<
        long double,convertible_to_double,py_float_or_int_as_double> long_double_from_python;
    
    static scalar_from_python<
        char const*, convertible_to_cstring, extract_cstring> cstring_from_python;

    static tp_cref_from_python<
        std::string, convertible_to_string, extract_cstring> string_from_python;
}

}}} // namespace boost::python::converter
