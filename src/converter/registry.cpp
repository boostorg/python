//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

# include <boost/python/converter/to_python.hpp>
# include <boost/python/converter/from_python.hpp>
# include <boost/python/converter/builtin_converters.hpp>
# include <boost/detail/binary_search.hpp>
# include <map>
# include <algorithm>
# include <stdexcept>
# ifdef BOOST_PYTHON_TRACE
#  include <iostream>
# endif 

namespace boost { namespace python { namespace converter { 

namespace // <unnamed>
{
  typedef std::map<type_id_t, registry::entry> registry_t;
  
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
} // namespace <unnamed>

namespace registry
{
  entry* find(type_id_t type)
  {
      return &entries()[type];
  }

  entry::entry()
      : m_to_python_converter(0)
  {
  }

  entry::~entry()
  {
      if (m_to_python_converter != 0)
          m_to_python_converter->m_can_unregister = false;
      
      for (from_python_converters::iterator p = m_from_python_converters.begin()
               ; p != m_from_python_converters.end()
               ; ++p)
      {
          (*p)->m_can_unregister = false;
      }
  }

  from_python_converter_base const*
  entry::get_from_python(PyObject* p, void*& data_out) const
  {      
      for (from_python_converters::const_iterator q = m_from_python_converters.begin(),
               finish = m_from_python_converters.end();
           q != finish;
           ++q)
      {
          void* const data = (*q)->convertible(p);
          if (data != 0)
          {
              data_out = data;
              return *q;
              break;
          }
      }
      return 0;
  }
  
  to_python_function_base entry::get_to_python() const
  {
      return m_to_python_converter
          ? m_to_python_converter->converter()
          : 0;
  }

  entry::from_python_converters::iterator entry::find(from_python_converter_base const& x)
  {
      return std::find(m_from_python_converters.begin(), m_from_python_converters.end(), &x);
  }

  void entry::insert(from_python_converter_base& x)
  {
      from_python_converters::iterator p = this->find(x);
      
      if (p != m_from_python_converters.end())
      {
          assert(!"converter already registered");
          throw std::runtime_error(
              "trying to register unrapper which is already registered");
      }

      m_from_python_converters.push_back(&x);
  }
  
  void entry::remove(from_python_converter_base& x)
  {
      from_python_converters::iterator p = find(x);

      // Be sure we're not removing a converter which hasn't been
      // registered.
      if (p == m_from_python_converters.end())
      {
          assert(!"trying to unregister from_python_converter which is not registered");
          throw std::runtime_error(
              "trying to unregister from_python_converter which is not registered");
      }
      m_from_python_converters.erase(p);
  }
  
  void entry::insert(to_python_converter_base& x)
  {
      assert(m_to_python_converter == 0); // we have a problem otherwise
      if (m_to_python_converter != 0)
      {
          throw std::runtime_error(
              "trying to register to_python_converter for a type which already has a registered to_python_converter");
      }
      m_to_python_converter = &x;
  }
  
  void entry::remove(to_python_converter_base& x)
  {
      assert(m_to_python_converter == &x);
      if (m_to_python_converter != &x)
      {
          throw std::runtime_error(
              "trying to unregister a to_python_converter which is not registered");
      }
      m_to_python_converter = 0;
  }

  void insert(to_python_converter_base& w)
  {
# ifdef BOOST_PYTHON_TRACE
      std::cout << "inserting to_python_converter for " << w.key() << std::endl;
# endif 
      find(w.key())->insert(w);
  }

  void insert(from_python_converter_base& u)
  {
# ifdef BOOST_PYTHON_TRACE
      std::cout << "inserting from_python_converter for " << u.key() << std::endl;
# endif 
      find(u.key())->insert(u);
  }

  void remove(to_python_converter_base& w)
  {
      find(w.key())->remove(w);
  }

  void remove(from_python_converter_base& u)
  {
      find(u.key())->remove(u);
  }
} // namespace registry

}}} // namespace boost::python::converter
