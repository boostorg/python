// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/object/function.hpp>
#include <numeric>
#include <boost/python/errors.hpp>
#include <boost/python/objects.hpp>

namespace boost { namespace python { namespace objects { 

extern PyTypeObject function_type;

function::function(py_function implementation, unsigned min_args, unsigned max_args)
    : m_fn(implementation)
    , m_min_args(min_args)
      , m_max_args(std::max(max_args,min_args))
      , m_overloads(0)
{
    PyObject* p = this;
    PyObject_INIT(p, &function_type);
}

function::~function()
{
    PyObject* overloads = m_overloads;
    Py_XDECREF(overloads);
}
    
PyObject* function::call(PyObject* args, PyObject* keywords) const
{
    std::size_t nargs = PyTuple_GET_SIZE(args);
    function const* f = this;
    do
    {
        // Check for a plausible number of arguments
        if (nargs >= f->m_min_args && nargs <= f->m_max_args)
        {
            // Call the function
            PyObject* result = f->m_fn(args, keywords);
            
            // If the result is NULL but no error was set, m_fn failed
            // the argument-matching test.

            // This assumes that all other error-reporters are
            // well-behaved and never return NULL to python without
            // setting an error.
            if (result != 0 || PyErr_Occurred())
                return result;
        }
        f = f->m_overloads;
    }
    while (f);
    // None of the overloads matched; time to generate the error message
    argument_error(args, keywords);
    return 0;
}

void function::argument_error(PyObject* args, PyObject* keywords) const
{
    // This function needs to be improved to do better error reporting.
    PyErr_BadArgument();
}

void function::add_overload(function* overload_)
{
    Py_XINCREF(overload_);
    
    function* parent = this;
    
    while (parent->m_overloads != 0)
    {
        parent = parent->m_overloads;
    }
    parent->m_overloads = overload_;
}

void function::add_to_namespace(
    ref const& name_space, char const* name_, ref const& attribute)
{
    string const name(name_);
    PyObject* const ns = name_space.get();
    
    if (attribute->ob_type == &function_type)
    {
        PyObject* dict = 0;
        
        if (PyClass_Check(ns))
            dict = ((PyClassObject*)ns)->cl_dict;
        else if (PyType_Check(ns))
            dict = ((PyTypeObject*)ns)->tp_dict;
        else
            dict = PyObject_GetAttrString(ns, "__dict__");

        if (dict == 0)
            throw error_already_set();
        
        ref existing(PyObject_GetItem(dict, name.get()), ref::null_ok);
        
        if (existing.get() && existing->ob_type == &function_type)
        {
            static_cast<function*>(existing.get())->add_overload(
                static_cast<function*>(attribute.get()));
            return;
        }
    }
    
    // The PyObject_GetAttrString() call above left an active error
    PyErr_Clear();
    if (PyObject_SetAttr(ns, name.get(), attribute.get()) < 0)
        throw error_already_set();
}

namespace
{
  struct bind_return
  {
      bind_return(PyObject*& result, function const* f, PyObject* args, PyObject* keywords)
          : m_result(result)
            , m_f(f)
            , m_args(args)
            , m_keywords(keywords)
      {}

      void operator()() const
      {
          m_result = m_f->call(m_args, m_keywords);
      }
      
   private:
      PyObject*& m_result;
      function const* m_f;
      PyObject* m_args;
      PyObject* m_keywords;
  };
}

extern "C"
{
    // Stolen from Python's funcobject.c
    static PyObject *
    function_descr_get(PyObject *func, PyObject *obj, PyObject *type_)
    {
        if (obj == Py_None)
            obj = NULL;
        return PyMethod_New(func, obj, type_);
    }

    static void
    function_dealloc(PyObject* p)
    {
        delete static_cast<function*>(p);
    }

    static PyObject *
    function_call(PyObject *func, PyObject *args, PyObject *kw)
    {
        PyObject* result = 0;
        handle_exception(bind_return(result, static_cast<function*>(func), args, kw));
        return result;
    }
}

PyTypeObject function_type = {
    PyObject_HEAD_INIT(&PyType_Type)
    0,
    "Boost.Python.function",
    sizeof(function),
    0,
    (destructor)function_dealloc,               /* tp_dealloc */
    0,                                  /* tp_print */
    0,                                  /* tp_getattr */
    0,                                  /* tp_setattr */
    0,                                  /* tp_compare */
    0, //(reprfunc)func_repr,                   /* tp_repr */
    0,                                  /* tp_as_number */
    0,                                  /* tp_as_sequence */
    0,                                  /* tp_as_mapping */
    0,                                  /* tp_hash */
    function_call,                              /* tp_call */
    0,                                  /* tp_str */
    0, // PyObject_GenericGetAttr,            /* tp_getattro */
    0, // PyObject_GenericSetAttr,            /* tp_setattro */
    0,                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT /* | Py_TPFLAGS_HAVE_GC */,/* tp_flags */
    0,                                  /* tp_doc */
    0, // (traverseproc)func_traverse,          /* tp_traverse */
    0,                                  /* tp_clear */
    0,                                  /* tp_richcompare */
    0, //offsetof(PyFunctionObject, func_weakreflist), /* tp_weaklistoffset */
    0,                                  /* tp_iter */
    0,                                  /* tp_iternext */
    0,                                  /* tp_methods */
    0, // func_memberlist,                      /* tp_members */
    0, //func_getsetlist,                       /* tp_getset */
    0,                                  /* tp_base */
    0,                                  /* tp_dict */
    function_descr_get,                 /* tp_descr_get */
    0,                                  /* tp_descr_set */
    0, //offsetof(PyFunctionObject, func_dict),      /* tp_dictoffset */
    0,                                      /* tp_init */
    0,                                      /* tp_alloc */
    0,
    0                                       /* tp_new */
};

}}} // namespace boost::python::objects
