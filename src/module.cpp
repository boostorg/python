//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/detail/module_base.hpp>
#include <boost/python/object/function.hpp>

namespace boost { namespace python { namespace detail {

module_base::module_base(const char* name)
    : m_module(
        Py_InitModule(const_cast<char*>(name), initial_methods)
        , ref::increment_count)
{
}

module_base::~module_base()
{
}

void module_base::setattr(const char* name, PyObject* x)
{
    setattr(name, ref(x));
}

void module_base::setattr(char const* name, ref const& x)
{
    // Use function::add_to_namespace to achieve overloading if
    // appropriate.
    objects::function::add_to_namespace(m_module, name, x);
}

void module_base::add(PyTypeObject* x)
{
    this->setattr(x->tp_name, (PyObject*)x);
}

void module_base::add_type(ref x)
{
    assert(PyObject_TypeCheck(x.get(), &PyType_Type));
    add((PyTypeObject*)x.release());
}

void module_base::add_class(ref const& class_obj)
{
    this->add_type(class_obj);
    
    ref module_name(
        PyObject_GetAttrString(
            m_module.get(), const_cast<char*>("__name__"))
        );
    
    int status = PyObject_SetAttrString(
        class_obj.get(), const_cast<char*>("__module__"), module_name.get());
    
    if (status == -1)
        throw_error_already_set();
}

PyMethodDef module_base::initial_methods[] = { { 0, 0, 0, 0 } };

}}} // namespace boost::python::detail
