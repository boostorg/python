// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef PYTYPE_EXTRACT_OBJECT_MANAGER_DWA2002716_HPP
# define PYTYPE_EXTRACT_OBJECT_MANAGER_DWA2002716_HPP

# include <boost/python/converter/pytype_result_from_python.hpp>
# include <boost/python/detail/raw_pyobject.hpp>
# include <boost/python/cast.hpp>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

// Provide a forward declaration as a convenience for clients, who all
// need it.
template <class T> struct extract_object_manager;

// Derive specializations of extract_object_manager from this class
// when T is an object manager for a particular Python type hierarchy.
//
template <PyTypeObject* pytype, class T>
struct pytype_extract_object_manager
{
    BOOST_STATIC_CONSTANT(bool, is_specialized = true);
    static inline python::detail::new_reference execute(PyObject*);
    static inline bool check(PyObject* x);
};

//
// implementations
//
template <PyTypeObject* pytype, class T>
inline python::detail::new_reference pytype_extract_object_manager<pytype,T>::execute(PyObject* x)
{
    return pytype_result_from_python(pytype, x);
}

template <PyTypeObject* pytype, class T>
inline bool pytype_extract_object_manager<pytype,T>::check(PyObject* x)
{
    return ::PyObject_IsInstance(x, python::upcast<PyObject>(pytype));
}

}}} // namespace boost::python::converter

#endif // PYTYPE_EXTRACT_OBJECT_MANAGER_DWA2002716_HPP
