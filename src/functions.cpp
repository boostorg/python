//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
// Revision History:
// Mar 01 01  Use PyObject_INIT() instead of trying to hand-initialize (David Abrahams)

#define BOOST_PYTHON_SOURCE

#include <boost/python/detail/functions.hpp>
#include <boost/python/detail/types.hpp>
#include <boost/python/detail/singleton.hpp>
#include <boost/python/objects.hpp>
#include <boost/python/errors.hpp>

namespace boost { namespace python { namespace detail {

struct function::type_object :
        singleton<function::type_object, callable<boost::python::detail::type_object<function> > >
{
    type_object() : singleton_base(&PyType_Type) {}
};


void function::add_to_namespace(reference<function> new_function, const char* name, PyObject* dict)
{
    dictionary d(ref(dict, ref::increment_count));
    string key(name);
    
    ref existing_object = d.get_item(key.reference());
    if (existing_object.get() == 0)
    {
        d[key] = ref(new_function.get(), ref::increment_count);
    }
    else
    {
        if (existing_object->ob_type == type_object::instance())
        {
            function* f = static_cast<function*>(existing_object.get());
            while (f->m_overloads.get() != 0)
                f = f->m_overloads.get();
            f->m_overloads = new_function;
        }
        else
        {
            PyErr_SetObject(PyExc_RuntimeError,
                            (string("Attempt to overload ") + name
                             + " failed. The existing attribute has type "
                             + existing_object->ob_type->tp_name).get());
            throw error_already_set();
        }
    }
}

function::function()
    : python_object(type_object::instance())
{
}

PyObject* function::call(PyObject* args, PyObject* keywords) const
{
    // Traverse the linked list of function overloads until we find one that
    // matches.
    for (const function* f = this; f != 0; f = f->m_overloads.get())
    {
        PyErr_Clear();
        try
        {
            PyObject* const result = f->do_call(args, keywords);
            if (result != 0)
                return result;
        }
        catch(const argument_error&)
        {
        }
    }

    // If we get here, no overloads matched the arguments

    // Allow the single-function error-reporting to take effect unless there was
    // an overload
    if (m_overloads.get() == 0)
        return 0;

    // Synthesize a more-explicit error message
    PyErr_Clear();
    string message("No overloaded functions match (");
    tuple arguments(ref(args, ref::increment_count));
    for (std::size_t i = 0; i < arguments.size(); ++i)
    {
        if (i != 0)
            message += ", ";
        message += arguments[i]->ob_type->tp_name;
    }

    message += "). Candidates are:\n";
    for (const function* f1 = this; f1 != 0; f1 = f1->m_overloads.get())
    {
        if (f1 != this)
            message += "\n";
        message += f1->description();
    }

    PyErr_SetObject(PyExc_TypeError, message.get());
    return 0;
}

// The instance class whose obj represents the type of bound_function
// objects in Python. bound_functions must be GetAttrable so the __doc__
// attribute of built-in Python functions can be accessed when bound.
struct bound_function::type_object :
    singleton<bound_function::type_object,
              getattrable<callable<boost::python::detail::type_object<bound_function> > > >
{
    type_object() : singleton_base(&PyType_Type) {}
    
private: // type_object<bound_function> hook override
    void dealloc(bound_function*) const;
};

bound_function* bound_function::create(const ref& target, const ref& fn)
{
    bound_function* const result = free_list;
    if (result == 0)
        return new bound_function(target, fn);
    
    free_list = result->m_free_list_link;
    result->m_target = target;
    result->m_unbound_function = fn;

    PyObject* self = result;
    PyObject_INIT(self, type_object::instance());
    return result;
}

bound_function::bound_function(const ref& target, const ref& fn)
    : python_object(type_object::instance()),
      m_target(target),
      m_unbound_function(fn),
      m_free_list_link(0)
{
}

PyObject*
bound_function::call(PyObject* args, PyObject* keywords) const
{
    // Build a new tuple which prepends the target to the arguments
    tuple tail_arguments(ref(args, ref::increment_count));
    ref all_arguments(PyTuple_New(tail_arguments.size() + 1));

    PyTuple_SET_ITEM(all_arguments.get(), 0, m_target.get());
    Py_INCREF(m_target.get());
    for (std::size_t i = 0; i < tail_arguments.size(); ++i)
    {
        PyTuple_SET_ITEM(all_arguments.get(), i + 1, tail_arguments[i].get());
        Py_INCREF(tail_arguments[i].get());
    }

    return PyEval_CallObjectWithKeywords(m_unbound_function.get(), all_arguments.get(), keywords);
}

PyObject* bound_function::getattr(const char* name) const
{
    return PyObject_GetAttrString(m_unbound_function.get(), const_cast<char*>(name));
}

void bound_function::type_object::dealloc(bound_function* obj) const
{
    obj->m_free_list_link = free_list;
    free_list = obj;
    obj->m_target.reset();
    obj->m_unbound_function.reset();
}

bound_function* bound_function::free_list;

}}} // namespace boost::python::detail
