//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "module.h"

namespace python {

namespace {
  ref name_holder;
}

string module_builder::name()
{
    // If this fails, you haven't created a module_builder object
    assert(name_holder.get() != 0);
    return string(name_holder);
}

module_builder::module_builder(const char* name)
    : m_module(Py_InitModule(const_cast<char*>(name), initial_methods))
{
    // If this fails, you've created more than 1 module_builder object in your module    
    assert(name_holder.get() == 0);
    name_holder = ref(PyObject_GetAttrString(m_module, const_cast<char*>("__name__")));
}

void
module_builder::add(detail::function* x, const char* name)
{
    reference<detail::function> f(x); // First take possession of the object.
    detail::function::add_to_namespace(f, name, PyModule_GetDict(m_module));
}

void module_builder::add(ref x, const char* name)
{
	PyObject* dictionary = PyModule_GetDict(m_module);
    PyDict_SetItemString(dictionary, const_cast<char*>(name), x.get());
}

void module_builder::add(PyTypeObject* x, const char* name /*= 0*/)
{
    this->add(ref(as_object(x)), name ? name : x->tp_name);
}

PyMethodDef module_builder::initial_methods[] = { { 0, 0, 0, 0 } };

}
