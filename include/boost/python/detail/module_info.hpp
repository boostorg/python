// Copyright David Hawkes 2002.
// Permission is hereby granted to copy, use and modify this software
// for any purpose, including commercial distribution, provided this
// copyright notice is not removed. No warranty WHATSOEVER is provided with this
// software. Any user(s) accepts this software "as is" and as such they will not
// bind the author(s) to any claim of suitabilty for any purpose.

#ifndef MODULE_INFO
# define MODULE_INFO

#include <boost/python/object.hpp>

namespace boost { namespace python { namespace detail { 

class module_info
{
public:
    module_info(const char *name)
    {
        m_module_name = name;
    }
    void set_module(object const& m)
    {
        if(!m_primary_module)
            m_primary_module = m;
    }
    object const& get_module() const
    {
        return m_primary_module;
    }
    void set_prior_module(object const& m)
    {
        m_prior_module = m;
    }
    object const& get_prior_module() const
    {
        return m_prior_module;
    }
    const char* get_module_name() const
    {
        return m_module_name;
    }
private:
    object m_primary_module;
    object m_prior_module;
    const char* m_module_name;
};

}}}

#endif  // MODULE_INFO
