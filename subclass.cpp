//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "subclass.h"
#include "functions.h"
#include "singleton.h"
#include <cstddef>
#include "callback.h"
#include <cstring>

namespace py {

namespace detail {
  void enable_named_method(py::detail::ClassBase* type_object, const char* name);
}

namespace {
  // Add the name of the module currently being loaded to the name_space with the
  // key "__module__". If no module is being loaded, or if name_space already has
  // a key "__module", has no effect. This is not really a useful public
  // interface; it's just used for Class<>::Class() below.
  void add_current_module_name(Dict&);

  bool is_prefix(const char* s1, const char* s2);
  bool is_special_name(const char* name);
  void enable_special_methods(py::detail::ClassBase* derived, const Tuple& bases, const Dict& name_space);

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
}


namespace detail {

  ClassBase::ClassBase(PyTypeObject* meta_class, String name, Tuple bases, const Dict& name_space)
      : py::TypeObjectBase(meta_class),
        m_name(name),
        m_bases(bases),
        m_name_space(name_space)
  {
      this->tp_name = const_cast<char*>(name.c_str());
      enable(TypeObjectBase::getattr);
      enable(TypeObjectBase::setattr);
      add_current_module_name(m_name_space);
      static const py::String docstr("__doc__", py::String::interned);
      if (PyDict_GetItem(m_name_space.get(), docstr.get())== 0)
      {
          PyDict_SetItem(m_name_space.get(), docstr.get(), Py_None);
      }
      enable_special_methods(this, bases, name_space);
  }

  void ClassBase::add_base(Ptr base)
  {
      Tuple new_bases(m_bases.size() + 1);
      for (std::size_t i = 0; i < m_bases.size(); ++i)
          new_bases.set_item(i, m_bases[i]);
      new_bases.set_item(m_bases.size(), base);
      m_bases = new_bases;
  }

  PyObject* ClassBase::getattr(const char* name) const
  {
      if (!PY_CSTD_::strcmp(name, "__dict__"))
      {
          PyObject* result = m_name_space.get();
          Py_INCREF(result);
          return result;
      }
      
      if (!PY_CSTD_::strcmp(name, "__bases__"))
      {
          PyObject* result = m_bases.get();
          Py_INCREF(result);
          return result;
      }
      
      if (!PY_CSTD_::strcmp(name, "__name__"))
      {
          PyObject* result = m_name.get();
          Py_INCREF(result);
          return result;
      }
      
      Ptr local_attribute = m_name_space.get_item(String(name).reference());
    
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
              // method must be a true Python Instance object otherwise. Do not
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
  PyObject* ClassBase::repr() const
  {
      PyObject *mod = PyDict_GetItemString(
          m_name_space.get(), const_cast<char*>("__module__"));
      unsigned long address = reinterpret_cast<unsigned long>(this);
      String result = (mod == NULL || !PyString_Check(mod))
                ? String("<extension class %s at %lx>") % Tuple(m_name, address)
                : String("<extension class %s.%s at %lx>") % Tuple(Ptr(mod, Ptr::borrowed), m_name, address);
      return result.reference().release();
  }


  int ClassBase::setattr(const char* name, PyObject* value)
  {
      if (is_special_name(name)
          && PY_CSTD_::strcmp(name, "__doc__") != 0
          && PY_CSTD_::strcmp(name, "__name__") != 0)
      {
          py::String message("Special attribute names other than '__doc__' and '__name__' are read-only, in particular: ");
          PyErr_SetObject(PyExc_TypeError, (message + name).get());
          throw ErrorAlreadySet();
      }
      
      if (PyCallable_Check(value))
          detail::enable_named_method(this, name);
      
      return PyDict_SetItemString(
          m_name_space.reference().get(), const_cast<char*>(name), value);
  }

  bool ClassBase::initialize_instance(Instance* instance, PyObject* args, PyObject* keywords)
  {
      // Getting the init function off the instance should result in a
      // bound method.
      PyObject* const init_function = instance->getattr("__init__", false);
        
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
          Ptr init_function_holder(init_function);
        
        // Declare a Ptr to manage the result of calling __init__ (which should be None).
          Ptr init_result(
              PyEval_CallObjectWithKeywords(init_function, args, keywords));
      }
      return true;
  }

