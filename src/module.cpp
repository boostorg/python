//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/detail/module_base.hpp>
#include <boost/python/object/function.hpp>
#include <boost/python/cast.hpp>

namespace boost { namespace python { namespace detail {

module_base::module_base(const char* name)
    : m_module(
        borrow(Py_InitModule(const_cast<char*>(name), initial_methods))
        )
{
}

module_base::~module_base()
{
}

void module_base::setattr(const char* name, PyObject* x)
{
    setattr(name, handle<>(x));
}

void module_base::setattr(char const* name, handle<> const& x)
{
    // Use function::add_to_namespace to achieve overloading if
    // appropriate.
    objects::function::add_to_namespace(m_module, name, x);
}

void module_base::add(type_handle const& x)
{
    this->setattr(x->tp_name, x);
}

void module_base::add_class(type_handle const& class_obj)
{
    this->add(class_obj);
    
    handle<> module_name(
        PyObject_GetAttrString(
            m_module.get(), const_cast<char*>("__name__"))
        );
    
    int status = PyObject_SetAttrString(
        python::upcast<PyObject>(class_obj.get())
        , const_cast<char*>("__module__"), module_name.get());
    
    if (status == -1)
        throw_error_already_set();
}

PyMethodDef module_base::initial_methods[] = { { 0, 0, 0, 0 } };

}}} // namespace boost::python::detail
