// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/converter/handle.hpp>
#include <boost/python/converter/body.hpp>

namespace boost { namespace python { namespace converter { 

bool handle::convertible() const
{
    for (handle const* p = this; p != 0; p = p->m_next)
    {
        if (p->m_body == 0)
            return false;
    }
    return true;
}

void handle::destroy()
{
    // Recurse down the chain releasing from tail to head
    if (m_next != 0)
        m_next->destroy();

    // Our body knows how to destroy us. If we never got a body,
    // there's nothing to do.
    if (m_body)
        m_body->destroy_handle(this);
}

// void handle::dummy::nonnull() {}

}}} // namespace boost::python::converter
