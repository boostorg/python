//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <map>
#include <stdexcept>

namespace boost { namespace python { namespace converter { 

namespace // <unnamed>
{
  // These are the elements stored in the registry
  struct entry
  {
      entry();
      
      // The unique to_python converter for the associated C++ type.
      to_python_function_t m_to_python_converter;
      
      // The collection of from_python converters for the associated
      // C++ type.
      lvalue_from_python_registration* m_lvalue_from_python;
      rvalue_from_python_registration* m_rvalue_from_python;

      // The class object associated with this type
      PyTypeObject* m_class_object;
  };
  
  typedef std::map<undecorated_type_id_t, entry> registry_t;
  
  registry_t& entries()
  {
      static registry_t registry;
      
#ifdef BOOST_PYTHON_DYNAMIC_LIB // this conditional should go away eventually.
      static bool builtin_converters_initialized = false;
      if (!builtin_converters_initialized)
      {
          // Make this true early because registering the builtin
          // converters will cause recursion.
          builtin_converters_initialized = true;
          
          initialize_builtin_converters();
      }
#endif 
      return registry;
  }

  entry* find(undecorated_type_id_t type)
  {
      return &entries()[type];
  }

  entry::entry()
      : m_to_python_converter(0)
        , m_lvalue_from_python(0)
        , m_rvalue_from_python(0)
        , m_class_object(0)
  {
  }
} // namespace <unnamed>

namespace registry
{
  to_python_function_t const& get_to_python_function(
      undecorated_type_id_t key)
  {
      return find(key)->m_to_python_converter;
  }
  
  void insert(to_python_function_t f, undecorated_type_id_t source_t)
  {
      to_python_function_t& slot = find(source_t)->m_to_python_converter;
      assert(slot == 0); // we have a problem otherwise
      if (slot != 0)
      {
          throw std::runtime_error(
              "trying to register to_python_converter for a type which already has a registered to_python_converter");
      }
      slot = f;
  }

  // Insert an lvalue from_python converter
  void insert(void* (*convert)(PyObject*), undecorated_type_id_t key)
  {
      entry* found = find(key);
      lvalue_from_python_registration *registration = new lvalue_from_python_registration;
      registration->convert = convert;
      registration->next = found->m_lvalue_from_python;
      found->m_lvalue_from_python = registration;
      
      insert(convert, 0, key);
  }

  // Insert an rvalue from_python converter
  void insert(void* (*convertible)(PyObject*)
              , constructor_function construct
              , undecorated_type_id_t key)
  {
      entry* found = find(key);
      rvalue_from_python_registration *registration = new rvalue_from_python_registration;
      registration->convertible = convertible;
      registration->construct = construct;
      registration->next = found->m_rvalue_from_python;
      found->m_rvalue_from_python = registration;
  }

  // Insert an rvalue from_python converter
  void push_back(void* (*convertible)(PyObject*)
              , constructor_function construct
              , undecorated_type_id_t key)
  {
      rvalue_from_python_registration** found = &find(key)->m_rvalue_from_python;
      while (*found != 0)
          found = &(*found)->next;
      
      rvalue_from_python_registration *registration = new rvalue_from_python_registration;
      registration->convertible = convertible;
      registration->construct = construct;
      registration->next = 0;
      *found = registration;
  }

  PyTypeObject*& class_object(undecorated_type_id_t key)
  {
      return find(key)->m_class_object;
  }

  lvalue_from_python_registration*& lvalue_converters(undecorated_type_id_t key)
  {
      return find(key)->m_lvalue_from_python;
  }
  
  rvalue_from_python_registration*& rvalue_converters(undecorated_type_id_t key)
  {
      return find(key)->m_rvalue_from_python;
  }
  
} // namespace registry

}}} // namespace boost::python::converter
