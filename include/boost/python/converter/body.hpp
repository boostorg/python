// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BODY_DWA2001127_HPP
# define BODY_DWA2001127_HPP
# include <boost/config.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/export.hpp>

namespace boost { namespace python { namespace converter { 

struct BOOST_PYTHON_EXPORT handle;

struct BOOST_PYTHON_EXPORT body
{
 public:
    body(type_id_t key);
    virtual ~body() {}

    // default implementation is a no-op
    virtual void destroy_handle(handle*) const;

    type_id_t key() const;

 private:
    type_id_t m_key;
};

//
// implementations
//
inline body::body(type_id_t key)
    : m_key(key)
{
}

inline type_id_t body::key() const
{
    return m_key;
}

}}} // namespace boost::python::converter

#endif // BODY_DWA2001127_HPP
