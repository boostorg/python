//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
// Revision History:
// 04 Mar 01  Rolled in const_cast from Dragon fork (Dave Abrahams)
// 03 Mar 01  added: pickle safety measures (Ralf W. Grosse-Kunstleve)
// 03 Mar 01  bug fix: use bound_function::create() (instead of new bound_function)

#define BOOST_PYTHON_SOURCE

#include <boost/python/classes.hpp>
#include <boost/python/detail/functions.hpp>
#include <boost/python/detail/singleton.hpp>
#include <cstddef>
#include <boost/python/callback.hpp>
#include <cstring>
#include <boost/python/module_builder.hpp>

namespace boost { namespace python {

namespace detail {
  void enable_named_method(boost::python::detail::class_base* type_obj, const char* name);
}

namespace {
  // Add the name of the module currently being loaded to the name_space with the
  // key "__module__". If no module is being loaded, or if name_space already has
  // a key "__module", has no effect. This is not really a useful public
  // interface; it's just used for class_t<>::class_t() below.
  void add_current_module_name(dictionary&);

  bool is_prefix(const char* s1, const char* s2);
  bool is_special_name(const char* name);
  void enable_special_methods(boost::python::detail::class_base* derived, const tuple& bases, const dictionary& name_space);

  void report_ignored_exception(PyObject* source)
  {
      // This bit of code copied wholesale from classobject.c in the Python source.
      PyObject *f, *t, *v, *tb;
      PyErr_Fetch(&t, &v, &tb);
      f = PySys_GetObject(const_cast<char*>("stderr"));
      if (f != NULL)
      {
          PyFile_WriteString(const_cast<char*>("Exception "), f);
          if (t) {
              PyFile_WriteObject(t, f, Py_PRINT_RAW);
              if (v && v != Py_None) {
                  PyFile_WriteString(const_cast<char*>(": "), f);
                  PyFile_WriteObject(v, f, 0);
              }
          }
          PyFile_WriteString(const_cast<char*>(" in "), f);
          PyFile_WriteObject(source, f, 0);
          PyFile_WriteString(const_cast<char*>(" ignored\n"), f);
          PyErr_Clear(); /* Just in case */
      }
      Py_XDECREF(t);
      Py_XDECREF(v);
      Py_XDECREF(tb);
  }

  //
  // pickle support courtesy of "Ralf W. Grosse-Kunstleve" <rwgk@cci.lbl.gov>
  //
  PyObject* class_reduce(PyObject* klass)
  {
      return PyObject_GetAttrString(klass, const_cast<char*>("__name__"));
  }

  ref global_class_reduce()
  {
      return ref(detail::new_wrapped_function(class_reduce));
  }
  

  tuple instance_reduce(PyObject* obj)
  {
      ref instance_class(PyObject_GetAttrString(obj, const_cast<char*>("__class__")));

      ref getinitargs(PyObject_GetAttrString(obj, const_cast<char*>("__getinitargs__")),
                      ref::null_ok);
      PyErr_Clear();
      ref initargs;
      if (getinitargs.get() != 0)
      {
          initargs = ref(PyEval_CallObject(getinitargs.get(), NULL));
          initargs = ref(PySequence_Tuple(initargs.get()));
      }
      else
      {
          initargs = ref(PyTuple_New(0));
      }

      ref getstate(PyObject_GetAttrString(obj, const_cast<char*>("__getstate__")),
                   ref::null_ok);
      PyErr_Clear();

      ref dict(PyObject_GetAttrString(obj, const_cast<char*>("__dict__")), ref::null_ok);
      PyErr_Clear();

      if (getstate.get() != 0)
      {
          if (dict.get() != 0 && dictionary(dict).size() > 0)
          {
              ref getstate_manages_dict(PyObject_GetAttrString(instance_class.get(), const_cast<char*>("__getstate_manages_dict__")), ref::null_ok);
              PyErr_Clear();
              if (getstate_manages_dict.get() == 0)
              {
                  PyErr_SetString(PyExc_RuntimeError, "Incomplete pickle support (__getstate_manages_dict__ not set)");
                  throw error_already_set();
              }
          }

          ref state = ref(PyEval_CallObject(getstate.get(), NULL));
          return tuple(instance_class, initargs, state);
      }

      if (getinitargs.get() == 0)
      {
          ref dict_defines_state(PyObject_GetAttrString(instance_class.get(), const_cast<char*>("__dict_defines_state__")), ref::null_ok);
          PyErr_Clear();
          if (dict_defines_state.get() == 0)
          {
              PyErr_SetString(PyExc_RuntimeError, "Incomplete pickle support (__dict_defines_state__ not set)");
              throw error_already_set();
          }
      }

      if (dict.get() != 0 && dictionary(dict).size() > 0)
      {
          return tuple(instance_class, initargs, dict);
      }

      return tuple(instance_class, initargs);
  }

