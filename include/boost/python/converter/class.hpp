// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA20011215_HPP
# define CLASS_DWA20011215_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/converter/from_python.hpp>

namespace boost { namespace python { namespace converter { 

template <class T>
struct class_from_python_converter
{
    class_from_python_converter();
    
    static void* convertible(PyObject*);
    static T& convert_ref(PyObject*, from_python_data&);
    static T const& convert_cref(PyObject*, from_python_data&);
    static T* convert_ptr(PyObject*, from_python_data&);
    static T const* convert_cptr(PyObject*, from_python_data&);

    from_python_converter<T&> to_ref;
    from_python_converter<T const&> to_cref;
    from_python_converter<T*> to_ptr;
    from_python_converter<T const*> to_cptr;
};

//
// implementations
//
template <class T>
class_from_python_converter<T>::class_from_python_converter()
    : to_ref(convertible, convert_ref)
      , to_cref(convertible, convert_cref)
      , to_ptr(convertible, convert_ptr)
      , to_cptr(convertible, convert_cptr)
{}

template <class T>
T& class_from_python_converter<T>::convert_ref(PyObject*, from_python_data& x)
{
    return *static_cast<T*>(x.stage1);
}

template <class T>
T const& class_from_python_converter<T>::convert_cref(PyObject*, from_python_data& x)
{
    return *static_cast<T*>(x.stage1);
}
    

template <class T>
T* class_from_python_converter<T>::convert_ptr(PyObject*, from_python_data& x)
{
    return static_cast<T*>(x.stage1);
}

template <class T>
T const* class_from_python_converter<T>::convert_cptr(PyObject*, from_python_data& x)
{
    return static_cast<T*>(x.stage1);
}

template <class T>
void* class_from_python_converter<T>::convertible(PyObject* p)
{
    return objects::find_instance<T>(p);
}

}}} // namespace boost::python::converter

#endif // CLASS_DWA20011215_HPP
