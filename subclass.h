//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef SUBCLASS_DWA051500_H_
# define SUBCLASS_DWA051500_H_

# include "pyconfig.h"
# include "newtypes.h"
# include "objects.h"
# include "singleton.h"
# include <boost/utility.hpp>
# include "py.h"
# include "callback.h"

namespace py {

// A simple type which acts something like a built-in Python class instance.
// TODO: implement all the special methods, like __call__, __getattr__, etc.,
// and the other special attributes, like __dict__.
class Instance : public PythonObject
{
 public:
    Instance(PyTypeObject* class_);

    // Standard Python functions.
    PyObject* repr();
    int compare(PyObject*);
    PyObject* str();
    long hash();
    PyObject* call(PyObject* args, PyObject* keywords);
    PyObject* getattr(const char* name, bool use_special_function = true);
    int setattr(const char* name, PyObject* value);

    // Mapping methods
    int length();
    PyObject* get_subscript(PyObject* key);
    void set_subscript(PyObject* key, PyObject* value);

    // Sequence methods
    PyObject* get_slice(int start, int finish);
    void set_slice(int start, int finish, PyObject* value);

    // Number methods
    PyObject* add(PyObject* other);
    PyObject* subtract(PyObject* other);
    PyObject* multiply(PyObject* other);
    PyObject* divide(PyObject* other);
    PyObject* remainder(PyObject* other);
    PyObject* divmod(PyObject* other);
    PyObject* power(PyObject*, PyObject*);
    PyObject* negative();
    PyObject* positive();
    PyObject* absolute();
    int nonzero();
    PyObject* invert();
    PyObject* lshift(PyObject* other);
    PyObject* rshift(PyObject* other);
    PyObject* do_and(PyObject* other);
    PyObject* do_xor(PyObject* other);
    PyObject* do_or(PyObject* other);
    int coerce(PyObject**, PyObject**);
    PyObject* as_int();
    PyObject* as_long();
    PyObject* as_float();
    PyObject* oct();
    PyObject* hex();

 private: // noncopyable, without the size bloat
    Instance(const Instance&);
    void operator=(const Instance&);
    
 private:
    Dict m_name_space;
};

template <class T> class MetaClass;

// A type which acts a lot like a built-in Python class. T is the instance type,
// so Class<Instance> is a very simple "class-alike".
template <class T>
class Class
    : public Getattrable<Setattrable<TypeObject<T> > >
{
 public:
    Class(MetaClass<T>* meta_class, String name, Tuple bases, const Dict& name_space);
    
    Tuple bases() const;
    String name() const;
    Dict& dict();
    
    // Standard Python functions.
    PyObject* getattr(const char* name);
    int setattr(const char* name, PyObject* value);
    PyObject* call(PyObject* args, PyObject* keywords);
    
    // the purpose of these functions is explained in extclass.cpp
    virtual void * try_class_conversions(InstanceHolderBase*) const { return 0; }
    virtual void * try_base_class_conversions(InstanceHolderBase*) const { return 0; }
    virtual void * try_derived_class_conversions(InstanceHolderBase*) const { return 0; }
    virtual void * extract_object_from_holder(InstanceHolderBase*) const { return 0; }

 protected:
    void add_base(Ptr base);
    
 private: // Implement mapping methods on instances
    PyObject* instance_repr(PyObject*) const;
    int instance_compare(PyObject*, PyObject* other) const;
    PyObject* instance_str(PyObject*) const;
    long instance_hash(PyObject*) const;
    int instance_mapping_length(PyObject*) const;
    PyObject* instance_mapping_subscript(PyObject*, PyObject*) const;
    int instance_mapping_ass_subscript(PyObject*, PyObject*, PyObject*) const;

 private: // Implement sequence methods on instances
    int instance_sequence_length(PyObject*) const;
    PyObject* instance_sequence_item(PyObject* instance, int n) const;
    int instance_sequence_ass_item(PyObject* instance, int n, PyObject* value) const;
    PyObject* instance_sequence_slice(PyObject*, int start, int finish) const;
    int instance_sequence_ass_slice(PyObject*, int start, int finish, PyObject* value) const;

 private: // Implement number methods on instances
    PyObject* instance_number_add(PyObject*, PyObject*) const;
    PyObject* instance_number_subtract(PyObject*, PyObject*) const;
    PyObject* instance_number_multiply(PyObject*, PyObject*) const;
    PyObject* instance_number_divide(PyObject*, PyObject*) const;
    PyObject* instance_number_remainder(PyObject*, PyObject*) const;
    PyObject* instance_number_divmod(PyObject*, PyObject*) const;
    PyObject* instance_number_power(PyObject*, PyObject*, PyObject*) const;
    PyObject* instance_number_negative(PyObject*) const;
    PyObject* instance_number_positive(PyObject*) const;
    PyObject* instance_number_absolute(PyObject*) const;
    int instance_number_nonzero(PyObject*) const;
    PyObject* instance_number_invert(PyObject*) const;
    PyObject* instance_number_lshift(PyObject*, PyObject*) const;
    PyObject* instance_number_rshift(PyObject*, PyObject*) const;
    PyObject* instance_number_and(PyObject*, PyObject*) const;
    PyObject* instance_number_xor(PyObject*, PyObject*) const;
    PyObject* instance_number_or(PyObject*, PyObject*) const;
    int instance_number_coerce(PyObject*, PyObject**, PyObject**) const;
    PyObject* instance_number_int(PyObject*) const;
    PyObject* instance_number_long(PyObject*) const;
    PyObject* instance_number_float(PyObject*) const;
    PyObject* instance_number_oct(PyObject*) const;
    PyObject* instance_number_hex(PyObject*) const;
    
 private: // Miscellaneous "special" methods
    PyObject* instance_call(PyObject* instance, PyObject* args, PyObject* keywords) const;

 private: // noncopyable, without the size bloat
    Class(const Class<T>&);
    void operator=(const Class&);
    
 private:
    String m_name;
    Tuple m_bases;
    Dict m_name_space;
};

// Don't really need to be friends, but are essentially part of the Class interface.
// These operate on TypeObjectBase just to save on code space.
void enable_special_methods(TypeObjectBase*, const Tuple& bases, const Dict& name_space);
void enable_named_method(TypeObjectBase*, const char*);
    
// The type of a Class<T> object.
template <class T>
class MetaClass
    : public Callable<Getattrable<Setattrable<TypeObject<Class<T> > > > >,
      boost::noncopyable
{
 public:
    MetaClass();

    // Standard Python functions.
    PyObject* call(PyObject* args, PyObject* keywords);
 private:
    
    struct TypeObject
        : Singleton<TypeObject, Callable<py::TypeObject<MetaClass> > >
    {
        TypeObject() : SingletonBase(&PyType_Type) {}
    };
};

// Add the name of the module currently being loaded to the name_space with the
// key "__module__". If no module is being loaded, or if name_space already has
// a key "__module", has no effect. This is not really a useful public
// interface; it's just used for Class<>::Class() below.
void add_current_module_name(Dict&);

//
// Member function implementations.
//
template <class T>
MetaClass<T>::MetaClass()
    : Properties(TypeObject::singleton())
{
} 

template <class T>
Class<T>::Class(MetaClass<T>* meta_class, String name, Tuple bases, const Dict& name_space)
    : Properties(meta_class, name.c_str()),
      m_name(name),
      m_bases(bases),
      m_name_space(name_space)
{
    add_current_module_name(m_name_space);
    enable_special_methods(this, bases, name_space);
}

template <class T>
String Class<T>::name() const
{
    return m_name;
}

template <class T>
PyObject* Class<T>::getattr(const char* name)
{
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
            return base_attribute;
    }
    return 0;
}