  ref global_instance_reduce()
  {
      return ref(detail::new_wrapped_function(instance_reduce));
  }
}


namespace detail {

  class_base::class_base(PyTypeObject* meta_class_obj, string name, tuple bases, const dictionary& name_space)
      : type_object_base(meta_class_obj),
        m_name(name),
        m_bases(bases),
        m_name_space(name_space)
  {
      this->tp_name = const_cast<char*>(name.c_str());
      enable(type_object_base::getattr);
      enable(type_object_base::setattr);
      add_current_module_name(m_name_space);
      static const boost::python::string docstr("__doc__", boost::python::string::interned);
      if (PyDict_GetItem(m_name_space.get(), docstr.get())== 0)
      {
          PyDict_SetItem(m_name_space.get(), docstr.get(), Py_None);
      }
      enable_special_methods(this, bases, name_space);
  }

  void class_base::add_base(ref base)
  {
      tuple new_bases(m_bases.size() + 1);
      for (std::size_t i = 0; i < m_bases.size(); ++i)
          new_bases.set_item(i, m_bases[i]);
      new_bases.set_item(m_bases.size(), base);
      m_bases = new_bases;
  }

  PyObject* class_base::getattr(const char* name)
  {
      if (!BOOST_CSTD_::strcmp(name, "__dict__"))
      {
          PyObject* result = m_name_space.get();
          Py_INCREF(result);
          return result;
      }
      
      if (!BOOST_CSTD_::strcmp(name, "__bases__"))
      {
          PyObject* result = m_bases.get();
          Py_INCREF(result);
          return result;
      }
      
      if (!BOOST_CSTD_::strcmp(name, "__name__"))
      {
          PyObject* result = m_name.get();
          Py_INCREF(result);
          return result;
      }

      // pickle support courtesy of "Ralf W. Grosse-Kunstleve" <rwgk@cci.lbl.gov>
      if (!BOOST_CSTD_::strcmp(name, "__safe_for_unpickling__"))
      {
          return PyInt_FromLong(1);
      }
      if (!BOOST_CSTD_::strcmp(name, "__reduce__"))
      {
          PyObject* self = as_object(this);
          ref target(self, ref::increment_count);
          return bound_function::create(target, global_class_reduce());
      }
      
      ref local_attribute = m_name_space.get_item(string(name).reference());
    
      if (local_attribute.get())
          return local_attribute.release();

      // In case there are no bases...
      PyErr_SetString(PyExc_AttributeError, name);

      // Check bases
      for (std::size_t i = 0; i < m_bases.size(); ++i)
      {
          if (PyErr_ExceptionMatches(PyExc_AttributeError))
              PyErr_Clear(); // we're going to try a base class
          else if (PyErr_Occurred()) 
              break; // Other errors count, though!
        
          PyObject* base_attribute = PyObject_GetAttrString(m_bases[i].get(), const_cast<char*>(name));

          if (base_attribute != 0)
          {
              // Unwind the actual underlying function from unbound Python class
              // methods in case of multiple inheritance from real Python
              // classes. Python stubbornly insists that the first argument to a
              // method must be a true Python instance object otherwise. Do not
              // unwrap bound methods; that would interfere with intended semantics.
              if (PyMethod_Check(base_attribute)
                  && reinterpret_cast<PyMethodObject*>(base_attribute)->im_self == 0)
              {
                  PyObject* function
                      = reinterpret_cast<PyMethodObject*>(base_attribute)->im_func;
                  Py_INCREF(function);
                  Py_DECREF(base_attribute);
                  return function;
              }
              else
              {
                  return base_attribute;
              }
          }
      }
      return 0;
  }

