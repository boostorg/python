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
# include <boost/python/converter/to_python_function.hpp>
# include <vector>
# include <memory>
# include <utility>

namespace boost { namespace python { namespace converter {

struct BOOST_PYTHON_DECL from_python_converter_base;
struct BOOST_PYTHON_DECL to_python_converter_base;

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
      from_python_converter_base const* get_from_python(PyObject*, void*& data) const;

      // Return a conversion function appropriate for converting a C++
      // object whose type this entry is associated with in the
      // registry to a Python object, or 0 if no such converter
      // exists. This function must be reinterpret_cast to the
      // appropriate to_python_function type.
      to_python_function_base get_to_python() const;

      // Conversion classes use these functions to register
      // themselves.
      void insert(from_python_converter_base&);
      void remove(from_python_converter_base&);

      void insert(to_python_converter_base&);
      void remove(to_python_converter_base&);

   private: // types
      typedef std::vector<from_python_converter_base*> from_python_converters;
      
   private: // helper functions
      from_python_converters::iterator find(from_python_converter_base const&);
      
   private: // data members
      
      // The collection of from_python converters for the associated
      // C++ type.
      from_python_converters m_from_python_converters;

      // The unique to_python converter for the associated C++ type.
      to_python_converter_base* m_to_python_converter;
  };

  BOOST_PYTHON_DECL entry* find(type_id_t);
  
  BOOST_PYTHON_DECL void insert(to_python_converter_base& x);
  BOOST_PYTHON_DECL void insert(from_python_converter_base& x);
  BOOST_PYTHON_DECL void remove(to_python_converter_base& x);
  BOOST_PYTHON_DECL void remove(from_python_converter_base& x);
}

}}} // namespace boost::python::converter

#endif // REGISTRY_DWA20011127_HPP