  void ClassBase::instance_dealloc(PyObject* instance) const
  {
      Py_INCREF(instance); // This allows a __del__ function to revive the instance
      
      PyObject* exc_type;
      PyObject* exc_value;
      PyObject* exc_traceback;
      PyErr_Fetch(&exc_type, &exc_value, &exc_traceback);

      // This scope ensures that the reference held by del_function doesn't release
      // the last reference and delete the object recursively (infinitely).
      {
          Ptr del_function;
          try {
              Instance* const target = py::Downcast<py::Instance>(instance);
              del_function = Ptr(target->getattr("__del__", false), Ptr::null_ok);
          }
          catch(...) {
          }

          if (del_function.get() != 0)
          {
              Ptr result(PyEval_CallObject(del_function.get(), (PyObject *)NULL), Ptr::null_ok);
              
              if (result.get() == NULL)
                  report_ignored_exception(del_function.get());
          }
      }
      PyErr_Restore(exc_type, exc_value, exc_traceback);
      
      if (--instance->ob_refcnt <= 0)
          delete_instance(instance);
  }


}

Instance::Instance(PyTypeObject* class_)
    : PythonObject(class_)
{
}

Instance::~Instance()
{
}

PyObject* Instance::getattr(const char* name, bool use_special_function)
{
    if (!PY_CSTD_::strcmp(name, "__dict__"))
    {
        if (PyEval_GetRestricted()) {
            PyErr_SetString(PyExc_RuntimeError,
                            "instance.__dict__ not accessible in restricted mode");
				return 0;
        }
        Py_INCREF(m_name_space.get());
        return m_name_space.get();
    }
    
    if (!PY_CSTD_::strcmp(name, "__class__"))
    {
        Py_INCREF(this->ob_type);
        return as_object(this->ob_type);
    }
    
    Ptr local_attribute = m_name_space.get_item(String(name).reference());
    
    if (local_attribute.get())
        return local_attribute.release();

    // Check its class. 
    PyObject* function =
        PyObject_GetAttrString(as_object(this->ob_type), const_cast<char*>(name));
    
    if (function == 0 && !use_special_function)
    {
        return 0;
    }

    Ptr class_attribute;
    if (function != 0)
    {
        // This will throw if the attribute wasn't found
        class_attribute = Ptr(function);
    }
    else
    {
        // Clear the error while we try special methods method (if any).
        PyErr_Clear();

        // First we try the special method that comes from concatenating
        // "__getattr__" and <name> and 2 trailing underscores. This is an
        // extension to regular Python class functionality.
        const String specific_getattr_name(detail::getattr_string() + name + "__");
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
        Ptr owner(getattr_method);
        
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
        return new BoundFunction(Ptr(this, Ptr::borrowed), class_attribute);
    }
}

// Instance::setattr_dict
//
//  Implements setattr() functionality for the "__dict__" attribute
//
int Instance::setattr_dict(PyObject* value)
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
    m_name_space = Dict(Ptr(value, Ptr::borrowed));
    return 0;
}

// Instance::setattr -
//
//  Implements the setattr() and delattr() functionality for our own Instance
//  objects, using the standard Python interface: if value == 0, we are deleting
//  the attribute, and returns 0 unless an error occurred.
int Instance::setattr(const char* name, PyObject* value)
{
    if (PY_CSTD_::strcmp(name, "__class__") == 0)
    {
        PyErr_SetString(PyExc_TypeError, "__class__ attribute is read-only");
        throw ErrorAlreadySet();
    }
    
    if (PY_CSTD_::strcmp(name, "__dict__") == 0)
        return setattr_dict(value);
    
    // Try to find an appropriate "specific" setter or getter method, either
    // __setattr__<name>__(value) or __delattr__<name>__(). This is an extension
    // to regular Python class functionality.
    const String& base_name = value ? detail::setattr_string() : detail::delattr_string();
    const String specific_method_name(base_name + name + "__");
    
    Ptr special_method(
        PyObject_GetAttr(as_object(this->ob_type), specific_method_name.get()),
        Ptr::null_ok);

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
            Ptr::null_ok);
        
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
        expect_and_absorb_non_null(result_object);
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

PyObject* Instance::call(PyObject* args, PyObject* keywords)
{
    return PyEval_CallObjectWithKeywords(
        Ptr(getattr("__call__")).get(), // take possession of the result from getattr()
        args, keywords);
}

PyObject* Instance::repr()
{
    return Callback<PyObject*>::call_method(this, "__repr__");
}

int Instance::compare(PyObject* other)
{
    return Callback<int>::call_method(this, "__cmp__", other);
}

PyObject* Instance::str()
{
    return Callback<PyObject*>::call_method(this, "__str__");
}

long Instance::hash()
{
    return Callback<long>::call_method(this, "__hash__");
}

int Instance::length()
{
    return Callback<int>::call_method(this, "__len__");
}

PyObject* Instance::get_subscript(PyObject* key)
{
    return Callback<PyObject*>::call_method(this, "__getitem__", key);
}

void Instance::set_subscript(PyObject* key, PyObject* value)
{
    if (value == 0)
        Callback<void>::call_method(this, "__delitem__", key);
    else
        Callback<void>::call_method(this, "__setitem__", key, value);
}