  // Mostly copied wholesale from Python's classobject.c
  PyObject* class_base::repr() const
  {
      PyObject *mod = PyDict_GetItemString(
          m_name_space.get(), const_cast<char*>("__module__"));
      unsigned long address = reinterpret_cast<unsigned long>(this);
      string result = (mod == NULL || !PyString_Check(mod))
                ? string("<extension class %s at %lx>") % tuple(m_name, address)
                : string("<extension class %s.%s at %lx>") % tuple(ref(mod, ref::increment_count), m_name, address);
      return result.reference().release();
  }


  int class_base::setattr(const char* name, PyObject* value)
  {
      if (is_special_name(name)
          && BOOST_CSTD_::strcmp(name, "__doc__") != 0
          && BOOST_CSTD_::strcmp(name, "__name__") != 0)
      {
          boost::python::string message("Special attribute names other than '__doc__' and '__name__' are read-only, in particular: ");
          PyErr_SetObject(PyExc_TypeError, (message + name).get());
          throw error_already_set();
      }
      
      if (PyCallable_Check(value))
          detail::enable_named_method(this, name);
      
      return PyDict_SetItemString(
          m_name_space.reference().get(), const_cast<char*>(name), value);
  }

  bool class_base::initialize_instance(instance* obj, PyObject* args, PyObject* keywords)
  {
      // Getting the init function off the obj should result in a
      // bound method.
      PyObject* const init_function = obj->getattr("__init__", false);
        
      if (init_function == 0)
      {
          if (PyErr_Occurred() && PyErr_ExceptionMatches(PyExc_AttributeError)) {
              PyErr_Clear(); // no __init__? That's legal.
          }
          else {
              return false; // Something else? Keep the error
          }
      }
      else
      {
          // Manage the reference to the bound function
          ref init_function_holder(init_function);
        
        // Declare a ref to manage the result of calling __init__ (which should be None).
          ref init_result(
              PyEval_CallObjectWithKeywords(init_function, args, keywords));
      }
      return true;
  }

