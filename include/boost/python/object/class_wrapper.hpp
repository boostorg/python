// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_WRAPPER_DWA20011221_HPP
# define CLASS_WRAPPER_DWA20011221_HPP

# include <boost/python/handle.hpp>
# include <boost/python/to_python_converter.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/ref.hpp>

namespace boost { namespace python { namespace objects { 

template <class Src, class Holder>
struct copy_construct_instance
{
    static Holder* execute(PyObject* instance, Src const& x)
    {
        return new Holder(instance, cref(x));
    }
};

// Used to convert objects of type Src to wrapped C++ classes by
// building a new instance object and installing a Holder constructed
// from the Src object.
template <class Src, class Holder, class MakeHolder = copy_construct_instance<Src,Holder> >
struct class_wrapper
    : to_python_converter<Src,class_wrapper<Src,Holder,MakeHolder> >
{
    static PyObject* convert(Src const& x)
    {
        // Get the class object associated with the wrapped type
        typedef typename Holder::value_type value_type;
        PyTypeObject* class_object = converter::registered<value_type>::converters.class_object;
        
        // Don't call the type directly to do the construction, since
        // that would require the registration of an appropriate
        // __init__ function.
        PyObject* raw_result = class_object->tp_alloc(class_object, 0);

        if (raw_result == 0)
            return 0;

        // Everything's OK; Bypass NULL checks but guard against
        // exceptions.
        handle<> result(python::allow_null(raw_result));

        // Build a value_holder to contain the object using the copy
        // constructor
        Holder* p = MakeHolder::execute(raw_result, x);

        // Install it in the instance
        p->install(raw_result);

        // Return the new result
        return result.release();
    }
};

}}} // namespace boost::python::objects

#endif // CLASS_WRAPPER_DWA20011221_HPP
