// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/detail/config.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <boost/python/converter/from_python_data.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/reference.hpp>
#include <boost/python/errors.hpp>
#include <boost/cast.hpp>
#include <string>
#include <complex>

namespace boost { namespace python { namespace converter {

namespace
{
  // An lvalue conversion function which extracts a char const* from a
  // Python String.
  void* convert_to_cstring(PyObject* obj)
  {
      return PyString_Check(obj) ? PyString_AsString(obj) : 0;
  }

  // Given a target type and a SlotPolicy describing how to perform a
  // given conversion, registers from_python converters which use the
  // SlotPolicy to extract the type.
  template <class T, class SlotPolicy>
  struct slot_rvalue_from_python
  {
   public:
      slot_rvalue_from_python()
      {
          registry::insert(
              &slot_rvalue_from_python<T,SlotPolicy>::convertible
              , &slot_rvalue_from_python<T,SlotPolicy>::construct
              , undecorated_type_id<T>()
              );
      }
      
   private:
      static void* convertible(PyObject* obj)
      {
          unaryfunc* slot = SlotPolicy::get_slot(obj);
          return slot && *slot ? slot : 0;
      }

      static void construct(PyObject* obj, rvalue_stage1_data* data)
      {
          // Get the (intermediate) source object
          unaryfunc creator = *static_cast<unaryfunc*>(data->convertible);
          ref intermediate(creator(obj));

          // Get the location in which to construct
          void* storage = ((rvalue_data<T>*)data)->storage.bytes;
          new (storage) T(SlotPolicy::extract(intermediate.get()));

          // record successful construction
          data->convertible = storage;
      }
  };

  // A SlotPolicy for extracting integer types from Python objects
  struct int_rvalue_from_python
  {
      static unaryfunc* get_slot(PyObject* obj)
      {
          PyNumberMethods* number_methods = obj->ob_type->tp_as_number;
          if (number_methods == 0)
              return 0;

          // For floating types, return the float conversion slot to avoid
          // creating a new object. We'll handle that below
          if (PyFloat_Check(obj))
              return &number_methods->nb_float;

          if (PyInstance_Check(obj) && !PyObject_HasAttrString(obj, "__int__"))
              return 0;
          
          return &number_methods->nb_int;
      }
      
      static long extract(PyObject* intermediate)
      {
          if (PyFloat_Check(intermediate))
          {
              return numeric_cast<long>(PyFloat_AS_DOUBLE(intermediate));
          }
          else
          {
              return PyInt_AS_LONG(intermediate);
          }
      }
  };


  // identity_unaryfunc/py_object_identity -- manufacture a unaryfunc
  // "slot" which just returns its argument. Used for bool
  // conversions, since all Python objects are directly convertible to
  // bool
  extern "C" PyObject* identity_unaryfunc(PyObject* x)
  {
      Py_INCREF(x);
      return x;
  }
  unaryfunc py_object_identity = identity_unaryfunc;

  // A SlotPolicy for extracting bool from a Python object
  struct bool_rvalue_from_python
  {
      static unaryfunc* get_slot(PyObject*)
      {
          return &py_object_identity;
      }
      
      static bool extract(PyObject* intermediate)
      {
          return PyObject_IsTrue(intermediate);
      }
  };

  // A SlotPolicy for extracting floating types from Python objects.
  struct float_rvalue_from_python
  {
      static unaryfunc* get_slot(PyObject* obj)
      {
          PyNumberMethods* number_methods = obj->ob_type->tp_as_number;
          if (number_methods == 0)
              return 0;

          // For integer types, return the tp_int conversion slot to avoid
          // creating a new object. We'll handle that below
          if (PyInt_Check(obj))
              return &number_methods->nb_int;
      
          if (PyInstance_Check(obj) && !PyObject_HasAttrString(obj, "__float__"))
              return 0;
          
          return &number_methods->nb_float;
      }
      
