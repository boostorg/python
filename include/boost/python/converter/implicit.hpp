// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef IMPLICIT_DWA2002326_HPP
# define IMPLICIT_DWA2002326_HPP
# include <boost/python/converter/from_python_data.hpp>
# include <boost/python/converter/from_python_stage1_data.hpp>
# include <boost/python/converter/registrations.hpp>

namespace boost { namespace python { namespace converter { 

template <class Source, class Target>
struct implicit
{
    static void* convertible(PyObject* obj)
    {
        // Find a converter registration which can produce a Source
        // instance from obj
        return const_cast<rvalue_from_python_registration*>(
            find_chain(obj, rvalue_from_python_chain<Source>::value));
    }
      
    static void construct(PyObject* obj, rvalue_stage1_data* data)
    {
        // This is the registration we got from the convertible step
        rvalue_from_python_registration const* registration
            = static_cast<rvalue_from_python_registration*>(data->convertible);

        // Call the convertible function again
        rvalue_data<Source> intermediate_data(registration->convertible(obj));
          
        // Use the result to construct the source type if the first
        // converter was an rvalue converter.
        if (registration->construct != 0)
            registration->construct(obj, &intermediate_data.stage1);
          
        void* storage = ((rvalue_base_data<Target>*)data)->storage.bytes;
        new (storage) Target(*static_cast<Source*>(intermediate_data.stage1.convertible));

        // record successful construction
        data->convertible = storage;
          
    }
};

}}} // namespace boost::python::converter

#endif // IMPLICIT_DWA2002326_HPP
