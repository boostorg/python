// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/converter/registry.hpp>
#include <boost/python/object/class.hpp>
#include <boost/python/objects.hpp>
#include <boost/python/detail/map_entry.hpp>
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
    struct class_registry
    {
     public:
        type_handle get(class_id id) const;
        type_handle query(class_id id) const;
        void set(class_id, type_handle class_object);
     private:
        typedef detail::map_entry<class_id,type_handle> entry;
        std::vector<entry> m_impl;
    };

    class_registry& registry()
    {
        static class_registry x;
        return x;
    }

    inline type_handle class_registry::query(class_id id) const
    {
        std::vector<entry>::const_iterator start = m_impl.begin();
        std::vector<entry>::const_iterator finish = m_impl.end();

        std::vector<entry>::const_iterator p
            = boost::detail::lower_bound(start, finish, id);

        return (p == finish || p->key != id) ? type_handle() : p->value;
    }
  
    inline type_handle class_registry::get(class_id id) const
    {
        type_handle result(this->query(id));

        if (result.get() == 0)
        {
            string report("extension class wrapper for base class ");
            (report += id.name()) += " has not been created yet";
            PyErr_SetObject(PyExc_RuntimeError, report.get());
            throw_error_already_set();
        }
        return result;
    }

    inline void class_registry::set(class_id id, type_handle object)
    {
        std::vector<entry>::iterator start = m_impl.begin();
        std::vector<entry>::iterator finish = m_impl.end();
        m_impl.insert(
            boost::detail::lower_bound(start, finish, id)
            , entry(id, object));
        converter::registry::class_object(id) = (PyTypeObject*)object.get();
    }
  }

  class_base::class_base(
      char const* name, std::size_t num_types, class_id const* const types)
  {
      class_registry& r = registry();
      assert(num_types >= 1);
      tuple bases(std::max(num_types - 1, static_cast<std::size_t>(1)));
      if (num_types > 1)
      {
          for (std::size_t i = 1; i < num_types; ++i)
              bases.set_item(i - 1, r.get(types[i]));
      }
      else
      {
          bases.set_item(0, class_type());
      }
    
      tuple args(3);
      args.set_item(0, string(name).reference());
      args.set_item(1, bases.reference());
      args.set_item(2, dictionary().reference());

      PyObject* c = PyObject_CallObject(upcast<PyObject>(class_metatype().get()), args.get());
      assert(PyType_IsSubtype(c->ob_type, &PyType_Type));
      m_object = type_handle((PyTypeObject*)c);
      r.set(types[0], m_object);
  }

  extern "C"
  {
      // This declaration needed due to broken Python 2.2 headers
      extern DL_IMPORT(PyTypeObject) PyProperty_Type;
  }

  void class_base::add_property(char const* name, handle<> const& fget)
  {
      handle<> property(PyObject_CallFunction((PyObject*)&PyProperty_Type, "O", fget.get()));
      setattr(name, property);
  }

  void class_base::add_property(char const* name, handle<> const& fget, handle<> const& fset)
  {
      handle<> property(PyObject_CallFunction((PyObject*)&PyProperty_Type, "OO", fget.get(), fset.get()));
      setattr(name, property);
  }

  void class_base::setattr(char const* name, handle<> const& x)
  {
      if (PyObject_SetAttrString(upcast<PyObject>(object().get()), const_cast<char*>(name), x.get()) < 0)
          throw_error_already_set();
  }

  BOOST_PYTHON_DECL type_handle registered_class_object(class_id id)
  {
      return registry().query(id);
  }
} // namespace objects

}} // namespace boost::python