      static double extract(PyObject* intermediate)
      {
          if (PyInt_Check(intermediate))
          {
              return PyInt_AS_LONG(intermediate);
          }
          else
          {
              return PyFloat_AS_DOUBLE(intermediate);
          }
      }
  };

  // A SlotPolicy for extracting C++ strings from Python objects.
  struct string_rvalue_from_python
  {
      // If the underlying object is "string-able" this will succeed
      static unaryfunc* get_slot(PyObject* obj)
      {
          if (PyInstance_Check(obj) && !PyObject_HasAttrString(obj, "__str__"))
              return 0;
          
          return &obj->ob_type->tp_str;
      };

      // Remember that this will be used to construct the result object 
      static char const* extract(PyObject* intermediate)
      {
          return PyString_AsString(intermediate);
      }
  };


  // identity_unaryfunc/non_null -- manufacture a unaryfunc "slot"
  // which just returns its argument. Used for bool conversions, since
  // all Python objects are directly convertible to bool
  extern "C" PyObject* to_complex_unaryfunc(PyObject* x)
  {
      return PyObject_CallMethod(x, "__complex__", const_cast<char*>("()"));
  }
  unaryfunc py_object_to_complex = to_complex_unaryfunc;

  struct complex_rvalue_from_python
  {
      static unaryfunc* get_slot(PyObject* obj)
      {

          if (PyComplex_Check(obj))
              return &py_object_identity;

          PyNumberMethods* number_methods = obj->ob_type->tp_as_number;
          
          // For integer types, return the tp_int conversion slot to avoid
          // creating a new object. We'll handle that below
          if (PyInt_Check(obj) && number_methods)
              return &number_methods->nb_int;
      
          if (PyFloat_Check(obj) && number_methods)
              return &number_methods->nb_float;
      
          if (!PyObject_HasAttrString((PyObject*)obj, "__complex__"))
              return 0;
          
          return &py_object_to_complex;
      }
      
      static std::complex<double> extract(PyObject* intermediate)
      {
          if (PyComplex_Check(intermediate))
          {
              return std::complex<double>(
                  PyComplex_RealAsDouble(intermediate)
                  , PyComplex_ImagAsDouble(intermediate));
          }
          else if (PyInt_Check(intermediate))
          {
              return PyInt_AS_LONG(intermediate);
          }
          else if (PyFloat_Check(intermediate))
          {
              return PyFloat_AS_DOUBLE(intermediate);
          }
          else
          {
              PyErr_SetString(PyExc_TypeError, "__complex__ method did not return a Complex object");
              throw error_already_set();
          }
      }
  };
} 

#define REGISTER_INT_CONVERTERS(U) slot_rvalue_from_python<U,int_rvalue_from_python>()
#define REGISTER_INT_CONVERTERS2(U) REGISTER_INT_CONVERTERS(signed U); REGISTER_INT_CONVERTERS(unsigned U)  

void initialize_builtin_converters()
{
    // booleans
    slot_rvalue_from_python<bool,bool_rvalue_from_python>();

    // integer types
    REGISTER_INT_CONVERTERS2(char);
    REGISTER_INT_CONVERTERS2(short);
    REGISTER_INT_CONVERTERS2(int);
    REGISTER_INT_CONVERTERS2(long);

    // floating types
    slot_rvalue_from_python<float,float_rvalue_from_python>();
    slot_rvalue_from_python<double,float_rvalue_from_python>();
    slot_rvalue_from_python<long double,float_rvalue_from_python>();
    
    slot_rvalue_from_python<std::complex<float>,complex_rvalue_from_python>();
    slot_rvalue_from_python<std::complex<double>,complex_rvalue_from_python>();
    slot_rvalue_from_python<std::complex<long double>,complex_rvalue_from_python>();
    
    // Add an lvalue converter for char which gets us char const*
    registry::insert(convert_to_cstring,undecorated_type_id<char>());

    // Register by-value converters to std::string
    slot_rvalue_from_python<std::string, string_rvalue_from_python>();
}

}}} // namespace boost::python::converter
