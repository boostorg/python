// Copyright John Zwinck 2012.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/gil.hpp>
#include <boost/assert.hpp>
#include <boost/thread/tss.hpp>

namespace boost { namespace python {

namespace {

    void thread_cleanup(PyThreadState*)
    {
        // nothing needs to be done here
    }

    boost::thread_specific_ptr<PyThreadState> g_thread_state(thread_cleanup);

} // namespace

    gil_guard_release::gil_guard_release()
        : m_do_acquire(false)
    {
        if (!g_thread_state.get() && PyEval_ThreadsInitialized())
        {
            g_thread_state.reset(PyEval_SaveThread());
            m_do_acquire = true;
        }
    }

    gil_guard_release::~gil_guard_release()
    {
        if (m_do_acquire)
        {
            if (g_thread_state.get())
            {
                PyEval_RestoreThread(g_thread_state.get());
                g_thread_state.reset();
            }
            else
            {
                // This should never happen.
                BOOST_ASSERT(false);
            }
        }
    }

    gil_guard_acquire::gil_guard_acquire()
        : m_thread_state(g_thread_state.get())
    {
        if (m_thread_state)
        {
            PyEval_RestoreThread(m_thread_state);
            g_thread_state.reset();
        }
    }

    gil_guard_acquire::~gil_guard_acquire()
    {
        if (m_thread_state)
        {
            BOOST_ASSERT(!g_thread_state.get());
            g_thread_state.reset(PyEval_SaveThread());
        }
    }

}} // namespace boost::python

