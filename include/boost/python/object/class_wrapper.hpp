// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_WRAPPER_DWA20011221_HPP
# define CLASS_WRAPPER_DWA20011221_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/object/value_holder.hpp>
# include <boost/python/reference.hpp>
# include <boost/python/converter/to_python.hpp>
# include <memory>

namespace boost { namespace python { namespace objects { 

template <class T>
struct class_wrapper
    : converter::to_python_converter<T const&>
{
    class_wrapper(ref const& type_)
        : converter::to_python_converter<T const&>(convert)
        , m_class_object_keeper(type_)
    {
        assert(type_->ob_type == (PyTypeObject*)class_metatype().get());
        m_class_object = (PyTypeObject*)type_.get();
    }
    
    static PyObject* convert(T const& x)
    {
        // Don't call the type to do the construction, since that
        // would require the registration of an __init__ copy
        // constructor. Instead, just construct the object in place.
        PyObject* raw_result = (PyObject*)PyObject_New(
            instance, m_class_object);
        
        if (raw_result == 0)
            return 0;

        // Everything's OK; Bypass NULL checks but guard against
        // exceptions.
        ref result(raw_result, ref::allow_null());

        // Build a value_holder to contain the object using the copy
        // constructor
        value_holder<T>* p = new value_holder<T>(raw_result, cref(x));

        // Install it in the instance
        p->install(raw_result);

        // Return the new result
        return result.release();
    }
    
 private:
    ref m_class_object_keeper;
    static PyTypeObject* m_class_object;
};

template <class T>
PyTypeObject* class_wrapper<T>::m_class_object;

}}} // namespace boost::python::objects

#endif // CLASS_WRAPPER_DWA20011221_HPP
