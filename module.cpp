//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "module.h"

namespace py {

Module::Module(const char* name)
    : m_module(Py_InitModule(const_cast<char*>(name), initial_methods))
{
}

void
Module::add(Function* x, const char* name)
{
    PyPtr<Function> f(x); // First take possession of the object.
    Function::add_to_namespace(f, name, PyModule_GetDict(m_module));
}

void Module::add(Ptr x, const char* name)
{
	PyObject* dictionary = PyModule_GetDict( m_module );
    PyDict_SetItemString(dictionary, const_cast<char*>(name), x.get());
}

void Module::add(PyTypeObject* x, const char* name /*= 0*/)
{
    this->add(Ptr(as_object(x), Ptr::new_ref),
        name ? name : x->tp_name);
}

PyMethodDef Module::initial_methods[] = { { 0, 0, 0, 0 } };

}
