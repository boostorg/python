//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef ERRORS_DWA052500_H_
# define ERRORS_DWA052500_H_

# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python {

struct error_already_set {};
struct argument_error : error_already_set {};

struct object_functor_base
{
    typedef PyObject* result_type;
    virtual PyObject* operator()() const = 0;
 private:
    static void* operator new(std::size_t); // don't allow dynamic allocation
    void operator delete(void*); 
    void operator delete(void*, size_t); 
};

template <class T>
struct object_functor : object_functor_base
{
    object_functor(T const& f)
        : m_f(f)
    {
    }
    
    PyObject* operator()() const
    {
        return m_f();
    }
 private:
    T const& m_f;
};


// Handles exceptions caught just before returning to Python code.
PyObject* handle_exception_impl(object_functor_base const& f);

template <class T>
PyObject* handle_exception(T const& f)
{
    return handle_exception_impl(object_functor<T>(f));
}

void handle_exception(void (*)());

template <class T>
T* expect_non_null(T* x)
{
    if (x == 0)
        throw error_already_set();
    return x;
}

}} // namespace boost::python

#endif // ERRORS_DWA052500_H_
