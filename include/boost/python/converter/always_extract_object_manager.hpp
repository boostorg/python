// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ALWAYS_EXTRACT_OBJECT_MANAGER_DWA2002716_HPP
# define ALWAYS_EXTRACT_OBJECT_MANAGER_DWA2002716_HPP

# include <boost/config.hpp>

namespace boost { namespace python { namespace converter { 

// Derive specializations of extract_object_manager from this when the
// object manager is indiscriminate about the Python objects it manages
struct always_extract_object_manager
{
    BOOST_STATIC_CONSTANT(bool, is_specialized = true);
    static inline bool check(PyObject* x);
};

// Provide a forward declaration as a convenience for clients, who all
// need it.
template <class T> struct extract_object_manager;

//
// implementations
//
inline bool always_extract_object_manager::check(PyObject* x)
{
    return true;
}

}}} // namespace boost::python::converter

#endif // ALWAYS_EXTRACT_OBJECT_MANAGER_DWA2002716_HPP
