// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef OBJ_MGR_ARG_FROM_PYTHON_DWA2002628_HPP
# define OBJ_MGR_ARG_FROM_PYTHON_DWA2002628_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/referent_storage.hpp>
# include <boost/python/detail/destroy.hpp>
# include <boost/python/detail/construct.hpp>
# include <boost/python/converter/object_manager.hpp>

//
// arg_from_python converters for Python type wrappers, to be used as
// base classes for specializations.
//
namespace boost { namespace python { namespace converter { 

template <class T>
struct object_manager_value_arg_from_python
{
    typedef T result_type;
    
    object_manager_value_arg_from_python(PyObject*);
    bool convertible() const;
    T operator()(PyObject*) const;
 private:
    PyObject* m_source;
};

template <class Ref>
struct object_manager_ref_arg_from_python
{
    typedef Ref result_type;
    
    object_manager_ref_arg_from_python(PyObject*);
    bool convertible() const;
    Ref operator()(PyObject*) const;
    ~object_manager_ref_arg_from_python();
 private:
    typename python::detail::referent_storage<Ref>::type m_result;
};

//
// implementations
//

template <class T>
inline object_manager_value_arg_from_python<T>::object_manager_value_arg_from_python(PyObject* x)
    : m_source(x)
{
}
    
template <class T>
inline bool object_manager_value_arg_from_python<T>::convertible() const
{
    return extract_object_manager<T>::check(m_source);
}

template <class T>
inline T object_manager_value_arg_from_python<T>::operator()(PyObject* x) const
{
    return T(python::detail::borrowed_reference(x));
}

template <class Ref>
inline object_manager_ref_arg_from_python<Ref>::object_manager_ref_arg_from_python(PyObject* x)
{
    python::detail::construct_referent<Ref>(&m_result.bytes, python::detail::borrowed_reference(x));
}

template <class Ref>
inline object_manager_ref_arg_from_python<Ref>::~object_manager_ref_arg_from_python()
{
    python::detail::destroy_referent<Ref>(this->m_result.bytes);
}

namespace detail
{
  template <class T>
  inline bool object_manager_ref_check(T const& x)
  {
      return extract_object_manager<T>::check((get_managed_object)(x));
  }
}

template <class Ref>
inline bool object_manager_ref_arg_from_python<Ref>::convertible() const
{
    return detail::object_manager_ref_check(
        python::detail::void_ptr_to_reference(this->m_result.bytes, (Ref(*)())0));
}

template <class Ref>
inline Ref object_manager_ref_arg_from_python<Ref>::operator()(PyObject*) const
{
    return python::detail::void_ptr_to_reference(
        this->m_result.bytes, (Ref(*)())0);
}

}}} // namespace boost::python::converter

#endif // OBJ_MGR_ARG_FROM_PYTHON_DWA2002628_HPP
