// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CONVERTIBLE_DWA2002614_HPP
# define CONVERTIBLE_DWA2002614_HPP

// Supplies a runtime is_convertible check which can be used with tag
// dispatching to work around the Metrowerks Pro7 limitation with boost::is_convertible
namespace boost { namespace python { namespace detail { 

typedef char* yes_convertible;
typedef int* no_convertible;

template <class Target>
struct convertible
{
    static inline yes_convertible check(Target) { return 0; }
    static inline no_convertible check(...) { return 0; }
};

}}} // namespace boost::python::detail

#endif // CONVERTIBLE_DWA2002614_HPP
