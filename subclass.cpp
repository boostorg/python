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

namespace py {

Instance::Instance(PyTypeObject* class_)
    : PythonObject(class_)
{
}

PyObject* Instance::getattr(const char* name, bool use_special_function)
{
    Ptr local_attribute = m_name_space.get_item(String(name).reference());
    
    if (local_attribute.get())
        return local_attribute.release();

    // Check its class. 
    PyObject* function =
        PyObject_GetAttrString(as_object(this->ob_type), const_cast<char*>(name));

    Ptr class_attribute;
    if (!use_special_function || function != 0)
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
            throw ErrorAlreadySet();
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

// Instance::setattr -
//
//  Implements the setattr() and delattr() functionality for our own Instance
//  objects, using the standard Python interface: if value == 0, we are deleting
//  the attribute, and returns 0 unless an error occurred.
int Instance::setattr(const char* name, PyObject* value)
{
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

// Enable any special methods which are enabled in the base class.
void enable_special_methods(TypeObjectBase* derived, const Tuple& bases, const Dict& name_space)
{
    detail::AllMethods all_methods;
    PY_CSTD_::memset(&all_methods, 0, sizeof(all_methods));
    
    for (std::size_t i = 0; i < bases.size(); ++i)
    {
        PyTypeObject* base = Downcast<PyTypeObject>(bases[i].get());
        
        for (std::size_t n = 0; n < detail::num_capabilities; ++n)
        {
            detail::add_capability(n, derived, all_methods, base);
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
                detail::add_capability(enablers[i].capability, derived, all_methods, 0);
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

// Enable the special handler for methods of the given name, if any.
void enable_named_method(TypeObjectBase* type_object, const char* name)
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