PyObject* Instance::get_slice(int start, int finish)
{
    return Callback<PyObject*>::call_method(this, "__getslice__", start, finish);
}

void Instance::set_slice(int start, int finish, PyObject* value)
{
    if (value == 0)
        Callback<void>::call_method(this, "__delslice__", start, finish);
    else
        Callback<void>::call_method(this, "__setslice__", start, finish, value);
}

PyObject* Instance::add(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__add__", other);
}

PyObject* Instance::subtract(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__sub__", other);
}

PyObject* Instance::multiply(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__mul__", other);
}

PyObject* Instance::divide(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__div__", other);
}

PyObject* Instance::remainder(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__mod__", other);
}

PyObject* Instance::divmod(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__divmod__", other);
}

PyObject* Instance::power(PyObject* exponent, PyObject* modulus)
{
    if (as_object(modulus->ob_type) == Py_None)
        return Callback<PyObject*>::call_method(this, "__pow__", exponent);
    else
        return Callback<PyObject*>::call_method(this, "__pow__", exponent, modulus);
}

PyObject* Instance::negative()
{
    return Callback<PyObject*>::call_method(this, "__neg__");
}

PyObject* Instance::positive()
{
    return Callback<PyObject*>::call_method(this, "__pos__");
}

PyObject* Instance::absolute()
{
    return Callback<PyObject*>::call_method(this, "__abs__");
}

int Instance::nonzero()
{
    return Callback<bool>::call_method(this, "__nonzero__");
}

PyObject* Instance::invert()
{
    return Callback<PyObject*>::call_method(this, "__invert__");
}

PyObject* Instance::lshift(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__lshift__", other);
}

PyObject* Instance::rshift(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__rshift__", other);
}

PyObject* Instance::do_and(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__and__", other);
}

PyObject* Instance::do_xor(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__xor__", other);
}

PyObject* Instance::do_or(PyObject* other)
{
    return Callback<PyObject*>::call_method(this, "__or__", other);
}

int Instance::coerce(PyObject** x, PyObject** y)
{
    assert(this == *x);
    
    // Coerce must return a tuple
    Tuple result(Callback<Tuple>::call_method(this, "__coerce__", *y));
    
    *x = result[0].release();
    *y = result[1].release();
    return 0;
}

PyObject* Instance::as_int()
{
    return Callback<PyObject*>::call_method(this, "__int__");
}

PyObject* Instance::as_long()
{
    return Callback<PyObject*>::call_method(this, "__long__");
}

PyObject* Instance::as_float()
{
    return Callback<PyObject*>::call_method(this, "__float__");
}

PyObject* Instance::oct()
{
    return Callback<PyObject*>::call_method(this, "__oct__");
}

PyObject* Instance::hex()
{
    return Callback<PyObject*>::call_method(this, "__hex__");
}

namespace {
  struct NamedCapability
  {
      const char* name;
      TypeObjectBase::Capability capability;
  };

  const NamedCapability enablers[] =
  {
      { "__hash__", TypeObjectBase::hash },
      { "__cmp__", TypeObjectBase::compare },
      { "__repr__", TypeObjectBase::repr },
      { "__str__", TypeObjectBase::str },
      { "__call__", TypeObjectBase::call },
      { "__getattr__", TypeObjectBase::getattr },
      { "__setattr__", TypeObjectBase::setattr },
      { "__len__", TypeObjectBase::mapping_length },
      { "__len__", TypeObjectBase::sequence_length },
      { "__getitem__", TypeObjectBase::mapping_subscript },
      { "__getitem__", TypeObjectBase::sequence_item },
      { "__setitem__", TypeObjectBase::mapping_ass_subscript },
      { "__setitem__", TypeObjectBase::sequence_ass_item },
      { "__delitem__", TypeObjectBase::mapping_ass_subscript },
      { "__delitem__", TypeObjectBase::sequence_ass_item },
      { "__getslice__", TypeObjectBase::sequence_slice },
      { "__setslice__", TypeObjectBase::sequence_ass_slice },
      { "__delslice__", TypeObjectBase::sequence_ass_slice },
      { "__add__", TypeObjectBase::number_add },
      { "__sub__", TypeObjectBase::number_subtract },
      { "__mul__", TypeObjectBase::number_multiply },
      { "__div__", TypeObjectBase::number_divide },
      { "__mod__", TypeObjectBase::number_remainder },
      { "__divmod__", TypeObjectBase::number_divmod },
      { "__pow__", TypeObjectBase::number_power },
      { "__neg__", TypeObjectBase::number_negative },
      { "__pos__", TypeObjectBase::number_positive },
      { "__abs__", TypeObjectBase::number_absolute },
      { "__nonzero__", TypeObjectBase::number_nonzero },
      { "__invert__", TypeObjectBase::number_invert },
      { "__lshift__", TypeObjectBase::number_lshift },
      { "__rshift__", TypeObjectBase::number_rshift },
      { "__and__", TypeObjectBase::number_and },
      { "__xor__", TypeObjectBase::number_xor },
      { "__or__", TypeObjectBase::number_or },
      { "__coerce__", TypeObjectBase::number_coerce },
      { "__int__", TypeObjectBase::number_int },
      { "__long__", TypeObjectBase::number_long },
      { "__float__", TypeObjectBase::number_float },
      { "__oct__", TypeObjectBase::number_oct },
      { "__hex__", TypeObjectBase::number_hex }
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

    std::size_t name_length = PY_CSTD_::strlen(name);
    return name[name_length - 1] == '_' && name[name_length - 2] == '_';
  }
}

