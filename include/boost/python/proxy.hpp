// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef PROXY_DWA2002615_HPP
# define PROXY_DWA2002615_HPP
# include <boost/python/object_core.hpp>

namespace boost { namespace python { 

class object;

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
    proxy& operator=(copy_ctor_self);
    
    template <class T>
    inline proxy& operator=(T const& rhs)
    {
        Policies::set(m_target, m_key, python::object(rhs));
        return *this;
    }

# define BOOST_PYTHON_PROXY_ASSIGN_DECL(op)     \
    object operator op (object const&);         \
                                                \
    template <class T>                          \
    object operator op (T const& rhs)           \
    {                                           \
        return *this op python::object(rhs);    \
    }
    
//    BOOST_PYTHON_PROXY_ASSIGN_DECL(=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(+=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(-=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(*=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(/=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(%=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(<<=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(>>=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(&=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(^=)
    BOOST_PYTHON_PROXY_ASSIGN_DECL(|=)
# undef BOOST_PYTHON_PROXY_ASSIGN_DECL

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
inline proxy<Policies>& proxy<Policies>::operator=(typename proxy::copy_ctor_self rhs)
{
    return *this = python::object(rhs);
}

# define BOOST_PYTHON_PROXY_ASSIGN_DEF(op)                      \
template <class Policies>                                       \
inline object proxy<Policies>::operator op(object const& other) \
{                                                               \
    return Policies::set(                                       \
          m_target, m_key                                       \
        , Policies::get(m_target,m_key) op other);              \
}

BOOST_PYTHON_PROXY_ASSIGN_DEF(+=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(-=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(*=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(/=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(%=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(<<=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(>>=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(&=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(^=)
BOOST_PYTHON_PROXY_ASSIGN_DEF(|=)

# undef BOOST_PYTHON_PROXY_ASSIGN_DEF


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
    
}} // namespace boost::python

#endif // PROXY_DWA2002615_HPP
