// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/scope.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/object/class.hpp>
#include <boost/python/object/find_instance.hpp>
#include <boost/python/object/pickle_support.hpp>
#include <boost/python/detail/map_entry.hpp>
#include <boost/python/object.hpp>
#include <boost/python/object_protocol.hpp>
#include <boost/detail/binary_search.hpp>
#include <boost/python/self.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <vector>

namespace boost { namespace python {

# ifdef BOOST_PYTHON_SELF_IS_CLASS
namespace self_ns
{
  self_t self;
}
# endif 

instance_holder::instance_holder()
    : m_next(0)
{
}

instance_holder::~instance_holder()
{
}

// This is copied from typeobject.c in the Python sources. Even though
// class_metatype_object doesn't set Py_TPFLAGS_HAVE_GC, that bit gets
// filled in by the base class initialization process in
// PyType_Ready(). However, tp_is_gc is *not* copied from the base
// type, making it assume that classes are GC-able even if (like
// class_type_object) they're statically allocated.
static int
type_is_gc(PyTypeObject *python_type)
{
    return python_type->tp_flags & Py_TPFLAGS_HEAPTYPE;
}

static PyTypeObject class_metatype_object = {
    PyObject_HEAD_INIT(0)//&PyType_Type)
    0,
    "Boost.Python.class",
    PyType_Type.tp_basicsize,
    0,
    0,                                      /* tp_dealloc */
    0,                                      /* tp_print */
    0,                                      /* tp_getattr */
    0,                                      /* tp_setattr */
    0,                                      /* tp_compare */
    0,                                      /* tp_repr */
    0,                                      /* tp_as_number */
    0,                                      /* tp_as_sequence */
    0,                                      /* tp_as_mapping */
    0,                                      /* tp_hash */
    0,                                      /* tp_call */
    0,                                      /* tp_str */
    0,                                      /* tp_getattro */
    0,                                      /* tp_setattro */
    0,                                      /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT // | Py_TPFLAGS_HAVE_GC
    | Py_TPFLAGS_BASETYPE,          /* tp_flags */
    0,                                      /* tp_doc */
    0,                                      /* tp_traverse */
    0,                                      /* tp_clear */
    0,                                      /* tp_richcompare */
    0,                                      /* tp_weaklistoffset */
    0,                                      /* tp_iter */
    0,                                      /* tp_iternext */
    0,                                      /* tp_methods */
    0,                                      /* tp_members */
    0,                                      /* tp_getset */
    0, //&PyType_Type,                           /* tp_base */
    0,                                      /* tp_dict */
    0,                                      /* tp_descr_get */
    0,                                      /* tp_descr_set */
    0,                                      /* tp_dictoffset */
    0,                                      /* tp_init */
    0,                                      /* tp_alloc */
    0, // filled in with type_new           /* tp_new */
    0, // filled in with __PyObject_GC_Del  /* tp_free */
    (inquiry)type_is_gc,                    /* tp_is_gc */
};

// Install the instance data for a C++ object into a Python instance
// object.
void instance_holder::install(PyObject* self) throw()
{
    assert(self->ob_type->ob_type == &class_metatype_object);
    m_next = ((objects::instance*)self)->objects;
    ((objects::instance*)self)->objects = this;
}


namespace objects
{
// Get the metatype object for all extension classes.
  BOOST_PYTHON_DECL type_handle class_metatype()
  {
      if (class_metatype_object.tp_dict == 0)
      {
          class_metatype_object.ob_type = &PyType_Type;
          class_metatype_object.tp_base = &PyType_Type;
          if (PyType_Ready(&class_metatype_object))
              return type_handle();
      }
      return type_handle(borrowed(&class_metatype_object));
  }
  extern "C"
  {
      static void instance_dealloc(PyObject* inst)
      {
          instance* kill_me = (instance*)inst;

          for (instance_holder* p = kill_me->objects, *next; p != 0; p = next)
          {
              next = p->next();
              delete p;
          }
        
          inst->ob_type->tp_free(inst);
      }
  }


