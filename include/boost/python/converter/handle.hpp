// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef HANDLE_DWA20011130_HPP
# define HANDLE_DWA20011130_HPP
# include <boost/python/detail/config.hpp>
# include <boost/utility.hpp>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

struct BOOST_PYTHON_DECL body;

// The common base class for unwrap_ and wrap_ handle objects. They
// share a common base so that handles can be linked into a chain
// within a function wrapper which is managed by a single object.
struct BOOST_PYTHON_DECL handle : private boost::noncopyable
{
 public: // member functions

    // All constructors take a body* passed from the derived class.
    //
    // Constructors taking a handle links this into a chain of
    // handles, for more efficient management in function wrappers
    handle();
    handle(body* body);
    handle(body* body, handle& prev);

    // returns true iff all handles in the chain can convert their
    // arguments
    bool convertible() const;

    // safe_bool idiom from Peter Dimov: provides handles to/from
    // bool without enabling handles to integer types/void*.
 private:
    struct dummy { inline void nonnull() {} };
    typedef void (dummy::*safe_bool)();
 public:
    inline operator safe_bool() const;
    inline safe_bool operator!() const;
    
 protected: // member functions for derived classes
    // Get the body we hold
    inline body* get_body() const;

    inline void set_body(body*);
    inline void set_prev(handle&);
    
    // Release all bodies in the chain, in reverse order of
    // initialization. Only actually called for the head of the chain.
    void destroy();
    
 private:
    // Holds implementation
    body* m_body;
    
    // handle for next argument, if any.
    handle* m_next;
};

//
// implementations
// 
inline handle::handle()
    : m_next(0)
{}

inline handle::handle(body* body, handle& prev)
    : m_body(body), m_next(0)
{
    prev.m_next = this;
}

inline handle::handle(body* body)
    : m_body(body), m_next(0)
{
}

inline handle::operator handle::safe_bool() const
{
    return convertible() ? &dummy::nonnull : 0;
}

inline handle::safe_bool handle::operator!() const
{
    return convertible() ? 0 : &dummy::nonnull;
}

inline body* handle::get_body() const
{
    return m_body;
}

inline void handle::set_body(body* body)
{
    m_body = body;
}

inline void handle::set_prev(handle& prev)
{
    prev.m_next = this;
}

}}} // namespace boost::python::converter

#endif // HANDLE_DWA20011130_HPP
