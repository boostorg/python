// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLER_DWA20011214_HPP
# define CALLER_DWA20011214_HPP

# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/detail/returning.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/same_traits.hpp>

namespace boost { namespace python
{
  template <class T> struct to_python;
}}

namespace boost { namespace python { namespace detail {

struct caller
{
    typedef PyObject* result_type;
    
    template <class P, class R>
    PyObject* operator()(R (*f)(), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0>
    PyObject* operator()(R (*f)(A0), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1>
    PyObject* operator()(R (*f)(A0, A1), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2>
    PyObject* operator()(R (*f)(A0, A1, A2), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3>
    PyObject* operator()(R (*f)(A0, A1, A2, A3), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4>
    PyObject* operator()(R (*f)(A0, A1, A2, A3, A4), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    PyObject* operator()(R (*f)(A0, A1, A2, A3, A4, A5), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

// Member functions
    template <class P, class R, class A0>
    PyObject* operator()(R (A0::*f)(), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1>
    PyObject* operator()(R (A0::*f)(A1), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2>
    PyObject* operator()(R (A0::*f)(A1, A2), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3>
    PyObject* operator()(R (A0::*f)(A1, A2, A3), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4, A5), PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0>
    PyObject* operator()(R (A0::*f)() const, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1>
    PyObject* operator()(R (A0::*f)(A1) const, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2>
    PyObject* operator()(R (A0::*f)(A1, A2) const, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3>
    PyObject* operator()(R (A0::*f)(A1, A2, A3) const, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4) const, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0>
    PyObject* operator()(R (A0::*f)() volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1>
    PyObject* operator()(R (A0::*f)(A1) volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2>
    PyObject* operator()(R (A0::*f)(A1, A2) volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3>
    PyObject* operator()(R (A0::*f)(A1, A2, A3) volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4) volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4, A5) volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0>
    PyObject* operator()(R (A0::*f)() const volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1>
    PyObject* operator()(R (A0::*f)(A1) const volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2>
    PyObject* operator()(R (A0::*f)(A1, A2) const volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3>
    PyObject* operator()(R (A0::*f)(A1, A2, A3) const volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4) const volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }

    template <class P, class R, class A0, class A1, class A2, class A3, class A4, class A5>
    PyObject* operator()(R (A0::*f)(A1, A2, A3, A4, A5) const volatile, PyObject* args, PyObject* keywords, P const& policies) const
    {
        return returning<R>::call(f, args, keywords, policies);
    }
};

}}} // namespace boost::python::detail

#endif // CALLER_DWA20011214_HPP
