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
#include <boost/bind.hpp>
#include <functional>
#include <vector>

namespace boost { namespace python { namespace objects { 

instance_holder::instance_holder()
    : m_next(0)
{
}

instance_holder::~instance_holder()
{
}

PyTypeObject class_metatype_object = {
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
		| Py_TPFLAGS_BASETYPE,		/* tp_flags */
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
        0,
        // PyType_GenericNew                       /* tp_new */
};

// Get the metatype object for all extension classes.
BOOST_PYTHON_DECL ref class_metatype()
{
    if (class_metatype_object.tp_dict == 0)
    {
        class_metatype_object.ob_type = &PyType_Type;
        class_metatype_object.tp_base = &PyType_Type;
        if (PyType_Ready(&class_metatype_object))
            return ref();
    }
    return ref((PyObject*)&class_metatype_object, ref::increment_count);
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

// Do we really need this? I'm beginning to think we don't!
PyTypeObject class_type_object = {
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
		| Py_TPFLAGS_BASETYPE,		/* tp_flags */
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

BOOST_PYTHON_DECL ref class_type()
{
    if (class_type_object.tp_dict == 0)
    {
        class_type_object.ob_type = (PyTypeObject*)class_metatype().release();
        class_type_object.tp_base = &PyBaseObject_Type;
        if (PyType_Ready(&class_type_object))
            return ref();
    }
    return ref((PyObject*)&class_type_object, ref::increment_count);
}

// Install the instance data for a C++ object into a Python instance
// object.
void instance_holder::install(PyObject* self) throw()
{
    assert(self->ob_type->ob_type == &class_metatype_object);
    m_next = ((instance*)self)->objects;
    ((instance*)self)->objects = this;
}

BOOST_PYTHON_DECL void*
find_instance_impl(PyObject* inst, converter::undecorated_type_id_t type)
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
      ref get(class_id id) const;
      void set(class_id, ref class_object);
   private:
      typedef detail::map_entry<class_id,ref> entry;
      std::vector<entry> m_impl;
  };

  class_registry& registry()
  {
      static class_registry x;
      return x;
  }

  ref class_registry::get(class_id id) const
  {
      std::vector<entry>::const_iterator start = m_impl.begin();
      std::vector<entry>::const_iterator finish = m_impl.end();

      std::vector<entry>::const_iterator p
          = boost::detail::lower_bound(start, finish, id);

      if (p == finish || p->key != id)
      {
          string report("extension class wrapper for base class ");
          (report += id.name()) += " has not been created yet";
          PyErr_SetObject(PyExc_RuntimeError, report.get());
          throw error_already_set();
      }
      return p->value;
  }

  void class_registry::set(class_id id, ref object)
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
    
    m_object = ref(PyObject_CallObject(class_metatype().get(), args.get()));
    r.set(types[0], m_object);
}

}}} // namespace boost::python::objects