  void class_base::instance_dealloc(PyObject* obj) const
  {
      Py_INCREF(obj); // This allows a __del__ function to revive the obj
      
      PyObject* exc_type;
      PyObject* exc_value;
      PyObject* exc_traceback;
      PyErr_Fetch(&exc_type, &exc_value, &exc_traceback);

      // This scope ensures that the reference held by del_function doesn't release
      // the last reference and delete the object recursively (infinitely).
      {
          ref del_function;
          try {
              instance* const target = boost::python::downcast<boost::python::instance>(obj);
              del_function = ref(target->getattr("__del__", false), ref::null_ok);
          }
          catch(...) {
          }

          if (del_function.get() != 0)
          {
              ref result(PyEval_CallObject(del_function.get(), (PyObject *)NULL), ref::null_ok);
              
              if (result.get() == NULL)
                  report_ignored_exception(del_function.get());
          }
      }
      PyErr_Restore(exc_type, exc_value, exc_traceback);
      
      if (--obj->ob_refcnt <= 0)
          delete_instance(obj);
  }


}

instance::instance(PyTypeObject* class_)
    : boost::python::detail::base_object<PyObject>(class_)
{
}

instance::~instance()
{
}

PyObject* instance::getattr(const char* name, bool use_special_function)
{
    if (!BOOST_CSTD_::strcmp(name, "__dict__"))
    {
        if (PyEval_GetRestricted()) {
            PyErr_SetString(PyExc_RuntimeError,
                            "instance.__dict__ not accessible in restricted mode");
				return 0;
        }
        Py_INCREF(m_name_space.get());
        return m_name_space.get();
    }
    
    if (!BOOST_CSTD_::strcmp(name, "__class__"))
    {
        Py_INCREF(this->ob_type);
        return as_object(this->ob_type);
    }

    if (!BOOST_CSTD_::strcmp(name, "__reduce__"))
    {
      return detail::bound_function::create(ref(this, ref::increment_count), global_instance_reduce());
    }
    
    ref local_attribute = m_name_space.get_item(string(name).reference());
    
    if (local_attribute.get())
        return local_attribute.release();

    // Check its class. 
    PyObject* function =
        PyObject_GetAttrString(as_object(this->ob_type), const_cast<char*>(name));
    
    if (function == 0 && !use_special_function)
    {
        return 0;
    }

    ref class_attribute;
    if (function != 0)
    {
        // This will throw if the attribute wasn't found
        class_attribute = ref(function);
    }
    else
    {
        // Clear the error while we try special methods method (if any).
        PyErr_Clear();

        // First we try the special method that comes from concatenating
        // "__getattr__" and <name> and 2 trailing underscores. This is an
        // extension to regular Python class functionality.
        const string specific_getattr_name(detail::getattr_string() + name + "__");
        PyObject* getattr_method = PyObject_GetAttr(
            as_object(this->ob_type), specific_getattr_name.get());

        // Use just the first arg to PyEval_CallFunction if found
        char* arg_format = const_cast<char*>("(O)"); 

        // Try for the regular __getattr__ method if not found
        if (getattr_method == 0)
        {
             PyErr_Clear();
             getattr_method = PyObject_GetAttrString(
                as_object(this->ob_type), const_cast<char*>("__getattr__"));
            
            // Use both args to PyEval_CallFunction
            arg_format = const_cast<char*>("(Os)");
        }
        
        // If there is no such method, throw now.
        if (PyErr_Occurred())
        {
            PyErr_SetString(PyExc_AttributeError, name);
            return 0;
        }

        // Take ownership of the method
        ref owner(getattr_method);
        
        // Call it to get the attribute.
        return PyEval_CallFunction(getattr_method, arg_format, this, name);
    }

    if (!PyCallable_Check(class_attribute.get()))
    {
        PyErr_Clear();
        return class_attribute.release();
    }
    else
    {
        return detail::bound_function::create(ref(this, ref::increment_count), class_attribute);
    }
}

// instance::setattr_dict
//
//  Implements setattr() functionality for the "__dict__" attribute
//
int instance::setattr_dict(PyObject* value)
{
    if (PyEval_GetRestricted())
    {
        PyErr_SetString(PyExc_RuntimeError,
                        "__dict__ not accessible in restricted mode");
        return -1;
    }

    if (value == 0 || !PyDict_Check(value))
    {
        PyErr_SetString(PyExc_TypeError,
                        "__dict__ must be set to a dictionary");
        return -1;
    }
    m_name_space = dictionary(ref(value, ref::increment_count));
    return 0;
}

// instance::setattr -
//
//  Implements the setattr() and delattr() functionality for our own instance
//  objects, using the standard Python interface: if value == 0, we are deleting
//  the attribute, and returns 0 unless an error occurred.
int instance::setattr(const char* name, PyObject* value)
{
    if (BOOST_CSTD_::strcmp(name, "__class__") == 0)
    {
        PyErr_SetString(PyExc_TypeError, "__class__ attribute is read-only");
        throw error_already_set();
    }
    
    if (BOOST_CSTD_::strcmp(name, "__dict__") == 0)
        return setattr_dict(value);
    
    // Try to find an appropriate "specific" setter or getter method, either
    // __setattr__<name>__(value) or __delattr__<name>__(). This is an extension
    // to regular Python class functionality.
    const string& base_name = value ? detail::setattr_string() : detail::delattr_string();
    const string specific_method_name(base_name + name + "__");
    
    ref special_method(
        PyObject_GetAttr(as_object(this->ob_type), specific_method_name.get()),
        ref::null_ok);

    PyObject* result_object = 0;
    if (special_method.get() != 0)
    {
        // The specific function was found; call it now. Note that if value is
        // not included in the format string, it is ignored.
        char* format_string = const_cast<char*>(value ? "(OO)" : "(O)");
        result_object = PyEval_CallFunction(special_method.get(), format_string, this, value);
    }
    else
    {
        // If not found, try the usual __setattr__(name, value) or
        // __delattr__(name) functions.
        PyErr_Clear();
        special_method.reset(
            PyObject_GetAttr(as_object(this->ob_type), base_name.get()),
            ref::null_ok);
        
        if (special_method.get() != 0)
        {
            // The special function was found; call it now. Note that if value
            // is not included in the format string, it is ignored.
            char* format_string = const_cast<char*>(value ? "(OsO)" : "(Os)");
            result_object = PyEval_CallFunction(
                special_method.get(), format_string, this, name, value);
        }
    }

    // If we found an appropriate special method, handle the return value.
    if (special_method.get() != 0)
    {
        ref manage_result(result_object);
        return 0;
    }
    
    PyErr_Clear(); // Nothing was found; clear the python error state
    
    if (value == 0) // Try to remove the attribute from our name space
    {
        const int result = PyDict_DelItemString(m_name_space.reference().get(),
                                                const_cast<char*>(name));
        if (result < 0)
        {
            PyErr_Clear();
            PyErr_SetString(PyExc_AttributeError, "delete non-existing instance attribute");
        }
        return result;
    }
    else // Change the specified item in our name space
    {
        return PyDict_SetItemString(m_name_space.reference().get(),
                                    const_cast<char*>(name), value);
    }
}

PyObject* instance::call(PyObject* args, PyObject* keywords)
{
    return PyEval_CallObjectWithKeywords(
        ref(getattr("__call__")).get(), // take possession of the result from getattr()
        args, keywords);
}

PyObject* instance::repr()
{
    return callback<PyObject*>::call_method(this, "__repr__");
}

int instance::compare(PyObject* other)
{
    return callback<int>::call_method(this, "__cmp__", other);
}

PyObject* instance::str()
{
    return callback<PyObject*>::call_method(this, "__str__");
}

long instance::hash()
{
    return callback<long>::call_method(this, "__hash__");
}

int instance::length()
{
    return callback<int>::call_method(this, "__len__");
}

PyObject* instance::get_subscript(PyObject* key)
{
    return callback<PyObject*>::call_method(this, "__getitem__", key);
}

void instance::set_subscript(PyObject* key, PyObject* value)
{
    if (value == 0)
        callback<void>::call_method(this, "__delitem__", key);
    else
        callback<void>::call_method(this, "__setitem__", key, value);
}

PyObject* instance::get_slice(int start, int finish)
{
    return callback<PyObject*>::call_method(this, "__getslice__", start, finish);
}

void instance::set_slice(int start, int finish, PyObject* value)
{
    if (value == 0)
        callback<void>::call_method(this, "__delslice__", start, finish);
    else
        callback<void>::call_method(this, "__setslice__", start, finish, value);
}

PyObject* instance::add(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__add__", other);
}

PyObject* instance::subtract(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__sub__", other);
}

PyObject* instance::multiply(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__mul__", other);
}

PyObject* instance::divide(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__div__", other);
}

PyObject* instance::remainder(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__mod__", other);
}

PyObject* instance::divmod(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__divmod__", other);
}

PyObject* instance::power(PyObject* exponent, PyObject* modulus)
{
    if (as_object(modulus->ob_type) == Py_None)
        return callback<PyObject*>::call_method(this, "__pow__", exponent);
    else
        return callback<PyObject*>::call_method(this, "__pow__", exponent, modulus);
}

PyObject* instance::negative()
{
    return callback<PyObject*>::call_method(this, "__neg__");
}

PyObject* instance::positive()
{
    return callback<PyObject*>::call_method(this, "__pos__");
}

PyObject* instance::absolute()
{
    return callback<PyObject*>::call_method(this, "__abs__");
}

int instance::nonzero()
{
    return callback<bool>::call_method(this, "__nonzero__");
}

PyObject* instance::invert()
{
    return callback<PyObject*>::call_method(this, "__invert__");
}

PyObject* instance::lshift(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__lshift__", other);
}

PyObject* instance::rshift(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__rshift__", other);
}

PyObject* instance::do_and(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__and__", other);
}

PyObject* instance::do_xor(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__xor__", other);
}

PyObject* instance::do_or(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__or__", other);
}

int instance::coerce(PyObject** x, PyObject** y)
{
    assert(this == *x);
    
    // Coerce must return a tuple
    tuple result(callback<tuple>::call_method(this, "__coerce__", *y));
    
    *x = result[0].release();
    *y = result[1].release();
    return 0;
}

PyObject* instance::as_int()
{
    return callback<PyObject*>::call_method(this, "__int__");
}

PyObject* instance::as_long()
{
    return callback<PyObject*>::call_method(this, "__long__");
}

PyObject* instance::as_float()
{
    return callback<PyObject*>::call_method(this, "__float__");
}

PyObject* instance::oct()
{
    return callback<PyObject*>::call_method(this, "__oct__");
}

PyObject* instance::hex()
{
    return callback<PyObject*>::call_method(this, "__hex__");
}

PyObject* instance::lt(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__lt__", other);
}

PyObject* instance::le(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__le__", other);
}

PyObject* instance::eq(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__eq__", other);
}

PyObject* instance::ne(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__ne__", other);
}

PyObject* instance::gt(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__gt__", other);
}

PyObject* instance::ge(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__ge__", other);
}

PyObject* instance::inplace_add(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__iadd__", other);
}

PyObject* instance::inplace_subtract(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__isub__", other);
}

PyObject* instance::inplace_multiply(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__imul__", other);
}

PyObject* instance::inplace_divide(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__idiv__", other);
}

PyObject* instance::inplace_remainder(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__imod__", other);
}

PyObject* instance::inplace_power(PyObject* exponent, PyObject* modulus)
{
    if (modulus == Py_None)
        return callback<PyObject*>::call_method(this, "__ipow__", exponent);
    else
        return callback<PyObject*>::call_method(this, "__ipow__", exponent, modulus);
}

PyObject* instance::inplace_lshift(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__ilshift__", other);
}

PyObject* instance::inplace_rshift(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__irshift__", other);
}

PyObject* instance::inplace_and(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__iand__", other);
}

PyObject* instance::inplace_or(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__ior__", other);
}

PyObject* instance::inplace_xor(PyObject* other)
{
    return callback<PyObject*>::call_method(this, "__ixor__", other);
}

namespace {
  struct named_capability
  {
      const char* name;
      detail::type_object_base::capability capability;
  };

