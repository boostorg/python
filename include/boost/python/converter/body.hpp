// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BODY_DWA2001127_HPP
# define BODY_DWA2001127_HPP
# include <boost/python/detail/config.hpp>
# include <boost/python/converter/type_id.hpp>

namespace boost { namespace python { namespace converter { 

struct BOOST_PYTHON_DECL handle;

namespace registry
{
  class entry;
}

struct BOOST_PYTHON_DECL body
{
 public:
    body(type_id_t key);
    virtual ~body() {}

    // default implementation is a no-op
    virtual void destroy_handle(handle*) const;

    type_id_t key() const;

 protected:
    // true iff the registry is still alive
    bool can_unregister() const;
    
 private:
    // called when the registry is destroyed, to prevent it from being
    // unregistered.
    void do_not_unregister();
    friend class registry::entry;
    
 private:
    type_id_t m_key;
    bool m_can_unregister;
};

//
// implementations
//
inline body::body(type_id_t key)
    : m_key(key)
    , m_can_unregister(true)
{
}

inline type_id_t body::key() const
{
    return m_key;
}

inline bool body::can_unregister() const
{
    return m_can_unregister;
}

}}} // namespace boost::python::converter

#endif // BODY_DWA2001127_HPP
