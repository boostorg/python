// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FUNCTION_OBJECT_DWA2002725_HPP
# define FUNCTION_OBJECT_DWA2002725_HPP
# include <boost/python/object/function.hpp>
# include <boost/python/object_core.hpp>

namespace boost { namespace python { namespace objects { 

template <class F>
inline object function_object(F const& f, unsigned min_args, unsigned max_args = 0)
{
    return python::object(
        python::detail::new_non_null_reference(
            new function(objects::py_function(f), min_args, max_args)));
}

}}} // namespace boost::python::object

#endif // FUNCTION_OBJECT_DWA2002725_HPP