  static PyTypeObject class_type_object = {
      PyObject_HEAD_INIT(0) //&class_metatype_object)
      0,
      "Boost.Python.instance",
      sizeof(instance),
      0,
      instance_dealloc,                       /* tp_dealloc */
      0,                                      /* tp_print */
      0,                                      /* tp_getattr */
      0,                                      /* tp_setattr */
      0,                                      /* tp_compare */
      0,                                      /* tp_repr */
      0,                                      /* tp_as_number */
      0,                                      /* tp_as_sequence */
      0,                                      /* tp_as_mapping */
      0,                                      /* tp_hash */
      0,                                      /* tp_call */
      0,                                      /* tp_str */
      0,                                      /* tp_getattro */
      0,                                      /* tp_setattro */
      0,                                      /* tp_as_buffer */
      Py_TPFLAGS_DEFAULT // | Py_TPFLAGS_HAVE_GC
      | Py_TPFLAGS_BASETYPE,          /* tp_flags */
      0,                                      /* tp_doc */
      0,                                      /* tp_traverse */
      0,                                      /* tp_clear */
      0,                                      /* tp_richcompare */
      0,                                      /* tp_weaklistoffset */
      0,                                      /* tp_iter */
      0,                                      /* tp_iternext */
      0,                                      /* tp_methods */
      0,                                      /* tp_members */
      0,                                      /* tp_getset */
      0, //&PyBaseObject_Type,                     /* tp_base */
      0,                                      /* tp_dict */
      0,                                      /* tp_descr_get */
      0,                                      /* tp_descr_set */
      0,                                      /* tp_dictoffset */
      0,                                      /* tp_init */
      PyType_GenericAlloc,                    /* tp_alloc */
      PyType_GenericNew
  };

  BOOST_PYTHON_DECL type_handle class_type()
  {
      if (class_type_object.tp_dict == 0)
      {
          class_type_object.ob_type = incref(class_metatype().get());
          class_type_object.tp_base = &PyBaseObject_Type;
          if (PyType_Ready(&class_type_object))
              return type_handle();
      }
      return type_handle(borrowed(&class_type_object));
  }

  BOOST_PYTHON_DECL void*
  find_instance_impl(PyObject* inst, type_info type)
  {
      if (inst->ob_type->ob_type != &class_metatype_object)
          return 0;
    
      instance* self = reinterpret_cast<instance*>(inst);

      for (instance_holder* match = self->objects; match != 0; match = match->next())
      {
          void* const found = match->holds(type);
          if (found)
              return found;
      }
      return 0;
  }

  namespace
  {
    // Find a registered class object corresponding to id. Return a
    // null handle if no such class is registered.
    inline type_handle query_class(class_id id)
    {
        converter::registration const* p = converter::registry::query(id);
        return type_handle(
            python::borrowed(
                python::allow_null(p ? p->class_object : 0))
            );
    }

    // Find a registered class corresponding to id. If not found,
    // throw an appropriate exception.
    type_handle get_class(class_id id)
    {
        type_handle result(query_class(id));

        if (result.get() == 0)
        {
            object report("extension class wrapper for base class ");
            report = report + id.name() + " has not been created yet";
            PyErr_SetObject(PyExc_RuntimeError, report.ptr());
            throw_error_already_set();
        }
        return result;
    }
  }

  // class_base constructor
  //
  // name -      the name of the new Python class
  //
  // num_types - one more than the number of declared bases
  //
  // types -     array of python::type_info, the first item
  //             corresponding to the class being created, and the
  //             rest corresponding to its declared bases.
  //

