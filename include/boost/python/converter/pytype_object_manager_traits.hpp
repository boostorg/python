// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef PYTYPE_OBJECT_MANAGER_TRAITS_DWA2002716_HPP
# define PYTYPE_OBJECT_MANAGER_TRAITS_DWA2002716_HPP

# include <boost/python/converter/pytype_result_from_python.hpp>
# include <boost/python/detail/raw_pyobject.hpp>
# include <boost/python/cast.hpp>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

// Provide a forward declaration as a convenience for clients, who all
// need it.
template <class T> struct object_manager_traits;

// Derive specializations of object_manager_traits from this class
// when T is an object manager for a particular Python type hierarchy.
//
template <PyTypeObject* pytype, class T>
struct pytype_object_manager_traits
{
    BOOST_STATIC_CONSTANT(bool, is_specialized = true);
    static inline python::detail::new_reference adopt(PyObject*);
    static inline bool check(PyObject* x);
};

//
// implementations
//
template <PyTypeObject* pytype, class T>
inline python::detail::new_reference pytype_object_manager_traits<pytype,T>::adopt(PyObject* x)
{
    return pytype_result_from_python(pytype, x);
}

template <PyTypeObject* pytype, class T>
inline bool pytype_object_manager_traits<pytype,T>::check(PyObject* x)
{
    return ::PyObject_IsInstance(x, python::upcast<PyObject>(pytype));
}

}}} // namespace boost::python::converter

#endif // PYTYPE_OBJECT_MANAGER_TRAITS_DWA2002716_HPP
