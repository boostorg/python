// Copyright John Zwinck 2012.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PYTHON_GIL_JZ201212_HPP
# define BOOST_PYTHON_GIL_JZ201212_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/noncopyable.hpp>

namespace boost { namespace python {

    // When a C++ function is called by Python and it will be long-running,
    // it should release the Global Interpreter Lock (GIL) by constructing one of these.
    // This does not mean the C++ function needs to do this when invoked directly from C++:
    // it should instead have a wrapper that sits in front of its Python binding, like this:
    //
    // void MyClass::longRunningFunction(); // native C++ code
    //
    // void myWrapper(MyClass& my) // local function in Python bindings module
    // {
    //     gil_guard_release guard;
    //     my.longRunningFunction();
    // }
    //
    // // within BOOST_PYTHON_MODULE():
    //     class_<MyClass>("MyClass")
    //         .def("longRunningFunction", myWrapper);
    //
    // See http://wiki.python.org/moin/boost.python/HowTo#Multithreading_Support_for_my_function
    class gil_guard_release
        : boost::noncopyable
    {
    public:
        gil_guard_release();
        ~gil_guard_release();

    private:
        bool m_do_acquire;
    };

    class gil_guard_acquire
        : boost::noncopyable
    {
    public:
        gil_guard_acquire();
        ~gil_guard_acquire();

    private:
        PyThreadState* m_thread_state;
    };

}} // namespace boost::python

#endif // BOOST_PYTHON_GIL_JZ201212_HPP
