// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLER_DWA20011214_HPP
# define CALLER_DWA20011214_HPP

# include <boost/python/call.hpp>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace detail { 

struct caller
{
    typedef PyObject* result_type;
    
    template <class F>
    PyObject* operator()(F f, PyObject* args, PyObject* keywords)
    {
        return call(f, args, keywords);
    }
};

}}} // namespace boost::python::detail

#endif // CALLER_DWA20011214_HPP
