// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef DESTROY_DWA2002221_HPP
# define DESTROY_DWA2002221_HPP

# include <boost/type_traits/is_array.hpp>

namespace boost { namespace python { namespace detail { 

template <bool array> struct value_destroyer;
    
template <>
struct value_destroyer<false>
{
    template <class T>
    static void execute(T const volatile* p)
    {
        p->T::~T();
    }
};

template <>
struct value_destroyer<true>
{
    template <class A, class T>
    static void execute(A*, T const volatile* const first)
    {
        for (T const volatile* p = first; p != first + sizeof(A)/sizeof(T); ++p)
        {
            value_destroyer<
                boost::is_array<T>::value
            >::execute(p);
        }
    }
    
    template <class T>
    static void execute(T const volatile* p)
    {
        execute(p, *p);
    }
};

template <class T>
inline void destroy_referent_impl(void* p, T& (*)())
{
    // note: cv-qualification needed for MSVC6
    // must come *before* T for metrowerks
    value_destroyer<
         (boost::is_array<T>::value)
    >::execute((const volatile T*)p);
}

template <class T>
inline void destroy_referent(void* p, T(*)() = 0)
{
    destroy_referent_impl(p, (T(*)())0);
}

}}} // namespace boost::python::detail

#endif // DESTROY_DWA2002221_HPP
