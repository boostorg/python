// Copyright Pan Yue 2021.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
// 1. posix::stream_descriptor need windows version
// 2. call_* need return async.Handle
# ifndef EVENT_LOOP_PY2021_HPP
# define EVENT_LOOP_PY2021_HPP

#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/python.hpp>

namespace boost { namespace python { namespace asio {

class event_loop
{
public:
    event_loop(boost::asio::io_context::strand& strand): 
        _strand{strand}, _created_time{std::chrono::steady_clock::now()}
    {
        try
        {
            _pymod_ssl = import("ssl");
        }
        catch (const error_already_set& e)
        {
            if (PyErr_ExceptionMatches(PyExc_ImportError))
            {
                PyErr_Clear();
            }
        }
    }

    // TODO: An instance of asyncio.Handle is returned, which can be used later to cancel the callback.
    inline void call_soon(object f)
    {
        _strand.post([f, loop=this] {
            f(boost::ref(*loop));
        });
        return;
    }

    // TODO: implement this
    inline void call_soon_thread_safe(object f) {};

    // Schedule callback to be called after the given delay number of seconds
    // TODO: An instance of asyncio.Handle is returned, which can be used later to cancel the callback.
    void call_later(double delay, object f);

    void call_at(double when, object f);

    inline double time()
    {
        return static_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - _created_time).count();
    }

    inline void add_reader(int fd, object f)
    {
        _add_reader_or_writer(fd, f, fd * 2);
    }

    inline void remove_reader(int fd)
    {
        _remove_reader_or_writer(fd * 2);
    }

    inline void add_writer(int fd, object f)
    {
        _add_reader_or_writer(fd, f, fd * 2 + 1);
    }

    inline void remove_writer(int fd)
    {
        _remove_reader_or_writer(fd * 2 + 1);
    }


    object sock_recv(object sock, size_t nbytes);

    object sock_recv_into(object sock, object buffer);

    object sock_sendall(object sock, object data);

    object sock_connect(object sock, object address);

    object sock_accept(object sock);
    
    object sock_sendfile(object sock, object file, int offset = 0, int count = 0, bool fallback = true);

    object start_tls(object transport, object protocol, object sslcontext, 
        bool server_side = false, 
        object server_hostname = object(), 
        object ssl_handshake_timeout = object());

    object getaddrinfo(object host, int port, int family = 0, int type = 0, int proto = 0, int flags = 0);

    object getnameinfo(object sockaddr, int flags = 0);

    void set_exception_handler(object handler)
    {
        if (handler != object() && !PyObject_HasAttrString(handler.ptr(), "__call__")) {
            PyErr_SetString(PyExc_TypeError, "A callable object or None is expected");
            throw_error_already_set();
        }
        _exception_handler = handler;
    }

    object get_exception_handler()
    {
        return _exception_handler;
    }

    void default_exception_handler(object context);

    void call_exception_handler(object context);

private:
    int64_t _timer_id = 0;
    object _pymod_ssl = object();
    object _pymod_socket = import("socket");
    object _pymod_traceback = import("traceback");
    object _pymod_logger = import("asyncio.log").attr("logger");
    object _pymod_concurrent_future = import("concurrent").attr("futures");
    object _exception_handler = object();
    boost::asio::io_context::strand _strand;
    std::unordered_map<int, std::unique_ptr<boost::asio::steady_timer>> _id_to_timer_map;
    // read: key = fd * 2 + 0, write: key = fd * 2 + 1
    std::unordered_map<int, std::unique_ptr<boost::asio::posix::stream_descriptor>> _descriptor_map;
    std::chrono::steady_clock::time_point _created_time;

    void _add_reader_or_writer(int fd, object f, int key);
    void _remove_reader_or_writer(int key);
};

}}}


# endif
