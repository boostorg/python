// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef VALUE_FROM_PYTHON_DWA2002130_HPP
# define VALUE_FROM_PYTHON_DWA2002130_HPP

# include <boost/python/converter/from_python.hpp>
# include <boost/type_traits/object_traits.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/static_assert.hpp>

namespace boost { namespace python { 

template <typename T, class Derived>
struct value_from_python
{
    typedef converter::from_python_check from_python_check;
    
    value_from_python(from_python_check convertible)
        : m_converter(
            convertible
            , &Derived::convert
            
            // Change this to a compile-time check later to avoid
            // generating destroy function
            , has_trivial_destructor<T>::value ? 0 : &Derived::destroy
            )
    {
    }

    value_from_python()
        : m_converter(
            &Derived::convertible
            , &Derived::convert
            
            // Change this to a compile-time check later to avoid
            // generating destroy function
            , has_trivial_destructor<T>::value ? 0 : &Derived::destroy
            )
    {
    }

    static void* get_storage(converter::from_python_data& data)
    {
        return converter::get_storage<T const&>(data);
    }

    // Mark successful construction
    static void constructed(converter::from_python_data& data)
    {
        data.stage1 = get_storage(data);
    }
    
    inline static void destroy(converter::from_python_data& data)
    {
        // Get the location of the storage for
        void* storage = get_storage(data);

        // Check for successful construction
        if (data.stage1 == storage)
            static_cast<T*>(storage)->~T();
    }

 private:
    converter::from_python_converter<T const&> m_converter;
};

}} // namespace boost::python

#endif // VALUE_FROM_PYTHON_DWA2002130_HPP
