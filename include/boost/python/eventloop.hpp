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
    event_loop(const boost::asio::io_context::strand& strand): _strand{strand}
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
        _strand.post([f]{f();});
    }

    // TODO: implement this
    inline void call_soon_thread_safe(object f) {};

    // Schedule callback to be called after the given delay number of seconds
    // TODO: An instance of asyncio.Handle is returned, which can be used later to cancel the callback.
    void call_later(double delay, object f);

    void call_at(double when, object f);

    inline double time()
    {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }

    inline void add_reader(int fd, object f)
    {
        _async_wait_fd(fd, f, _read_key(fd));
    }

    inline void remove_reader(int fd)
    {
        _descriptor_map.erase(_read_key(fd));
    }

    inline void add_writer(int fd, object f)
    {
        _async_wait_fd(fd, f, _write_key(fd));
    }

    inline void remove_writer(int fd)
    {
        _descriptor_map.erase(_write_key(fd));
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
    object _pymod_ssl = object();
    object _pymod_socket = import("socket");
    object _pymod_traceback = import("traceback");
    object _py_wrap_future = import("asyncio").attr("wrap_future");
    object _py_logger = import("asyncio.log").attr("logger");
    object _pymod_concurrent_future = import("concurrent").attr("futures");
    object _exception_handler = object();
    boost::asio::io_context::strand _strand;
    // read: key = fd * 2 + 0, write: key = fd * 2 + 1
    std::unordered_map<int, std::unique_ptr<boost::asio::posix::stream_descriptor>> _descriptor_map;

    inline int _read_key(int fd)
    {
        return fd * 2;
    }

    inline int _write_key(int fd)
    {
        return fd * 2 + 1;
    }

    template<typename F>
    void _async_wait_fd(int fd, F f, int key)
    {
        // add descriptor
        if (_descriptor_map.find(key) == _descriptor_map.end())
        {
            _descriptor_map.emplace(key,
                std::move(std::make_unique<boost::asio::posix::stream_descriptor>(_strand.context(), fd))
            );
        }

        _descriptor_map.find(key)->second->async_wait(boost::asio::posix::descriptor::wait_type::wait_read,
            boost::asio::bind_executor(_strand, [this, key, f] (const boost::system::error_code& ec)
            {
                _descriptor_map.erase(key);
                f();
            }));
        return;
    }

    static void _sock_connect_cb(object pymod_socket, object fut, object sock, object addr);
    static void _sock_accept(event_loop& loop, object fut, object sock);
};

}}} // namespace boost::python


# endif
