// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef PROXY_DWA2002615_HPP
# define PROXY_DWA2002615_HPP
# include <boost/python/object_core.hpp>
# include <boost/python/object_operators.hpp>

namespace boost { namespace python { namespace api {

template <class Policies>
class proxy
{
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1200
    typedef proxy const& copy_ctor_self;
# else
    typedef proxy copy_ctor_self;
# endif
 public:
    operator object() const;

    // to support a[b] = c[d]
    proxy const& operator=(copy_ctor_self) const;
    
    template <class T>
    inline proxy const& operator=(T const& rhs) const
    {
        Policies::set(m_target, m_key, python::object(rhs));
        return *this;
    }

    // truth value testing
    operator object::bool_type() const;
    bool operator!() const; // needed for vc6
    
 private:
    friend class object;
    proxy(object const& target, object const& key);
    
 private:
    object m_target;
    object m_key;
};

//
// implementation
//

template <class Policies>
inline proxy<Policies>::proxy(object const& target, object const& key)
    : m_target(target), m_key(key)
{}

template <class Policies>
inline proxy<Policies>::operator object() const
{
    return Policies::get(m_target, m_key);
}

// to support a[b] = c[d]
template <class Policies>
inline proxy<Policies> const& proxy<Policies>::operator=(typename proxy::copy_ctor_self rhs) const
{
    return *this = python::object(rhs);
}

# define BOOST_PYTHON_PROXY_INPLACE(op)                                         \
template <class Policies, class R>                                              \
proxy<Policies> const& operator op(proxy<Policies> const& lhs, R const& other)  \
{                                                                               \
    object old(lhs);                                                            \
    return lhs = (old op other);                                                \
} 
BOOST_PYTHON_PROXY_INPLACE(+=)
BOOST_PYTHON_PROXY_INPLACE(-=)
BOOST_PYTHON_PROXY_INPLACE(*=)
BOOST_PYTHON_PROXY_INPLACE(/=)
BOOST_PYTHON_PROXY_INPLACE(%=)
BOOST_PYTHON_PROXY_INPLACE(<<=)
BOOST_PYTHON_PROXY_INPLACE(>>=)
BOOST_PYTHON_PROXY_INPLACE(&=)
BOOST_PYTHON_PROXY_INPLACE(^=)
BOOST_PYTHON_PROXY_INPLACE(|=)
# undef BOOST_PYTHON_PROXY_INPLACE

template <class Policies>
inline proxy<Policies>::operator object::bool_type() const
{
    return python::object(*this);
}

template <class Policies>
inline bool proxy<Policies>::operator!() const
{
    return !python::object(*this);
}
    
}}} // namespace boost::python::api

#endif // PROXY_DWA2002615_HPP
