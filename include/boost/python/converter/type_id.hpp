//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#ifndef TYPE_ID_DWA20011127_HPP
# define TYPE_ID_DWA20011127_HPP
# include <boost/python/detail/config.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/operators.hpp>
# include <typeinfo>
# include <iosfwd>
# include <cstring>


namespace boost { namespace python { namespace converter { 

// a portable mechanism for identifying types at runtime across modules.

namespace detail
{
  template <class T> class dummy;
}

// for this compiler at least, cross-shared-library type_info
// comparisons don't work, so use typeid(x).name() instead. It's not
// yet clear what the best default strategy is.
# if defined(__GNUC__) && __GNUC__ >= 3
#  define BOOST_PYTHON_TYPE_ID_NAME
# endif 

// type ids which represent the same information as std::type_info
// (i.e. the top-level reference and cv-qualifiers are stripped), but
// which works across shared libraries.
struct undecorated_type_id_t : totally_ordered<undecorated_type_id_t>
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    typedef char const* base_id_t;
#  else
    typedef std::type_info const* base_id_t;
#  endif
    
    undecorated_type_id_t(base_id_t);
    
    // default constructor for use in BGL graph internal properties
    undecorated_type_id_t() {} 

    bool operator<(undecorated_type_id_t const& rhs) const;
    bool operator==(undecorated_type_id_t const& rhs) const;
    
    friend BOOST_PYTHON_DECL std::ostream& operator<<(
        std::ostream&, undecorated_type_id_t const&);
    
 private: // data members
    base_id_t m_base_type;
};

struct type_id_t : totally_ordered<type_id_t>
{
    enum decoration { const_ = 0x1, volatile_ = 0x2, reference = 0x4 };
    
    type_id_t(undecorated_type_id_t, decoration decoration);

    bool operator<(type_id_t const& rhs) const;
    bool operator==(type_id_t const& rhs) const;
    friend BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream&, type_id_t const&);
    
 private: // type
    typedef undecorated_type_id_t base_id_t;
    
 private: // data members
    decoration m_decoration;
    base_id_t m_base_type;
};

#  ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct is_reference_to_const
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_reference_to_const<T const&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class T>
struct is_reference_to_volatile
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_reference_to_volatile<T volatile&>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};
#  else 
template <typename V>
struct is_const_help
{
    typedef typename mpl::select_type<
        is_const<V>::value
        , type_traits::yes_type
        , type_traits::no_type
        >::type type;
};

template <typename V>
struct is_volatile_help
{
    typedef typename mpl::select_type<
        is_volatile<V>::value
        , type_traits::yes_type
        , type_traits::no_type
        >::type type;
};

template <typename V>
typename is_const_help<V>::type reference_to_const_helper(V&);
    
type_traits::no_type
reference_to_const_helper(...);

template <class T>
struct is_reference_to_const
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = sizeof(reference_to_const_helper(t)) == sizeof(type_traits::yes_type));
};

template <typename V>
typename is_volatile_help<V>::type reference_to_volatile_helper(V&);
type_traits::no_type reference_to_volatile_helper(...);

template <class T>
struct is_reference_to_volatile
{
    static T t;
    BOOST_STATIC_CONSTANT(
        bool, value
        = sizeof(reference_to_volatile_helper(t)) == sizeof(type_traits::yes_type));
};
#  endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION 

template <class T>
inline undecorated_type_id_t undecorated_type_id(detail::dummy<T>* = 0)
{
    return undecorated_type_id_t(
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
        typeid(T).name()
#  else
        &typeid(T)
#  endif
        );
}

template <class T>
inline type_id_t type_id(detail::dummy<T>* = 0)
{
    return type_id_t(
        undecorated_type_id<T>()
        , type_id_t::decoration(
            (is_const<T>::value || is_reference_to_const<T>::value
             ? type_id_t::const_ : 0)
            | (is_volatile<T>::value || is_reference_to_volatile<T>::value
               ? type_id_t::volatile_ : 0)
            | (is_reference<T>::value ? type_id_t::reference : 0)
            )
        );
}

inline undecorated_type_id_t::undecorated_type_id_t(base_id_t base_t)
    : m_base_type(base_t)
{
}

inline type_id_t::type_id_t(undecorated_type_id_t base_t, decoration decoration)
    : m_decoration(decoration)
    , m_base_type(base_t)
{
}

inline bool undecorated_type_id_t::operator<(undecorated_type_id_t const& rhs) const
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    return std::strcmp(m_base_type, rhs.m_base_type) < 0;
#  else
    return m_base_type->before(*rhs.m_base_type);
#  endif 
}

inline bool type_id_t::operator<(type_id_t const& rhs) const
{
    return m_decoration < rhs.m_decoration
        || m_decoration == rhs.m_decoration
           && m_base_type < rhs.m_base_type;
}

inline bool undecorated_type_id_t::operator==(undecorated_type_id_t const& rhs) const
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    return !std::strcmp(m_base_type, rhs.m_base_type);
#  else
    return *m_base_type == *rhs.m_base_type;
#  endif 
}

inline bool type_id_t::operator==(type_id_t const& rhs) const
{
    return m_decoration == rhs.m_decoration && m_base_type == rhs.m_base_type;
}

BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream&, undecorated_type_id_t const&);
BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream&, type_id_t const&);

}}} // namespace boost::python::converter

#endif // TYPE_ID_DWA20011127_HPP
