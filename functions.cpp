//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "functions.h"
#include "newtypes.h"
#include "singleton.h"
#include "objects.h"
#include "errors.h"

namespace py {

struct Function::TypeObject :
        Singleton<Function::TypeObject, Callable<py::TypeObject<Function> > >
{
    TypeObject() : SingletonBase(&PyType_Type) {}
};


void Function::add_to_namespace(PyPtr<Function> new_function, const char* name, PyObject* dict)
{
    Dict d(Ptr(dict, Ptr::borrowed));
    String key(name);
    
    Ptr existing_object = d.get_item(key.reference());
    if (existing_object.get() == 0)
    {
        d[key] = Ptr(new_function.get(), Ptr::borrowed);
    }
    else
    {
        if (existing_object->ob_type == TypeObject::singleton())
        {
            Function* f = static_cast<Function*>(existing_object.get());
            while (f->m_overloads.get() != 0)
                f = f->m_overloads.get();
            f->m_overloads = new_function;
        }
        else
        {
            PyErr_SetObject(PyExc_RuntimeError,
                            (String("Attempt to overload ") + name
                             + " failed. The existing attribute has type "
                             + existing_object->ob_type->tp_name).get());
            throw ErrorAlreadySet();
        }
    }
}

Function::Function()
    : PythonObject(TypeObject::singleton())
{
}

PyObject* Function::call(PyObject* args, PyObject* keywords) const
{
    for (const Function* f = this; f != 0; f = f->m_overloads.get())
    {
        PyErr_Clear();
        try
        {
            PyObject* const result = f->do_call(args, keywords);
            if (result != 0)
                return result;
        }
        catch(const ArgumentError&)
        {
        }
    }

    if (m_overloads.get() == 0)
        return 0;

    PyErr_Clear();
    String message("No overloaded functions match (");
    Tuple arguments(Ptr(args, Ptr::borrowed));
    for (std::size_t i = 0; i < arguments.size(); ++i)
    {
        if (i != 0)
            message += ", ";
        message += arguments[i]->ob_type->tp_name;
    }

    message += "). Candidates are:\n";
    for (const Function* f1 = this; f1 != 0; f1 = f1->m_overloads.get())
    {
        if (f1 != this)
            message += "\n";
        message += f1->description();
    }

    PyErr_SetObject(PyExc_TypeError, message.get());
    return 0;
}

Ptr BoundFunction::create(Ptr target, Ptr fn)
{
    BoundFunction* result = free_list;
    if (result != 0)
    {
        free_list = result->m_free_list_link;
        result->m_target = target;
        result->m_unbound_function = fn;
    }
    else
    {
        result = new BoundFunction(target, fn);
    }
    return Ptr(result, Ptr::new_ref);
}

// The singleton class whose instance represents the type of BoundFunction
// objects in Python. BoundFunctions must be GetAttrable so the __doc__
// attribute of built-in Python functions can be accessed when bound.
struct BoundFunction::TypeObject :
    Singleton<BoundFunction::TypeObject,
              Getattrable<Callable<py::TypeObject<BoundFunction> > > >
{
    TypeObject() : SingletonBase(&PyType_Type) {}
    
private: // TypeObject<BoundFunction> hook override
    void dealloc(BoundFunction*) const;
};

BoundFunction::BoundFunction(Ptr target, Ptr fn)
    : PythonObject(TypeObject::singleton()),
      m_target(target),
      m_unbound_function(fn),
      m_free_list_link(0)
{
}

PyObject*
BoundFunction::call(PyObject* args, PyObject* keywords) const
{
    // Build a new tuple which prepends the target to the arguments
    Tuple tail_arguments(Ptr(args, Ptr::borrowed));
    Ptr all_arguments(PyTuple_New(tail_arguments.size() + 1));

    PyTuple_SET_ITEM(all_arguments.get(), 0, m_target.get());
    Py_INCREF(m_target.get());
    for (std::size_t i = 0; i < tail_arguments.size(); ++i)
    {
        PyTuple_SET_ITEM(all_arguments.get(), i + 1, tail_arguments[i].get());
        Py_INCREF(tail_arguments[i].get());
    }

    return PyEval_CallObjectWithKeywords(m_unbound_function.get(), all_arguments.get(), keywords);
}

PyObject* BoundFunction::getattr(const char* name) const
{
    return PyObject_GetAttrString(m_unbound_function.get(), const_cast<char*>(name));
}

void BoundFunction::TypeObject::dealloc(BoundFunction* instance) const
{
    instance->m_free_list_link = free_list;
    free_list = instance;
    instance->m_target.reset();
    instance->m_unbound_function.reset();
}

BoundFunction* BoundFunction::free_list;

}
