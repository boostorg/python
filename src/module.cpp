//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/module.hpp>

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
    : m_module(
        Py_InitModule(const_cast<char*>(name), initial_methods)
        , ref::increment_count)
{
    // If this fails, you've created more than 1 module object in your module    
    assert(name_holder.get() == 0);
    name_holder = ref(PyObject_GetAttrString(
                          m_module.get() , const_cast<char*>("__name__")));
}

module_base::~module_base()
{
    name_holder.reset();
}

void module_base::add(PyObject* x, const char* name)
{
    add(ref(x), name);
}

void module_base::add(ref const& x, const char* name)
{
    // Use function::add_to_namespace to achieve overloading if
    // appropriate.
    objects::function::add_to_namespace(m_module, name, x);
}

void module_base::add(PyTypeObject* x, const char* name /*= 0*/)
{
    this->add((PyObject*)x, name ? name : x->tp_name);
}

PyMethodDef module_base::initial_methods[] = { { 0, 0, 0, 0 } };

}} // namespace boost::python
