//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#include <boost/python/converter/registry.hpp>
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
      to_python_value_function m_to_python_converter;

      // The collection of from_python converters for the associated
      // C++ type.
      from_python_converter_base* m_from_python_converters;

      // The class object associated with this type
      PyTypeObject* m_class_object;
  };
  
  typedef std::map<type_id_t, entry> registry_t;
  
  registry_t& entries()
  {
      static registry_t registry;
      static bool builtin_converters_initialized = false;
      if (!builtin_converters_initialized)
      {
          // Make this true early because registering the builtin
          // converters will cause recursion.
          builtin_converters_initialized = true;
          
          initialize_builtin_converters();
      }
      return registry;
  }

  entry* find(type_id_t type)
  {
      return &entries()[type];
  }

  entry::entry()
      : m_to_python_converter(0)
        , m_from_python_converters(0)
        , m_class_object(0)
  {
  }
} // namespace <unnamed>

namespace registry
{
  to_python_value_function const& to_python_function(
      undecorated_type_id_t key)
  {
      return find(key)->m_to_python_converter;
  }
  
  void insert(to_python_value_function f, undecorated_type_id_t source_t)
  {
      to_python_value_function& slot = find(source_t)->m_to_python_converter;
      assert(slot == 0); // we have a problem otherwise
      if (slot != 0)
      {
          throw std::runtime_error(
              "trying to register to_python_converter for a type which already has a registered to_python_converter");
      }
      slot = f;
  }

  from_python_converter_base*& from_python_chain(type_id_t key)
  {
      return find(key)->m_from_python_converters;
  }
  
  PyTypeObject*& class_object(undecorated_type_id_t key)
  {
      return find(key)->m_class_object;
  }
} // namespace registry

}}} // namespace boost::python::converter