namespace detail {
  // Enable the special handler for methods of the given name, if any.
  void enable_named_method(py::detail::ClassBase* type_object, const char* name)
  {
      const std::size_t num_enablers = sizeof(enablers) / sizeof(enablers[0]);

      // Make sure this ends with "__" since we'll only compare the head of the
      // string.  This is done to make the __getattr__<name>__/__setattr__<name>__
      // extension work.
      if (!is_special_name(name))
          return;

      for (std::size_t i = 0; i < num_enablers; ++i)
      {
          if (is_prefix(enablers[i].name + 2, name + 2))
          {
              type_object->enable(enablers[i].capability);
          }
      }
  }
}

namespace {
  // Enable any special methods which are enabled in the base class.
  void enable_special_methods(py::detail::ClassBase* derived, const Tuple& bases, const Dict& name_space)
  {
      detail::AllMethods all_methods;
      PY_CSTD_::memset(&all_methods, 0, sizeof(all_methods));

      for (std::size_t i = 0; i < bases.size(); ++i)
      {
          PyObject* base = bases[i].get();

          for (std::size_t n = 0; n < PY_ARRAY_LENGTH(enablers); ++n)
          {
              Ptr attribute(
                  PyObject_GetAttrString(base, const_cast<char*>(enablers[n].name)),
                  Ptr::null_ok);
              PyErr_Clear();
              if (attribute.get() != 0 && PyCallable_Check(attribute.get()))
                  detail::add_capability(n, derived, all_methods);
          }
      }

      Ptr keys = name_space.keys();
      for (std::size_t j = 0, len = PyList_GET_SIZE(keys.get()); j < len; ++j)
      {
          const char* name = PyString_AsString(PyList_GetItem(keys.get(), j));

          if (!is_special_name(name))
              continue;

          for (std::size_t i = 0; i < PY_ARRAY_LENGTH(enablers); ++i)
          {
              if (is_prefix(enablers[i].name + 2, name + 2))
              {
                  detail::add_capability(enablers[i].capability, derived, all_methods);
              }
          }
      }

      // Now replace those pointers with a persistent copy
      using detail::UniquePodSet;
      if (derived->tp_as_buffer)
          derived->tp_as_buffer = UniquePodSet::instance().get(*derived->tp_as_buffer);

      if (derived->tp_as_number)
          derived->tp_as_number = UniquePodSet::instance().get(*derived->tp_as_number);

      if (derived->tp_as_sequence)
          derived->tp_as_sequence = UniquePodSet::instance().get(*derived->tp_as_sequence);

      if (derived->tp_as_mapping)
          derived->tp_as_mapping = UniquePodSet::instance().get(*derived->tp_as_mapping);
  }

  void add_current_module_name(Dict& name_space)
  {
      static String module_key("__module__", String::interned);
      static String name_key("__name__", String::interned);
    
      Ptr existing_value = name_space.get_item(module_key);
      if (existing_value.get() == 0)
      {
          PyObject* globals = PyEval_GetGlobals();
          if (globals != 0) // Why don't we throw in this case? Who knows? This is
          {                 // what Python does for class objects!
              PyObject* module_name = PyDict_GetItem(globals, name_key.get());
              if (module_name != 0)
              {
                  name_space[module_key] = Ptr(module_name, Ptr::borrowed);
              }
          }
      }
  }
}

void adjust_slice_indices(PyObject* instance, int& start, int& finish)
{
    int length = Callback<int>::call_method(instance, "__len__");
    
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
const String& setattr_string()
{
    static String x("__setattr__", String::interned);
    return x;
}

const String& getattr_string()
{
    static String x("__getattr__", String::interned);
    return x;
}

const String& delattr_string()
{
    static String x("__delattr__", String::interned);
    return x;
}
}

} // namespace py
