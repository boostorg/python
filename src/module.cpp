//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/module.hpp>
#include <boost/python/errors.hpp>

namespace boost { namespace python {

namespace {
  ref name_holder;
}

bool module_base::initializing()
{
    return name_holder.get() != 0;
}

string module_base::name()
{
    // If this fails, you haven't created a module object
    assert(initializing());
    return string(name_holder);
}

module_base::module_base(const char* name)
    : m_module(Py_InitModule(const_cast<char*>(name), initial_methods))
{
    // If this fails, you've created more than 1 module object in your module    
    assert(name_holder.get() == 0);
    name_holder = ref(PyObject_GetAttrString(m_module, const_cast<char*>("__name__")));
}

module_base::~module_base()
{
    name_holder.reset();
}

void module_base::add(PyObject* x, const char* name)
{
    add(ref(x), name);
}

void module_base::add(ref x, const char* name)
{
    ref f(x); // First take possession of the object.
    if (PyObject_SetAttrString(m_module, const_cast<char*>(name), x.get()) < 0)
        throw error_already_set();
}

void module_base::add(PyTypeObject* x, const char* name /*= 0*/)
{
    this->add((PyObject*)x, name ? name : x->tp_name);
}

void module_base::add_overload(objects::function* x, const char* name)
{
    PyObject* existing = PyObject_HasAttrString(m_module, const_cast<char*>(name))
        ? PyObject_GetAttrString(m_module, const_cast<char*>(name))
        : 0;
    
    if (existing != 0 && existing->ob_type == &objects::function_type)
    {
        static_cast<objects::function*>(existing)->add_overload(x);
    }
    else
    {
        add(x, name);
    }
}

PyMethodDef module_base::initial_methods[] = { { 0, 0, 0, 0 } };

}} // namespace boost::python
