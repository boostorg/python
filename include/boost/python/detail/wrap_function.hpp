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
# include <boost/mpl/select_type.hpp>

namespace boost { namespace python { namespace detail { 

// A function which converts its argument into a Python callable
// object. Not very general yet!

// This should eventually be replaced with a mechanism for specialized
// wrap/unwrap objects. In other words, to_python(f), where f is a
// function pointer or function type, should produce a callable Python
// object.

template <bool needs_wrapping>
struct wrap_function_select
{
    template <class F>
    static objects::function* execute(F f)
    {
        return make_function(f);
    }
};

template<>
struct wrap_function_select<false>
{
    template <class F>
    static F execute(F f)
    {
        return f;
    }
};

template <class F>
PyObject* wrap_function(F f)
{
    return wrap_function_select<
# if 1
        type_traits::ice_not<
                is_pointer<F>::value
# else 
              type_traits::ice_or<
                 is_function<F>::value
                 , is_member_function_pointer<F>::value
# endif 
        >::value >::execute(f);
}

}}} // namespace boost::python::detail

#endif // WRAP_FUNCTION_DWA2002118_HPP
