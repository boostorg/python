//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#ifndef TYPE_ID_DWA20011127_HPP
# define TYPE_ID_DWA20011127_HPP
# include <boost/python/detail/config.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/msvc_typeinfo.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/mpl/select_if.hpp>
# include <boost/operators.hpp>
# include <boost/type.hpp>
# include <typeinfo>
# include <iosfwd>
# include <cstring>


namespace boost { namespace python { namespace converter { 

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
    undecorated_type_id_t(std::type_info const&);
    
    // default constructor needed to build arrays, etc.
    undecorated_type_id_t();

    bool operator<(undecorated_type_id_t const& rhs) const;
    bool operator==(undecorated_type_id_t const& rhs) const;

    char const* name() const;
    friend BOOST_PYTHON_DECL std::ostream& operator<<(
        std::ostream&, undecorated_type_id_t const&);
    
 private: // data members
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    typedef char const* base_id_t;
#  else
    typedef std::type_info const* base_id_t;
#  endif
    
    base_id_t m_base_type;
};

struct type_id_t : totally_ordered<type_id_t>
{
    enum decoration { const_ = 0x1, volatile_ = 0x2, reference = 0x4 };
    
    type_id_t(undecorated_type_id_t, decoration = decoration());

    bool operator<(type_id_t const& rhs) const;
    bool operator==(type_id_t const& rhs) const;

    friend BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream&, type_id_t const&);

    operator undecorated_type_id_t const&() const;
 private: // type
    typedef undecorated_type_id_t base_id_t;
    
 private: // data members
    decoration m_decoration;
    base_id_t m_base_type;
};

template <class T>
inline undecorated_type_id_t undecorated_type_id(boost::type<T>* = 0)
{
    return undecorated_type_id_t(
#  if (!defined(BOOST_MSVC) || BOOST_MSVC > 1300) && (!defined(BOOST_INTEL_CXX_VERSION) || BOOST_INTEL_CXX_VERSION > 600)
        typeid(T)
#  else // strip the decoration which msvc and Intel mistakenly leave in
        python::detail::msvc_typeid<T>()
#  endif 
        );
}

template <class T>
inline type_id_t type_id(boost::type<T>* = 0)
{
    return type_id_t(
        undecorated_type_id<T>()
        , type_id_t::decoration(
            (is_const<T>::value || python::detail::is_reference_to_const<T>::value
             ? type_id_t::const_ : 0)
            | (is_volatile<T>::value || python::detail::is_reference_to_volatile<T>::value
               ? type_id_t::volatile_ : 0)
            | (is_reference<T>::value ? type_id_t::reference : 0)
            )
        );
}

inline undecorated_type_id_t::undecorated_type_id_t(std::type_info const& id)
    : m_base_type(
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
        id.name()
#  else
        &id
#  endif
        )
{
}

inline undecorated_type_id_t::undecorated_type_id_t()
    : m_base_type()
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

inline type_id_t::operator undecorated_type_id_t const&() const
{
    return m_base_type;
}

inline char const* undecorated_type_id_t::name() const
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    return m_base_type;
#  else
    return m_base_type->name();
#  endif 
}


BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream&, undecorated_type_id_t const&);
BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream&, type_id_t const&);

}}} // namespace boost::python::converter

#endif // TYPE_ID_DWA20011127_HPP
