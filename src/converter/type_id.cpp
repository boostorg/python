// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/type_id.hpp>
#if !defined(__GNUC__) || __GNUC__ >= 3 || __SGI_STL_PORT
# include <ostream>
#else 
# include <ostream.h>
#endif 

namespace boost { namespace python { namespace converter { 

BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream& os, undecorated_type_id_t const& x)
{
    return os << x.name();
}

BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream& os, type_id_t const& x)
{
    os << x.m_base_type;
    if (x.m_decoration & type_id_t::const_)
        os << " const";
    if (x.m_decoration & type_id_t::volatile_)
        os << " volatile";
    if (x.m_decoration & type_id_t::reference)
        os << "&";
    return os;
}

}}} // namespace boost::python::converter
