// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MSVC_TYPEINFO_DWA200222_HPP
# define MSVC_TYPEINFO_DWA200222_HPP

#include <boost/type.hpp>
#include <typeinfo>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
//
// Fix for MSVC's broken typeid() implementation which doesn't strip
// decoration. This fix doesn't handle cv-qualified array types. It
// could probably be done, but I haven't figured it out yet.
//

# if defined(BOOST_MSVC) && BOOST_MSVC <= 1300 || defined(BOOST_INTEL_CXX_VERSION) && BOOST_INTEL_CXX_VERSION <= 700

namespace boost { namespace python { namespace detail { 

typedef std::type_info const& typeinfo;

template<int>struct value_id_accessor;

template<>
struct value_id_accessor<0>
{
    template <class T>
    static typeinfo get(T*) { return typeid(T); }
};

template<>
struct value_id_accessor<1>
{
    template <class T>
    static typeinfo get(T const*) { return typeid(T); }
};

template<>
struct value_id_accessor<2>
{
    template <class T>
    static typeinfo get(T volatile*) { return typeid(T); }
};

template<>
struct value_id_accessor<3>
{
    template <class T>
    static typeinfo get(T const volatile*) { return typeid(T); }
};

template <bool> struct bool_t{};

template <class T>
inline typeinfo typeid_nonref(boost::type<T>* = 0)
{
    bool const c = is_const<T>::value;
    bool const v = is_volatile<T>::value;
    return value_id_accessor<(2 * v + c)>::get((T*)0);
}

template <class T>
inline typeinfo typeid_ref(T&(*)()) 
{
    return typeid_nonref<T>();
}

template <class T>
inline typeinfo array_ref_typeid(bool_t<true>, bool_t<false>, boost::type<T>* = 0)
{
    return typeid_ref((T&(*)())0);
}

template <class T>
inline typeinfo array_ref_typeid(bool_t<false>, bool_t<true>, boost::type<T>* = 0)
{
    return typeid_ref((T(*)())0);
}

template <class T>
inline typeinfo array_ref_typeid(bool_t<false>, bool_t<false>, boost::type<T>* = 0)
{
    return typeid_ref((T&(*)())0);
}

template <class T>
inline typeinfo msvc_typeid(boost::type<T>* = 0)
{
    typedef bool_t<is_array<T>::value> array_tag;
    typedef bool_t<is_reference<T>::value> ref_tag;
    return array_ref_typeid(array_tag(), ref_tag(), (boost::type<T>*)0);
}

}}} // namespace boost::python::detail

# endif // BOOST_MSVC
#endif // MSVC_TYPEINFO_DWA200222_HPP
