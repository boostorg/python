// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MSVC_TYPEINFO_DWA200222_HPP
# define MSVC_TYPEINFO_DWA200222_HPP

#include <boost/type.hpp>
#include <typeinfo>

//
// Fix for MSVC's broken typeid() implementation which doesn't strip
// decoration. This fix doesn't handle cv-qualified array types. It
// could probably be done, but I haven't figured it out yet.
//

# if defined(BOOST_MSVC) && BOOST_MSVC <= 1300 || defined(BOOST_INTEL_CXX_VERSION) && BOOST_INTEL_CXX_VERSION <= 600

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
    BOOST_STATIC_CONSTANT(bool, c = is_const<T>::value);
    BOOST_STATIC_CONSTANT(bool, v = is_volatile<T>::value);
    return value_id_accessor<(2 * v + c)>::get((T*)0);
}

template <class T>
inline typeinfo typeid_ref(boost::type<T>*, ...) 
{
    return typeid_nonref<T>();
}

template <class U, class T>
inline typeinfo typeid_ref(boost::type<U>*, T& (*)()) 
{
    return typeid_nonref<T>();
}

template <class T>
inline typeinfo typeid_array(bool_t<false>, boost::type<T>* = 0)
{
    typedef T (*x)();
    return typeid_ref((boost::type<T>*)0, x(0));
}

template <class T>
inline typeinfo typeid_array(bool_t<true>, boost::type<T>* = 0)
{
    return typeid_nonref<T>();
}

template <class T>
inline typeinfo msvc_typeid(boost::type<T>* = 0)
{
    typedef bool_t<is_array<T>::value> tag;
    return typeid_array(tag(), (boost::type<T>*)0);
}

}}} // namespace boost::python::detail

# endif // BOOST_MSVC
#endif // MSVC_TYPEINFO_DWA200222_HPP