  namespace
  {
    inline object
    new_class(char const* name, std::size_t num_types, class_id const* const types)
    {
      assert(num_types >= 1);
      
      // Build a tuple of the base Python type objects. If no bases
      // were declared, we'll use our class_type() as the single base
      // class.
      std::size_t const num_bases = std::max(num_types - 1, static_cast<std::size_t>(1));
      handle<> bases(PyTuple_New(num_bases));

      for (std::size_t i = 1; i <= num_bases; ++i)
      {
          type_handle c = (i >= num_types) ? class_type() : get_class(types[i]);
          // PyTuple_SET_ITEM steals this reference
          PyTuple_SET_ITEM(bases.get(), i - 1, upcast<PyObject>(c.release()));
      }

      object module_name = PyObject_IsInstance(scope().ptr(), upcast<PyObject>(&PyModule_Type))
          ? scope().attr("__name__")
          : api::getattr(scope(), "__module__", object(""))
          ;

      if (module_name)
          module_name += '.';
      
      // Build the (name, bases, dict) tuple for creating the new class
      handle<> args(PyTuple_New(3));
      PyTuple_SET_ITEM(args.get(), 0, incref((module_name + name).ptr()));
      PyTuple_SET_ITEM(args.get(), 1, bases.release());
      handle<> d(PyDict_New());
      PyTuple_SET_ITEM(args.get(), 2, d.release());

      // Call the class metatype to create a new class
      PyObject* c = PyObject_CallObject(upcast<PyObject>(class_metatype().get()), args.get());
      assert(PyType_IsSubtype(c->ob_type, &PyType_Type));
      object result = object(python::detail::new_reference(c));
      
      if (scope().ptr() != Py_None)
          scope().attr(name) = result;

      return result;
    }
  }
  
  class_base::class_base(
      char const* name, std::size_t num_types, class_id const* const types, char const* doc)
      : object(new_class(name, num_types, types))
  {
      // Insert the new class object in the registry
      converter::registration& converters = const_cast<converter::registration&>(
          converter::registry::lookup(types[0]));

      // Class object is leaked, for now
      converters.class_object = (PyTypeObject*)incref(this->ptr());

      if (doc)
          this->attr("__doc__") = doc;
  }

  extern "C"
  {
      // This declaration needed due to broken Python 2.2 headers
      extern DL_IMPORT(PyTypeObject) PyProperty_Type;
  }

  void class_base::add_property(char const* name, object const& fget)
  {
      object property(
          (python::detail::new_reference)
              PyObject_CallFunction((PyObject*)&PyProperty_Type, "O", fget.ptr()));
      
      this->setattr(name, property);
  }

  void class_base::add_property(char const* name, object const& fget, object const& fset)
  {
      object property(
          (python::detail::new_reference)
              PyObject_CallFunction((PyObject*)&PyProperty_Type, "OO", fget.ptr(), fset.ptr()));
      
      this->setattr(name, property);
  }

  void class_base::setattr(char const* name, object const& x)
  {
      if (PyObject_SetAttrString(this->ptr(), const_cast<char*>(name), x.ptr()) < 0)
          throw_error_already_set();
  }

  namespace
  {
    extern "C" PyObject* no_init(PyObject*, PyObject*)
    {
        ::PyErr_SetString(::PyExc_RuntimeError, "This class cannot be instantiated from Python");
        return NULL;
    }
    static ::PyMethodDef no_init_def = {
        "__init__", no_init, METH_VARARGS,
        "Raises an exception\n"
        "This class cannot be instantiated from Python\n"
    };
  }
  
  void class_base::def_no_init()
  {
      handle<> f(::PyCFunction_New(&no_init_def, 0));
      this->setattr("__init__", object(f));
  }

  void class_base::enable_pickling(bool getstate_manages_dict)
  {
      setattr("__reduce__", object(make_instance_reduce_function()));
      setattr("__safe_for_unpickling__", object(true));
      
      if (getstate_manages_dict)
      {
          setattr("__getstate_manages_dict__", object(true));
      }
  }

  BOOST_PYTHON_DECL type_handle registered_class_object(class_id id)
  {
      return query_class(id);
  }
} // namespace objects

}} // namespace boost::python
