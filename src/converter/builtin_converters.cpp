// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/detail/config.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <boost/python/converter/rvalue_from_python_data.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/type_id.hpp>
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
              , type_id<T>()
              );
      }
      
   private:
      static void* convertible(PyObject* obj)
      {
          unaryfunc* slot = SlotPolicy::get_slot(obj);
          return slot && *slot ? slot : 0;
      }

      static void construct(PyObject* obj, rvalue_from_python_stage1_data* data)
      {
          // Get the (intermediate) source object
          unaryfunc creator = *static_cast<unaryfunc*>(data->convertible);
          handle<> intermediate(creator(obj));

          // Get the location in which to construct
          void* storage = ((rvalue_from_python_storage<T>*)data)->storage.bytes;
          new (storage) T(SlotPolicy::extract(intermediate.get()));

          // record successful construction
          data->convertible = storage;
      }
  };

  // A SlotPolicy for extracting integer types from Python objects
  struct int_rvalue_from_python_base
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
  };

  template <class T>
  struct int_rvalue_from_python : int_rvalue_from_python_base
  {
      static T extract(PyObject* intermediate)
      {
          return PyFloat_Check(intermediate)
              ? numeric_cast<T>(PyFloat_AS_DOUBLE(intermediate))
              : numeric_cast<T>(PyInt_AS_LONG(intermediate))
              ;
      }
  };

// using Python's macro instead of Boost's - we don't seem to get the
// config right all the time.
#ifdef HAVE_LONG_LONG
  // A SlotPolicy for extracting long long types from Python objects
  struct long_long_rvalue_from_python_base
  {
      static unaryfunc* get_slot(PyObject* obj)
      {
          PyNumberMethods* number_methods = obj->ob_type->tp_as_number;
          if (number_methods == 0)
              return 0;

          // For floating and integer types, return the identity
          // conversion slot to avoid creating a new object. We'll
          // handle that in the extract function
          if (PyInt_Check(obj))
              return &number_methods->nb_int;

          if (PyFloat_Check(obj))
              return &number_methods->nb_float;

          if (PyInstance_Check(obj) && !PyObject_HasAttrString(obj, "__long__"))
              return 0;
          
          return &number_methods->nb_long;
      }
  };

  struct long_long_rvalue_from_python : long_long_rvalue_from_python_base
  {
      static LONG_LONG extract(PyObject* intermediate)
      {
          if (PyInt_Check(intermediate))
          {
              return PyInt_AS_LONG(intermediate);
          }
          if (PyFloat_Check(intermediate))
          {
              return numeric_cast<LONG_LONG>(PyFloat_AS_DOUBLE(intermediate));
          }
          else
          {
              LONG_LONG result = PyLong_AsLongLong(intermediate);
              
              if (PyErr_Occurred())
                  throw_error_already_set();

              return result;
          }
      }
  };

  struct unsigned_long_long_rvalue_from_python : long_long_rvalue_from_python_base
  {
      static unsigned LONG_LONG extract(PyObject* intermediate)
      {
          if (PyInt_Check(intermediate))
          {
              return numeric_cast<unsigned LONG_LONG>(PyInt_AS_LONG(intermediate));
          }
          if (PyFloat_Check(intermediate))
          {
              return numeric_cast<unsigned LONG_LONG>(PyFloat_AS_DOUBLE(intermediate));
          }
          else
          {
              unsigned LONG_LONG result = PyLong_AsUnsignedLongLong(intermediate);
              
              if (PyErr_Occurred())
                  throw_error_already_set();

              return result;
          }
      }
  };
#endif 


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


  // to_complex_unaryfunc/py_object_to_complex -- manufacture a
  // unaryfunc "slot" which calls its argument's __complex__
  // method. We have this because there's no type object nb_complex
  // slot.
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
          else if (!PyFloat_Check(intermediate)) 
          {
              PyErr_SetString(PyExc_TypeError, "__complex__ method did not return a Complex object");
              throw_error_already_set();
          }
          
          return PyFloat_AS_DOUBLE(intermediate);
      }
  };
} 

BOOST_PYTHON_DECL PyObject* do_return_to_python(char x)
{
    return PyString_FromStringAndSize(&x, 1);
}
  
BOOST_PYTHON_DECL PyObject* do_return_to_python(char const* x)
{
    return x ? PyString_FromString(x) : boost::python::detail::none();
}
  
BOOST_PYTHON_DECL PyObject* do_return_to_python(PyObject* x)
{
    return x ? x : boost::python::detail::none();
}
  
BOOST_PYTHON_DECL PyObject* do_arg_to_python(PyObject* x)
{
    if (x == 0)
        return boost::python::detail::none();
      
    Py_INCREF(x);
    return x;
}

#define REGISTER_INT_CONVERTERS(U) slot_rvalue_from_python<U,int_rvalue_from_python<U> >()
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
    
// using Python's macro instead of Boost's - we don't seem to get the
// config right all the time.
# ifdef HAVE_LONG_LONG
    slot_rvalue_from_python<signed LONG_LONG,long_long_rvalue_from_python>();
    slot_rvalue_from_python<unsigned LONG_LONG,unsigned_long_long_rvalue_from_python>();
# endif
        
    // floating types
    slot_rvalue_from_python<float,float_rvalue_from_python>();
    slot_rvalue_from_python<double,float_rvalue_from_python>();
    slot_rvalue_from_python<long double,float_rvalue_from_python>();
    
    slot_rvalue_from_python<std::complex<float>,complex_rvalue_from_python>();
    slot_rvalue_from_python<std::complex<double>,complex_rvalue_from_python>();
    slot_rvalue_from_python<std::complex<long double>,complex_rvalue_from_python>();
    
    // Add an lvalue converter for char which gets us char const*
    registry::insert(convert_to_cstring,type_id<char>());

    // Register by-value converters to std::string
    slot_rvalue_from_python<std::string, string_rvalue_from_python>();
}

}}} // namespace boost::python::converter
