//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <set>
#include <stdexcept>

namespace boost { namespace python { namespace converter { 

namespace // <unnamed>
{
  // These are the elements stored in the registry
  struct entry
  {
      entry(type_info target);
      
      from_python_registration m_from_python;
      
      // The unique to_python converter for the associated C++ type.
      to_python_function_t m_to_python_converter;
      
      // The class object associated with this type
      PyTypeObject* m_class_object;
  };

  inline bool operator<(entry const& lhs, entry const& rhs)
  {
      return lhs.m_from_python.target_type < rhs.m_from_python.target_type;
  }
  
  typedef std::set<entry> registry_t;
  
  registry_t& entries()
  {
      static registry_t registry;

# ifdef BOOST_PYTHON_DYNAMIC_LIB // this conditional should go away eventually.
      static bool builtin_converters_initialized = false;
      if (!builtin_converters_initialized)
      {
          // Make this true early because registering the builtin
          // converters will cause recursion.
          builtin_converters_initialized = true;
          
          initialize_builtin_converters();
      }
# endif 
      return registry;
  }

  entry* get(type_info type)
  {
      return const_cast<entry*>(
          &*entries().insert(entry(type)).first
          );
  }

  entry::entry(type_info target)
      : m_from_python(target)
        , m_to_python_converter(0)
        , m_class_object(0)
  {
  }
} // namespace <unnamed>

namespace registry
{
  to_python_function_t const& get_to_python_function(
      type_info key)
  {
      return get(key)->m_to_python_converter;
  }
  
  void insert(to_python_function_t f, type_info source_t)
  {
      to_python_function_t& slot = get(source_t)->m_to_python_converter;
      assert(slot == 0); // we have a problem otherwise
      if (slot != 0)
      {
          throw std::runtime_error(
              "trying to register to_python_converter for a type which already has a registered to_python_converter");
      }
      slot = f;
  }

  // Insert an lvalue from_python converter
  void insert(convertible_function convert, type_info key)
  {
      entry* found = get(key);
      lvalue_from_python_chain *registration = new lvalue_from_python_chain;
      registration->convert = convert;
      registration->next = found->m_from_python.lvalue_chain;
      found->m_from_python.lvalue_chain = registration;
      
      insert(convert, 0, key);
  }

  // Insert an rvalue from_python converter
  void insert(void* (*convertible)(PyObject*)
              , constructor_function construct
              , type_info key)
  {
      entry* found = get(key);
      rvalue_from_python_chain *registration = new rvalue_from_python_chain;
      registration->convertible = convertible;
      registration->construct = construct;
      registration->next = found->m_from_python.rvalue_chain;
      found->m_from_python.rvalue_chain = registration;
  }

  // Insert an rvalue from_python converter
  void push_back(void* (*convertible)(PyObject*)
              , constructor_function construct
              , type_info key)
  {
      rvalue_from_python_chain** found = &get(key)->m_from_python.rvalue_chain;
      while (*found != 0)
          found = &(*found)->next;
      
      rvalue_from_python_chain *registration = new rvalue_from_python_chain;
      registration->convertible = convertible;
      registration->construct = construct;
      registration->next = 0;
      *found = registration;
  }

  PyTypeObject*& class_object(type_info key)
  {
      return get(key)->m_class_object;
  }

  from_python_registration const& from_python_converters(type_info key)
  {
      return get(key)->m_from_python;
  }
} // namespace registry

}}} // namespace boost::python::converter