  const named_capability enablers[] =
  {
      { "__hash__", detail::type_object_base::hash },
      { "__cmp__", detail::type_object_base::compare },
      { "__gt__", detail::type_object_base::richcompare },
      { "__ge__", detail::type_object_base::richcompare },
      { "__lt__", detail::type_object_base::richcompare },
      { "__le__", detail::type_object_base::richcompare },
      { "__eq__", detail::type_object_base::richcompare },
      { "__ne__", detail::type_object_base::richcompare },
      { "__iadd__", detail::type_object_base::number_inplace_add },
      { "__isub__", detail::type_object_base::number_inplace_subtract },
      { "__imul__", detail::type_object_base::number_inplace_multiply },
      { "__idiv__", detail::type_object_base::number_inplace_divide },
      { "__imod__", detail::type_object_base::number_inplace_remainder },
      { "__ipow__", detail::type_object_base::number_inplace_power },
      { "__ilshift__", detail::type_object_base::number_inplace_lshift },
      { "__irshift__", detail::type_object_base::number_inplace_rshift },
      { "__iand__", detail::type_object_base::number_inplace_and },
      { "__ixor__", detail::type_object_base::number_inplace_xor },
      { "__ior__", detail::type_object_base::number_inplace_or },
      { "__repr__", detail::type_object_base::repr },
      { "__str__", detail::type_object_base::str },
      { "__call__", detail::type_object_base::call },
      { "__getattr__", detail::type_object_base::getattr },
      { "__setattr__", detail::type_object_base::setattr },
      { "__len__", detail::type_object_base::mapping_length },
      { "__len__", detail::type_object_base::sequence_length },
      { "__getitem__", detail::type_object_base::mapping_subscript },
      { "__getitem__", detail::type_object_base::sequence_item },
      { "__setitem__", detail::type_object_base::mapping_ass_subscript },
      { "__setitem__", detail::type_object_base::sequence_ass_item },
      { "__delitem__", detail::type_object_base::mapping_ass_subscript },
      { "__delitem__", detail::type_object_base::sequence_ass_item },
      { "__getslice__", detail::type_object_base::sequence_slice },
      { "__setslice__", detail::type_object_base::sequence_ass_slice },
      { "__delslice__", detail::type_object_base::sequence_ass_slice },
      { "__add__", detail::type_object_base::number_add },
      { "__sub__", detail::type_object_base::number_subtract },
      { "__mul__", detail::type_object_base::number_multiply },
      { "__div__", detail::type_object_base::number_divide },
      { "__mod__", detail::type_object_base::number_remainder },
      { "__divmod__", detail::type_object_base::number_divmod },
      { "__pow__", detail::type_object_base::number_power },
      { "__neg__", detail::type_object_base::number_negative },
      { "__pos__", detail::type_object_base::number_positive },
      { "__abs__", detail::type_object_base::number_absolute },
      { "__nonzero__", detail::type_object_base::number_nonzero },
      { "__invert__", detail::type_object_base::number_invert },
      { "__lshift__", detail::type_object_base::number_lshift },
      { "__rshift__", detail::type_object_base::number_rshift },
      { "__and__", detail::type_object_base::number_and },
      { "__xor__", detail::type_object_base::number_xor },
      { "__or__", detail::type_object_base::number_or },
      { "__coerce__", detail::type_object_base::number_coerce },
      { "__int__", detail::type_object_base::number_int },
      { "__long__", detail::type_object_base::number_long },
      { "__float__", detail::type_object_base::number_float },
      { "__oct__", detail::type_object_base::number_oct },
      { "__hex__", detail::type_object_base::number_hex }
  };

