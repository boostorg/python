// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FUNCTION_OBJECT_DWA2002725_HPP
# define FUNCTION_OBJECT_DWA2002725_HPP
# include <boost/python/detail/wrap_python.hpp>
# include <boost/function/function2.hpp>
# include <boost/python/object_core.hpp>

namespace boost { namespace python { namespace objects { 

BOOST_PYTHON_DECL api::object function_object_impl(boost::function2<PyObject*, PyObject*, PyObject*> const& f, unsigned min_args, unsigned max_args = 0);

template <class F>
inline object function_object(F const& f, unsigned min_args, unsigned max_args = 0)
{
    return objects::function_object_impl(boost::function2<PyObject*, PyObject*, PyObject*>(f), min_args, max_args);
}

}}} // namespace boost::python::objects

#endif // FUNCTION_OBJECT_DWA2002725_HPP
