//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

# include <boost/python/converter/unwrapper.hpp>
# include <boost/python/converter/wrapper.hpp>
# include <map>
# include <list>
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
      : m_wrapper(0)
  {
  }

  entry::~entry()
  {
      if (m_wrapper != 0)
          m_wrapper->m_can_unregister = false;
      
      for (unwrappers::iterator p = m_unwrappers.begin(); p != m_unwrappers.end(); ++p)
      {
          (*p)->m_can_unregister = false;
      }
  }

  std::pair<unwrapper_base*,void*>
  entry::unwrapper(PyObject* p) const
  {
      unwrapper_base* body = 0;
      void* data = 0;
      
      for (unwrappers::const_iterator q = m_unwrappers.begin(),
               finish = m_unwrappers.end();
           q != finish;
           ++q)
      {
          data = (*q)->can_convert(p);
          if (data != 0)
          {
              body = *q;
              break;
          }
      }
      return std::make_pair(body,data);
  }
  
  wrapper_base* entry::wrapper() const
  {
      return m_wrapper;
  }

  entry::unwrappers::iterator entry::find(unwrapper_base const& x)
  {
      return std::find(m_unwrappers.begin(), m_unwrappers.end(), &x);
  }

  void entry::insert(unwrapper_base& x)
  {
      unwrappers::iterator p = this->find(x);
      
      assert(p == m_unwrappers.end());
      if (p != m_unwrappers.end())
      {
          throw std::runtime_error(
              "trying to register unrapper which is already registered");
      }
      m_unwrappers.push_back(&x);
  }
  
  void entry::remove(unwrapper_base& x)
  {
      unwrappers::iterator p = find(x);

      // Be sure we're not removing a converter which hasn't been
      // registered.
      assert(p != m_unwrappers.end());
      if (p == m_unwrappers.end())
      {
          throw std::runtime_error(
              "trying to unregister unwrapper which is not registered");
      }
      m_unwrappers.erase(p);
  }
  
  void entry::insert(wrapper_base& x)
  {
      assert(m_wrapper == 0); // we have a problem otherwise
      if (m_wrapper != 0)
      {
          throw std::runtime_error(
              "trying to register wrapper for a type which already has a registered wrapper");
      }
      m_wrapper = &x;
  }
  
  void entry::remove(wrapper_base& x)
  {
      assert(m_wrapper == &x);
      if (m_wrapper != &x)
      {
          throw std::runtime_error(
              "trying to unregister a wrapper which is not registered");
      }
      m_wrapper = 0;
  }

  void insert(wrapper_base& w)
  {
# ifdef BOOST_PYTHON_TRACE
      std::cout << "inserting wrapper for " << w.key() << std::endl;
# endif 
      find(w.key())->insert(w);
  }

  void insert(unwrapper_base& u)
  {
# ifdef BOOST_PYTHON_TRACE
      std::cout << "inserting unwrapper for " << u.key() << std::endl;
# endif 
      find(u.key())->insert(u);
  }

  void remove(wrapper_base& w)
  {
      find(w.key())->remove(w);
  }

  void remove(unwrapper_base& u)
  {
      find(u.key())->remove(u);
  }
} // namespace registry

}}} // namespace boost::python::converter
