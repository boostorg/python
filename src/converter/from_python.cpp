// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/find_from_python.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/converter/rvalue_from_python_data.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <vector>
#include <algorithm>

namespace boost { namespace python { namespace converter { 

BOOST_PYTHON_DECL rvalue_from_python_stage1_data rvalue_from_python_stage1(
    PyObject* source
    , from_python_registration const& converters)
{
    rvalue_from_python_chain const* chain = converters.rvalue_chain;
    
    rvalue_from_python_stage1_data data;
    data.convertible = 0;
    for (;chain != 0; chain = chain->next)
    {
        void* r = chain->convertible(source);
        if (r != 0)
        {
            data.convertible = r;
            data.construct = chain->construct;
            break;
        }
    }
    return data;
}

BOOST_PYTHON_DECL void* get_lvalue_from_python(
    PyObject* source
    , from_python_registration const& converters)
{
    lvalue_from_python_chain const* chain = converters.lvalue_chain;
    
    for (;chain != 0; chain = chain->next)
    {
        void* r = chain->convert(source);
        if (r != 0)
            return r;
    }
    return 0;
}

namespace
{
  // Prevent looping in implicit conversions. This could/should be
  // much more efficient, but will work for now.
  typedef std::vector<rvalue_from_python_chain const*> visited_t;
  static visited_t visited;

  inline bool visit(rvalue_from_python_chain const* chain)
  {
      visited_t::iterator const p = std::lower_bound(visited.begin(), visited.end(), chain);
      if (p != visited.end() && *p == chain)
          return false;
      visited.insert(p, chain);
      return true;
  }

  void unvisit(rvalue_from_python_chain const* chain)
  {
      visited_t::iterator const p = std::lower_bound(visited.begin(), visited.end(), chain);
      assert(p != visited.end());
      visited.erase(p);
  }
}

BOOST_PYTHON_DECL rvalue_from_python_chain const* implicit_conversion_chain(
    PyObject* source
    , from_python_registration const& converters)
{    
    rvalue_from_python_chain const* chain = converters.rvalue_chain;
    
    if (!visit(chain))
        return 0;
    
    try
    {
        for (;chain != 0; chain = chain->next)
        {
            if (chain->convertible(source))
                break;
        }
    }
    catch(...)
    {
        unvisit(chain);
        throw;
    }
    unvisit(chain);
    return chain;
}

}}} // namespace boost::python::converter
