//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#ifndef REGISTRY_DWA20011127_HPP
# define REGISTRY_DWA20011127_HPP
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/detail/config.hpp>
# include <list>
# include <memory>
# include <utility>

namespace boost { namespace python { namespace converter {

struct BOOST_PYTHON_DECL wrapper_base;
struct BOOST_PYTHON_DECL unwrapper_base;

// This namespace acts as a sort of singleton
namespace registry
{
  // These are the elements stored in the registry
  class BOOST_PYTHON_DECL entry
  {
   public: // member functions
      entry();
      ~entry();

      // Return a converter appropriate for converting the given
      // Python object from_python to the C++ type with which this
      // converter is associated in the registry, or 0 if no such
      // converter exists.
      std::pair<unwrapper_base*,void*> unwrapper(PyObject*) const;

      // Return a converter appropriate for converting a C++ object
      // whose type this entry is associated with in the registry to a
      // Python object, or 0 if no such converter exists.
      wrapper_base* wrapper() const;

      // Conversion classes use these functions to register
      // themselves.
      void insert(wrapper_base&);
      void remove(wrapper_base&);

      void insert(unwrapper_base&);
      void remove(unwrapper_base&);

   private: // types
      typedef std::list<unwrapper_base*> unwrappers;
      
   private: // helper functions
      unwrappers::iterator find(unwrapper_base const&);
      
   private: // data members
      
      // The collection of from_python converters for the associated
      // C++ type.
      unwrappers m_unwrappers;

      // The unique to_python converter for the associated C++ type.
      converter::wrapper_base* m_wrapper;
  };

  BOOST_PYTHON_DECL entry* find(type_id_t);
  
  BOOST_PYTHON_DECL void insert(wrapper_base& x);
  BOOST_PYTHON_DECL void insert(unwrapper_base& x);
  BOOST_PYTHON_DECL void remove(wrapper_base& x);
  BOOST_PYTHON_DECL void remove(unwrapper_base& x);
}

}}} // namespace boost::python::converter

#endif // REGISTRY_DWA20011127_HPP
