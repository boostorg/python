// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef WRAP_FUNCTION_DWA2002118_HPP
# define WRAP_FUNCTION_DWA2002118_HPP

# include <boost/python/make_function.hpp>
# include <boost/type_traits/ice.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/refcount.hpp>

namespace boost { namespace python {

template <class T> class reference;

namespace detail { 

// A function which converts its argument into a Python callable
// object. Not very general yet!

// This should eventually be replaced with a mechanism for specialized
// wrap/unwrap objects. In other words, to_python(f), where f is a
// function pointer or function type, should produce a callable Python
// object.

template <class F>
inline PyObject* wrap_function_aux(F const& f, PyObject*) { return f; }

template <class F, class T>
inline PyObject* wrap_function_aux(F const&, boost::python::handle<T> x) { return x.release(); }

template <class F>
inline PyObject* wrap_function_aux(F const&, object const& x) { return python::incref(x.ptr()); }

template <class F>
inline PyObject* wrap_function_aux(F const& f, ...) { return make_function(f); }

template <class F>
PyObject* wrap_function(F f)
{
    return wrap_function_aux(f, f);
}

}}} // namespace boost::python::detail

#endif // WRAP_FUNCTION_DWA2002118_HPP
