//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <boost/python/converter/python_type.hpp>

#include <set>
#include <map>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

#if defined(__APPLE__) && defined(__MACH__) && defined(__GNUC__) \
 && __GNUC__ == 3 && __GNUC_MINOR__ <= 4 && !defined(__APPLE_CC__)
# define BOOST_PYTHON_CONVERTER_REGISTRY_APPLE_MACH_WORKAROUND
#endif

#if defined(BOOST_PYTHON_TRACE_REGISTRY) \
 || defined(BOOST_PYTHON_CONVERTER_REGISTRY_APPLE_MACH_WORKAROUND)
# include <iostream>
#endif

namespace boost { namespace python { namespace converter { 

BOOST_PYTHON_DECL PyTypeObject* registration::get_class_object() const
{
    if (this->m_class_object == 0)
    {
        ::PyErr_Format(
            PyExc_TypeError
            , const_cast<char*>("No Python class registered for C++ class %s")
            , this->target_type.name());
    
        throw_error_already_set();
    }
    
    return this->m_class_object;
}
  
BOOST_PYTHON_DECL PyObject* registration::to_python(void const volatile* source) const
{
    if (this->m_to_python == 0)
    {
        handle<> msg(
            ::PyString_FromFormat(
                "No to_python (by-value) converter found for C++ type: %s"
                , this->target_type.name()
                )
            );
            
        PyErr_SetObject(PyExc_TypeError, msg.get());

        throw_error_already_set();
    }
        
    return source == 0
        ? incref(Py_None)
        : this->m_to_python(const_cast<void*>(source));
}

namespace // <unnamed>
{
  typedef registration entry;
  
  typedef std::set<entry> registry_t;
  
#ifndef BOOST_PYTHON_CONVERTER_REGISTRY_APPLE_MACH_WORKAROUND
  registry_t& entries()
  {
      static registry_t registry;

# ifndef BOOST_PYTHON_SUPPRESS_REGISTRY_INITIALIZATION
      static bool builtin_converters_initialized = false;
      if (!builtin_converters_initialized)
      {
          // Make this true early because registering the builtin
          // converters will cause recursion.
          builtin_converters_initialized = true;
          
          initialize_builtin_converters();
      }
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      std::cout << "registry: ";
      for (registry_t::iterator p = registry.begin(); p != registry.end(); ++p)
      {
          std::cout << p->target_type << "; ";
      }
      std::cout << '\n';
#  endif 
# endif 
      return registry;
  }
#else
  registry_t& static_registry()
  {
    static registry_t result;
    return result;
  }

  bool static_builtin_converters_initialized()
  {
    static bool result = false;
    if (result == false) {
      result = true;
      std::cout << std::flush;
      return false;
    }
    return true;
  }

  registry_t& entries()
  {
# ifndef BOOST_PYTHON_SUPPRESS_REGISTRY_INITIALIZATION
      if (!static_builtin_converters_initialized())
      {
          initialize_builtin_converters();
      }
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      std::cout << "registry: ";
      for (registry_t::iterator p = static_registry().begin(); p != static_registry().end(); ++p)
      {
          std::cout << p->target_type << "; ";
      }
      std::cout << '\n';
#  endif 
# endif 
      return static_registry();
  }
#endif // BOOST_PYTHON_CONVERTER_REGISTRY_APPLE_MACH_WORKAROUND

  entry* get(type_info type)
  {
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      registry_t::iterator p = entries().find(entry(type));
      
      std::cout << "looking up " << type << ": "
                << (p == entries().end() || p->target_type != type
                    ? "...NOT found\n" : "...found\n");
#  endif
      std::pair<registry_t::const_iterator,bool> pos_ins
          = entries().insert(entry(type));
      
#  if __MWERKS__ >= 0x3000
      // do a little invariant checking if a change was made
      if ( pos_ins.second )
          assert(entries().invariants());
#  endif
      return const_cast<entry*>(&*pos_ins.first);
  }
} // namespace <unnamed>

namespace registry
{
  void insert(to_python_function_t f, type_info source_t)
  {
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      std::cout << "inserting to_python " << source_t << "\n";
#  endif 
      to_python_function_t& slot = get(source_t)->m_to_python;
      
      assert(slot == 0); // we have a problem otherwise
      if (slot != 0)
      {
          std::string msg(
              "to-Python converter for "
              + lexical_cast<std::string>(source_t)
              + " already registered; second conversion method ignored."
          );
          
          if ( ::PyErr_Warn( NULL, const_cast<char*>(msg.c_str()) ) )
          {
              throw_error_already_set();
          }
      }
      slot = f;
  }

  // Insert an lvalue from_python converter
  void insert(convertible_function convert, type_info key)
  {
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      std::cout << "inserting lvalue from_python " << key << "\n";
#  endif 
      entry* found = get(key);
      lvalue_from_python_chain *registration = new lvalue_from_python_chain;
      registration->convert = convert;
      registration->next = found->lvalue_chain;
      found->lvalue_chain = registration;
      
      insert(convert, 0, key);
  }