template <class T>
int Class<T>::setattr(const char* name, PyObject* value)
{
    if (PyCallable_Check(value))
        enable_named_method(this, name);
    
    return PyDict_SetItemString(
        m_name_space.reference().get(), const_cast<char*>(name), value);
}

template <class T>
PyObject* Class<T>::call(PyObject* args, PyObject* keywords)
{
    PyPtr<T> result(new T(this));

    // Getting the init function off the result instance should result in a
    // bound method.
    PyObject* const init_function = result->getattr("__init__", false);
        
    if (init_function == 0)
    {
        if (PyErr_Occurred() && PyErr_ExceptionMatches(PyExc_AttributeError)) {
            PyErr_Clear(); // no __init__? That's legal.
        }
        else {
            return 0; // Something else? Keep the error
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
    
    return result.release();
}

template <class T>
PyObject* Class<T>::instance_repr(PyObject* instance) const
{
    return Downcast<T>(instance)->repr();
}

template <class T>
int Class<T>::instance_compare(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->compare(other);
}

template <class T>
PyObject* Class<T>::instance_str(PyObject* instance) const
{
    return Downcast<T>(instance)->str();
}

template <class T>
long Class<T>::instance_hash(PyObject* instance) const
{
    return Downcast<T>(instance)->hash();
}

template <class T>
int Class<T>::instance_mapping_length(PyObject* instance) const
{
    return Downcast<T>(instance)->length();
}

template <class T>
int Class<T>::instance_sequence_length(PyObject* instance) const
{
    return Downcast<T>(instance)->length();
}

template <class T>
PyObject* Class<T>::instance_mapping_subscript(PyObject* instance, PyObject* key) const
{
    return Downcast<T>(instance)->get_subscript(key);
}

template <class T>
PyObject* Class<T>::instance_sequence_item(PyObject* instance, int n) const
{
    Ptr key(to_python(n));
    return Downcast<T>(instance)->get_subscript(key.get());
}

template <class T>
int Class<T>::instance_sequence_ass_item(PyObject* instance, int n, PyObject* value) const
{
    Ptr key(to_python(n));
    Downcast<T>(instance)->set_subscript(key.get(), value);
    return 0;
}

template <class T>
int Class<T>::instance_mapping_ass_subscript(PyObject* instance, PyObject* key, PyObject* value) const
{
    Downcast<T>(instance)->set_subscript(key, value);
    return 0;
}

void adjust_slice_indices(PyObject* instance, int& start, int& finish);

template <class T>
PyObject* Class<T>::instance_sequence_slice(PyObject* instance, int start, int finish) const
{
    adjust_slice_indices(instance, start, finish);    
    return Downcast<T>(instance)->get_slice(start, finish);
}

template <class T>
int Class<T>::instance_sequence_ass_slice(PyObject* instance, int start, int finish, PyObject* value) const
{
    adjust_slice_indices(instance, start, finish);
    Downcast<T>(instance)->set_slice(start, finish, value);
    return 0;
}

template <class T>
PyObject* Class<T>::instance_call(PyObject* instance, PyObject* args, PyObject* keywords) const
{
    return Downcast<T>(instance)->call(args, keywords);
}

template <class T>
PyObject* Class<T>::instance_number_add(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->add(other);
}

template <class T>
PyObject* Class<T>::instance_number_subtract(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->subtract(other);
}

template <class T>
PyObject* Class<T>::instance_number_multiply(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->multiply(other);
}

template <class T>
PyObject* Class<T>::instance_number_divide(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->divide(other);
}

template <class T>
PyObject* Class<T>::instance_number_remainder(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->remainder(other);
}

template <class T>
PyObject* Class<T>::instance_number_divmod(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->divmod(other);
}

template <class T>
PyObject* Class<T>::instance_number_power(PyObject* instance, PyObject* exponent, PyObject* modulus) const
{
    return Downcast<T>(instance)->power(exponent, modulus);
}

template <class T>
PyObject* Class<T>::instance_number_negative(PyObject* instance) const
{
    return Downcast<T>(instance)->negative();
}

template <class T>
PyObject* Class<T>::instance_number_positive(PyObject* instance) const
{
    return Downcast<T>(instance)->positive();
}

template <class T>
PyObject* Class<T>::instance_number_absolute(PyObject* instance) const
{
    return Downcast<T>(instance)->absolute();
}

template <class T>
int Class<T>::instance_number_nonzero(PyObject* instance) const
{
    return Downcast<T>(instance)->nonzero();
}

template <class T>
PyObject* Class<T>::instance_number_invert(PyObject* instance) const
{
    return Downcast<T>(instance)->invert();
}

template <class T>
PyObject* Class<T>::instance_number_lshift(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->lshift(other);
}

template <class T>
PyObject* Class<T>::instance_number_rshift(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->rshift(other);
}

template <class T>
PyObject* Class<T>::instance_number_and(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->do_and(other);
}

template <class T>
PyObject* Class<T>::instance_number_xor(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->do_xor(other);
}

template <class T>
PyObject* Class<T>::instance_number_or(PyObject* instance, PyObject* other) const
{
    return Downcast<T>(instance)->do_or(other);
}

template <class T>
int Class<T>::instance_number_coerce(PyObject* instance, PyObject** x, PyObject** y) const
{
    return Downcast<T>(instance)->coerce(x, y);
}

template <class T>
PyObject* Class<T>::instance_number_int(PyObject* instance) const
{
    return Downcast<T>(instance)->as_int();
}

template <class T>
PyObject* Class<T>::instance_number_long(PyObject* instance) const
{
    return Downcast<T>(instance)->as_long();
}

template <class T>
PyObject* Class<T>::instance_number_float(PyObject* instance) const
{
    return Downcast<T>(instance)->as_float();
}

template <class T>
PyObject* Class<T>::instance_number_oct(PyObject* instance) const
{
    return Downcast<T>(instance)->oct();
}

template <class T>
PyObject* Class<T>::instance_number_hex(PyObject* instance) const
{
    return Downcast<T>(instance)->hex();
}

template <class T>
Dict& Class<T>::dict()
{
    return m_name_space;
}

template <class T>
Tuple Class<T>::bases() const
{
    return m_bases;
}

template <class T>
void Class<T>::add_base(Ptr base)
{
    Tuple new_bases(m_bases.size() + 1);
    for (std::size_t i = 0; i < m_bases.size(); ++i)
        new_bases.set_item(i, m_bases[i]);
    new_bases.set_item(m_bases.size(), base);
    m_bases = new_bases;
}

template <class T>
PyObject* MetaClass<T>::call(PyObject* args, PyObject* /*keywords*/)
{
    PyObject* name;
    PyObject* bases;
    PyObject* name_space;
    
    if (!PyArg_ParseTuple(args, const_cast<char*>("O!O!O!"),
                          &PyString_Type, &name,
                          &PyTuple_Type, &bases,
                          &PyDict_Type, &name_space))
    {
        return 0;
    }
    
    return as_object(
        new Class<T>(this, String(Ptr(name, Ptr::borrowed)),
                  Tuple(Ptr(bases, Ptr::borrowed)),
                  Dict(Ptr(name_space, Ptr::borrowed)))
        );
}

namespace detail {
const String& setattr_string();
const String& getattr_string();
const String& delattr_string();
}


} // namespace py
#endif