  bool is_prefix(const char* s1, const char* s2)
  {
      while (*s1 != 0 && *s2 != 0 && *s1 == *s2)
          ++s1, ++s2;
      return *s1 == 0;
  }

  bool is_special_name(const char* name)
  {
    if (name[0] != '_' || name[1] != '_' || name[2] == 0 || name[3] == 0)
        return false;

    std::size_t name_length = BOOST_CSTD_::strlen(name);
    return name[name_length - 1] == '_' && name[name_length - 2] == '_';
  }
}

namespace detail {
  // Enable the special handler for methods of the given name, if any.
  void enable_named_method(boost::python::detail::class_base* type_obj, const char* name)
  {
      const std::size_t num_enablers = PY_ARRAY_LENGTH(enablers);

      // Make sure this ends with "__" since we'll only compare the head of the
      // string.  This is done to make the __getattr__<name>__/__setattr__<name>__
      // extension work.
      if (!is_special_name(name))
          return;

      for (std::size_t i = 0; i < num_enablers; ++i)
      {
          if (is_prefix(enablers[i].name + 2, name + 2))
          {
              type_obj->enable(enablers[i].capability);
          }
      }
  }
}

namespace {
  // Enable any special methods which are enabled in the base class.
  void enable_special_methods(boost::python::detail::class_base* derived, const tuple& bases, const dictionary& name_space)
  {
      for (std::size_t i = 0; i < bases.size(); ++i)
      {
          PyObject* base = bases[i].get();

          for (std::size_t n = 0; n < PY_ARRAY_LENGTH(enablers); ++n)
          {
              ref attribute(
                  PyObject_GetAttrString(base, const_cast<char*>(enablers[n].name)),
                  ref::null_ok);
              PyErr_Clear();
              if (attribute.get() != 0 && PyCallable_Check(attribute.get()))
                  detail::add_capability(enablers[n].capability, derived);
          }
      }

      list keys(name_space.keys());
      for (std::size_t j = 0, len = keys.size(); j < len; ++j)
      {
          string name_obj(keys.get_item(j));
          const char* name = name_obj.c_str();

          if (!is_special_name(name))
              continue;

          for (std::size_t i = 0; i < PY_ARRAY_LENGTH(enablers); ++i)
          {
              if (is_prefix(enablers[i].name + 2, name + 2))
              {
                  detail::add_capability(enablers[i].capability, derived);
              }
          }
      }
  }