  // Insert an rvalue from_python converter
  void insert(void* (*convertible)(PyObject*)
              , constructor_function construct
              , type_info key)
  {
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      std::cout << "inserting rvalue from_python " << key << "\n";
#  endif 
      entry* found = get(key);
      rvalue_from_python_chain *registration = new rvalue_from_python_chain;
      registration->convertible = convertible;
      registration->construct = construct;
      registration->next = found->rvalue_chain;
      found->rvalue_chain = registration;
  }

  // Insert an rvalue from_python converter
  void push_back(void* (*convertible)(PyObject*)
              , constructor_function construct
              , type_info key)
  {
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      std::cout << "push_back rvalue from_python " << key << "\n";
#  endif 
      rvalue_from_python_chain** found = &get(key)->rvalue_chain;
      while (*found != 0)
          found = &(*found)->next;
      
      rvalue_from_python_chain *registration = new rvalue_from_python_chain;
      registration->convertible = convertible;
      registration->construct = construct;
      registration->next = 0;
      *found = registration;
  }

  registration const& lookup(type_info key)
  {
      return *get(key);
  }

  registration const* query(type_info type)
  {
      registry_t::iterator p = entries().find(entry(type));
#  ifdef BOOST_PYTHON_TRACE_REGISTRY
      std::cout << "querying " << type
                << (p == entries().end() || p->target_type != type
                    ? "...NOT found\n" : "...found\n");
#  endif 
      return (p == entries().end() || p->target_type != type) ? 0 : &*p;
  }
} // namespace registry



namespace detail
{
    namespace strip_type_info{
        struct type_info_map : std::map<boost::python::type_info, boost::python::type_info> 
        {
            type_info_map(){
                (*this)[boost::python::type_id<bool*>()] = boost::python::type_id<bool>(); 
                (*this)[boost::python::type_id<bool const*>()] = boost::python::type_id<bool>(); 

                (*this)[boost::python::type_id<char*>()] = boost::python::type_id<char>(); 
                (*this)[boost::python::type_id<unsigned char*>()] = boost::python::type_id<unsigned char>(); 

                (*this)[boost::python::type_id<short*>()] = boost::python::type_id<short>(); 
                (*this)[boost::python::type_id<short const*>()] = boost::python::type_id<short>(); 
                (*this)[boost::python::type_id<unsigned short*>()] = boost::python::type_id<unsigned short>(); 
                (*this)[boost::python::type_id<unsigned short const*>()] = boost::python::type_id<unsigned short>(); 

                (*this)[boost::python::type_id<int*>()] = boost::python::type_id<int>(); 
                (*this)[boost::python::type_id<int const*>()] = boost::python::type_id<int>(); 
                (*this)[boost::python::type_id<unsigned int*>()] = boost::python::type_id<unsigned int>(); 
                (*this)[boost::python::type_id<unsigned int const*>()] = boost::python::type_id<unsigned int>(); 

                (*this)[boost::python::type_id<long*>()] = boost::python::type_id<long>(); 
                (*this)[boost::python::type_id<long const*>()] = boost::python::type_id<long>(); 
                (*this)[boost::python::type_id<unsigned long*>()] = boost::python::type_id<unsigned long>(); 
                (*this)[boost::python::type_id<unsigned long const*>()] = boost::python::type_id<unsigned long>(); 

                (*this)[boost::python::type_id<long double*>()] = boost::python::type_id<long double>(); 
                (*this)[boost::python::type_id<long double const*>()] = boost::python::type_id<long double>(); 

                (*this)[boost::python::type_id<double*>()] = boost::python::type_id<double>(); 
                (*this)[boost::python::type_id<double const*>()] = boost::python::type_id<double>(); 

                (*this)[boost::python::type_id<float*>()] = boost::python::type_id<float>(); 
                (*this)[boost::python::type_id<float const*>()] = boost::python::type_id<float>(); 

                (*this)[boost::python::type_id<std::string*>()] = boost::python::type_id<std::string>(); 
                (*this)[boost::python::type_id<std::string const*>()] = boost::python::type_id<std::string>(); 

# ifndef BOOST_NO_STD_WSTRING
                (*this)[boost::python::type_id<std::wstring*>()] = boost::python::type_id<std::wstring>(); 
                (*this)[boost::python::type_id<std::wstring const*>()] = boost::python::type_id<std::wstring>(); 
# endif
            }
        };

        static std::map<boost::python::type_info, boost::python::type_info> &type_info_remap_registry()
        {
            static type_info_map res;
            return res;
        }
        BOOST_PYTHON_DECL void insert(boost::python::type_info t, boost::python::type_info pt)
        {
            if(t==pt)
                return;
            type_info_remap_registry()[pt] = t;
        }

        BOOST_PYTHON_DECL type_info query(boost::python::type_info pt)
        {
            std::map<boost::python::type_info, boost::python::type_info> :: iterator i
                = type_info_remap_registry().find(pt);
            return i == type_info_remap_registry().end()? pt : (*i).second;
        }
    }
}


}}} // namespace boost::python::converter
