// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FUNCTION_HANDLE_DWA2002725_HPP
# define FUNCTION_HANDLE_DWA2002725_HPP
# include <boost/python/handle.hpp>
# include <boost/python/detail/caller.hpp>
# include <boost/python/detail/arg_tuple_size.hpp>
# include <boost/python/default_call_policies.hpp>
# include <boost/python/object/py_function.hpp>
# include <boost/bind.hpp>

namespace boost { namespace python { namespace objects { 

BOOST_PYTHON_DECL handle<> function_handle_impl(py_function const& f, unsigned min_args, unsigned max_args = 0);

// Just like function_object, but returns a handle<> instead. Using
// this for arg_to_python<> allows us to break a circular dependency
// between object and arg_to_python.
template <class F>
inline handle<> function_handle(F const& f, unsigned min_args, unsigned max_args = 0)
{
    return objects::function_handle_impl(objects::py_function(f), min_args, max_args);
}

// Just like make_function, but returns a handle<> intead. Same
// reasoning as above.
template <class F>
handle<> make_function_handle(F f)
{
    return objects::function_handle(
        ::boost::bind<PyObject*>(python::detail::caller(), f, _1, _2, default_call_policies())
        , python::detail::arg_tuple_size<F>::value);
}

}}} // namespace boost::python::objects

#endif // FUNCTION_HANDLE_DWA2002725_HPP
