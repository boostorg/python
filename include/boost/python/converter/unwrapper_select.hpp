// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef UNWRAPPER_SELECT_DWA20011229_HPP
# define UNWRAPPER_SELECT_DWA20011229_HPP

namespace boost { namespace python { namespace converter { 

template <class T> struct unwrapper;

// Select the type returned by unwrapper objects when unwrapping a
// given type. When unwrapping T const&, the unwrapper returns T&, so
// that the same unwrapper object can be used for both conversions (on
// a conforming compiler).
template <class T>
struct unwrapper_select
{
    typedef unwrapper<T> type;
};

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct unwrapper_select<T const&>
{
    typedef unwrapper<T&> type;
};
# endif 

}}} // namespace boost::python::converter

#endif // UNWRAPPER_SELECT_DWA20011229_HPP