  void add_current_module_name(dictionary& name_space)
  {
      static string module_key("__module__", string::interned);

      // If the user didn't specify a __module__ attribute already
      if (name_space.get_item(module_key).get() == 0)
      {
          if (module_builder::initializing())
          {
              // The global __name__ is not properly set in this case
              name_space.set_item(module_key, module_builder::name());
          }
          else
          {
              // Get the module name from the global __name__
              PyObject *globals = PyEval_GetGlobals();
              if (globals != NULL)
              {
                  PyObject *module_name = PyDict_GetItemString(globals, const_cast<char*>("__name__"));
                  if (module_name != NULL)
                      name_space.set_item(module_key, module_name);
              }
          }
      }
  }
}

void adjust_slice_indices(PyObject* obj, int& start, int& finish)
{
    int length = callback<int>::call_method(obj, "__len__");
    
    // This is standard Python class behavior.
    if (start < 0)
        start += length;
    if (finish < 0)
        finish += length;
    
    // This is not
    if (start < 0)
        start = 0;
    if (finish < 0)
        finish = 0;
}

namespace detail {
const string& setattr_string()
{
    static string x("__setattr__", string::interned);
    return x;
}

const string& getattr_string()
{
    static string x("__getattr__", string::interned);
    return x;
}

const string& delattr_string()
{
    static string x("__delattr__", string::interned);
    return x;
}
}

}} // namespace boost::python
