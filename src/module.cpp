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
#include <boost/python/scope.hpp>
#include <boost/python/borrowed.hpp>
#include <boost/python/object.hpp>
#include <boost/python/detail/raw_pyobject.hpp>

namespace boost { namespace python { namespace detail {

module_base::module_base(char const* name, char const* doc)
    : m_module(
        allow_null(python::borrowed(
                       scope().ptr()
                       )))
{
    if (doc != 0)
        scope().attr("__doc__") = doc;
}

module_base::~module_base()
{
}

void module_base::setattr_doc(const char* name, python::object const& x, char const* doc)
{
    // Use function::add_to_namespace to achieve overloading if
    // appropriate.
    objects::function::add_to_namespace(python::object(m_module), name, x, doc);
}

void module_base::add(type_handle const& x)
{
    this->setattr_doc(x->tp_name, python::object(x), 0);
}

PyMethodDef module_base::initial_methods[] = { { 0, 0, 0, 0 } };

namespace
{
  PyMethodDef initial_methods[] = { { 0, 0, 0, 0 } };
}

BOOST_PYTHON_DECL void init_module(char const* name, void(*init_function)())
{
    
    PyObject* m
        = Py_InitModule(const_cast<char*>(name), initial_methods);

    if (m != 0)
    {
        ;
        
        // Create the current module scope
        scope current_module(
            (object(
                ((borrowed_reference_t*)m)
                ))
            );
        
        handle_exception(init_function);
    }
}

}}} // namespace boost::python::detail

namespace boost { namespace python {

BOOST_PYTHON_DECL PyObject* scope::current_scope = Py_None;

}}
