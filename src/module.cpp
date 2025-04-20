//  (C) Copyright David Abrahams 2000.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/scope.hpp>
#include <boost/python/object/add_to_namespace.hpp>

namespace boost { namespace python { namespace detail {

namespace
{
    PyObject* init_module_in_scope(PyObject* m, void(*init_function)())
    {
        if (m != 0)
        {
            // Create the current module scope
            object m_obj(((borrowed_reference_t*)m));
            scope current_module(m_obj);

            if (handle_exception(init_function)) return NULL;
        }

        return m;
    }
# if PY_VERSION_HEX >= 0x03050000
    class init_function_with_state {
    public:
        init_function_with_state(void(*init_function)(void*), void* state)
            : init_function_(init_function), state_(state) {}

        void operator()() const { init_function_(state_); }
    private:
        void(*const init_function_)(void*);
        void* const state_;
    };

    PyObject* init_module_in_scope_with_state(PyObject* m, void(*init_function)(void*))
    {
        if (m != 0)
        {
            // Create the current module scope
            object m_obj(((borrowed_reference_t*)m));
            scope current_module(m_obj);

            void* state = PyModule_GetState(m);

            if (handle_exception(init_function_with_state(init_function, state))) return NULL;
        }

        return m;       
    }
# endif
}

BOOST_PYTHON_DECL void scope_setattr_doc(char const* name, object const& x, char const* doc)
{
    // Use function::add_to_namespace to achieve overloading if
    // appropriate.
    scope current;
    objects::add_to_namespace(current, name, x, doc);
}

#if PY_VERSION_HEX >= 0x03000000

BOOST_PYTHON_DECL PyObject* init_module(PyModuleDef& moduledef,
    void(*init_function)(), bool gil_not_used)
{
    PyObject *mod = PyModule_Create(&moduledef);
#ifdef Py_GIL_DISABLED
    if (mod != NULL && gil_not_used) {
        PyUnstable_Module_SetGIL(mod, Py_MOD_GIL_NOT_USED);
    }
#endif
    return init_module_in_scope(
        mod,
        init_function);
}

# if PY_VERSION_HEX >= 0x03050000

BOOST_PYTHON_DECL int exec_module(PyObject* mod, void(*init_function)())
{
    PyObject* retval = init_module_in_scope(
        mod,
        init_function);
    return retval ? 0 : -1;
}

BOOST_PYTHON_DECL int exec_module_with_state(PyObject* mod, void(*init_function)(void*))
{
    PyObject* retval = init_module_in_scope_with_state(
        mod,
        init_function);
    return retval ? 0 : -1;
}

# endif

#else

namespace
{
    PyMethodDef initial_methods[] = { { 0, 0, 0, 0 } };
}

BOOST_PYTHON_DECL PyObject* init_module(char const* name, void(*init_function)())
{
    return init_module_in_scope(
        Py_InitModule(const_cast<char*>(name), initial_methods),
        init_function);
}

#endif

}}} // namespace boost::python::detail

namespace boost { namespace python {

namespace detail
{
  BOOST_PYTHON_DECL PyObject* current_scope = 0;
}

}}
