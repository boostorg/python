// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef IMPLICIT_DWA2002326_HPP
# define IMPLICIT_DWA2002326_HPP
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/python/converter/registrations.hpp>
# include <boost/python/converter/registered.hpp>

namespace boost { namespace python { namespace converter { 

template <class Source, class Target>
struct implicit
{
    static void* convertible(PyObject* obj)
    {
        // Find a converter chain which can produce a Source instance
        // from obj. The user has told us that Source can be converted
        // to Target, and instantiating construct() below, ensures
        // that at compile-time.
        return const_cast<rvalue_from_python_chain*>(
            converter::implicit_conversion_chain(obj, registered<Source>::converters));
    }
      
    static void construct(PyObject* obj, rvalue_from_python_stage1_data* data)
    {
        // This is the chain we got from the convertible step
        rvalue_from_python_chain const* chain
            = static_cast<rvalue_from_python_chain*>(data->convertible);

        // Call the convertible function again
        rvalue_from_python_data<Source> intermediate_data(chain->convertible(obj));
          
        // Use the result to construct the source type if the first
        // converter was an rvalue converter.
        if (chain->construct != 0)
            chain->construct(obj, &intermediate_data.stage1);
          
        void* storage = ((rvalue_from_python_storage<Target>*)data)->storage.bytes;
#   if !defined(BOOST_MSVC) || _MSC_FULL_VER != 13012108 // vc7.01 alpha workaround
        new (storage) Target(*static_cast<Source*>(intermediate_data.stage1.convertible));
#   else
        Target x(*static_cast<Source*>(intermediate_data.stage1.convertible));
        new (storage) Target(x);
#   endif 

        // record successful construction
        data->convertible = storage;
          
    }
};

}}} // namespace boost::python::converter

#endif // IMPLICIT_DWA2002326_HPP
