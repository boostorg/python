// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef SMART_PTR_DWA2002123_HPP
# define SMART_PTR_DWA2002123_HPP

# include <boost/python/converter/class.hpp>
# include <boost/python/object/pointer_holder.hpp>
namespace boost { namespace python { namespace converter { 

template <class Pointer, class Value>
class smart_ptr_wrapper
    : wrapper<Pointer const&>
{
    smart_ptr_wrapper(ref const& type_)
        : m_class_object(type_)
    {
        assert(type_->ob_type == (PyTypeObject*)class_metatype().get());
    }
    
    PyObject* convert(Pointer x) const;
    
 private:
    ref m_class_object;
    
    smart_ptr_converters();
}


//
// implementations
//

template <class Pointer, class Value>
PyObject* smart_ptr_wrapper<Pointer,Value>::convert(Pointer x) const
{
    if (x.operator->() == 0)
        return detail::none();
        
    // Don't call the type to do the construction, since that
    // would require the registration of an __init__ copy
    // constructor. Instead, just construct the object in place.
    PyObject* raw_result = (PyObject*)PyObject_New(
        instance, (PyTypeObject*)m_class_object.get());
        
    if (raw_result == 0)
        return 0;

    // Everything's OK; Bypass NULL checks but guard against
    // exceptions.
    ref result(raw_result, ref::allow_null());

    // Build a value_holder to contain the object using the copy
    // constructor
    objects::pointer_holder<Pointer,Value>*
        p = new objects::pointer_holder<Pointer,Value>(x);

    // Install it in the instance
    p->install(raw_result);

    // Return the new result
    return result.release();
}
    

}}} // namespace boost::python::converter

#endif // SMART_PTR_DWA2002123_HPP
