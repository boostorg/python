// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ENUM_DWA200298_HPP
# define ENUM_DWA200298_HPP

# include <boost/python/object/enum_base.hpp>
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/python/converter/registered.hpp>

namespace boost { namespace python { 

template <class T>
struct enum_ : public objects::enum_base
{
    typedef objects::enum_base base;

    enum_(char const* name);
    inline enum_<T>& value(char const* name, T);

 private:
    static PyObject* to_python(void const* x);
    static void* convertible(PyObject* obj);
    static void construct(PyObject* obj, converter::rvalue_from_python_stage1_data* data);
};

template <class T>
inline enum_<T>::enum_(char const* name)
    : base(
        name
        , &enum_<T>::to_python
        , &enum_<T>::convertible
        , &enum_<T>::construct
        , type_id<T>())
{
}

// This is the conversion function that gets registered for converting 
template <class T>
PyObject* enum_<T>::to_python(void const* x)
{
    return base::to_python(
        converter::registered<T>::converters.class_object
        , static_cast<long>(*(T const*)x));
}

template <class T>
void* enum_<T>::convertible(PyObject* obj)
{
    return PyObject_IsInstance(
        obj
        , upcast<PyObject>(
            converter::registered<T>::converters.class_object))
        
        ? obj : 0;
}
      
template <class T>
void enum_<T>::construct(PyObject* obj, converter::rvalue_from_python_stage1_data* data)
{
    T x = static_cast<T>(PyInt_AS_LONG(obj));
    void* const storage = ((converter::rvalue_from_python_storage<T>*)data)->storage.bytes;
    new (storage) T(x);
    data->convertible = storage;
}

template <class T>
inline enum_<T>& enum_<T>::value(char const* name, T x)
{
    this->add_value(name, static_cast<long>(x));
    return *this;
}

}} // namespace boost::python

#endif // ENUM_DWA200298_HPP
