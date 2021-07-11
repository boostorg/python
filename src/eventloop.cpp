// Copyright Pan Yue 2021.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
// 1. posix::stream_descriptor need windows version
// 2. call_* need return async.Handle
// 3. _ensure_fd_no_transport
// 4. _ensure_resolve

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/python.hpp>
#include <boost/python/eventloop.hpp>
#include <boost/mpl/vector.hpp>
#include <Python.h>


namespace boost { namespace python { namespace asio {
namespace
{

bool _hasattr(object o, const char* name)
{
    return PyObject_HasAttrString(o.ptr(), name);
}

void _sock_connect_cb(object pymod_socket, object fut, object sock, object addr)
{
    try 
    {
        object err = sock.attr("getsockopt")(
            pymod_socket.attr("SOL_SOCKET"), pymod_socket.attr("SO_ERROR"));
        if (err != object(0)) {
            // TODO: print the address
            PyErr_SetString(PyExc_OSError, "Connect call failed {address}");
            throw_error_already_set();
        }
        fut.attr("set_result")(object());
    }
    catch (const error_already_set& e)
    {
        if (PyErr_ExceptionMatches(PyExc_BlockingIOError)
            || PyErr_ExceptionMatches(PyExc_InterruptedError))
        {
            PyErr_Clear();
            // pass
        }
        else if (PyErr_ExceptionMatches(PyExc_SystemExit)
            || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
        {
            // raise
        }
        else
        {
            PyErr_Clear();
            fut.attr("set_exception")(std::current_exception());
        }
    }
}

void _sock_accept(event_loop& loop, object fut, object sock)
{
    int fd = extract<int>(sock.attr("fileno")());
    object conn;
    object address;
    try 
    {
        object ret = sock.attr("accept")();
        conn = ret[0];
        address = ret[1];
        conn.attr("setblocking")(object(false));
        fut.attr("set_result")(make_tuple(conn, address));
    }
    catch (const error_already_set& e)
    {
        if (PyErr_ExceptionMatches(PyExc_BlockingIOError)
            || PyErr_ExceptionMatches(PyExc_InterruptedError))
        {
            PyErr_Clear();
            loop.add_reader(fd, make_function(bind(
                _sock_accept, boost::ref(loop), fut, sock),
                default_call_policies(), boost::mpl::vector<void, object>()));
        }
        else if (PyErr_ExceptionMatches(PyExc_SystemExit)
            || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
        {
            // raise
        }
        else
        {
            PyErr_Clear();
            fut.attr("set_exception")(std::current_exception());
        }
    }  
}

}

void event_loop::_add_reader_or_writer(int fd, object f, int key)
{
    // add descriptor
    if (_descriptor_map.find(key) == _descriptor_map.end())
    {
        _descriptor_map.emplace(key,
            std::move(std::make_unique<boost::asio::posix::stream_descriptor>(_strand.context(), fd))
        );
    }

    _descriptor_map.find(key)->second->async_wait(boost::asio::posix::descriptor::wait_type::wait_read,
        boost::asio::bind_executor(_strand, [key, f, loop=this] (const boost::system::error_code& ec)
        {
            // move descriptor
            auto iter = loop->_descriptor_map.find(key);
            if (iter != loop->_descriptor_map.end())
            {
                iter->second->release();
                loop->_descriptor_map.erase(iter);
            }
            loop->call_soon(f);
        }));
    return;
}

void event_loop::_remove_reader_or_writer(int key)
{
    auto iter = _descriptor_map.find(key);
    if (iter != _descriptor_map.end())
    {
        iter->second->release();
        _descriptor_map.erase(iter);
    }
}

void event_loop::call_later(double delay, object f)
{
    auto p_timer = std::make_shared<boost::asio::steady_timer>(_strand.context(),
            std::chrono::nanoseconds(int64_t(delay * 1e9)));
    p_timer->async_wait(boost::asio::bind_executor(
        _strand, 
        [f, p_timer, this] (const boost::system::error_code& ec) {f();}));
}

void event_loop::call_at(double when, object f)
{
    double diff = when - time();
    if (diff > 0)
        return call_later(diff, f);
    return call_soon(f);
}

object event_loop::sock_recv(object sock, size_t nbytes)
{
    int fd = extract<int>(sock.attr("fileno")());
    int fd_dup = dup(fd);
    object py_fut = _pymod_concurrent_future.attr("Future")();
    add_reader(fd_dup, make_function(
        [py_fut, nbytes, fd=fd_dup] (object obj) {
            std::vector<char> buffer(nbytes);
            read(fd, buffer.data(), nbytes);
            py_fut.attr("set_result")(object(handle<>(PyBytes_FromStringAndSize(buffer.data(), nbytes))));
        },
        default_call_policies(), boost::mpl::vector<void, object>()));
    return py_fut;
}

object event_loop::sock_recv_into(object sock, object buffer)
{
    int fd = extract<int>(sock.attr("fileno")());
    int fd_dup = dup(fd);
    ssize_t nbytes = len(buffer);
    object py_fut = _pymod_concurrent_future.attr("Future")();
    add_reader(fd_dup, make_function(
        [py_fut, nbytes, fd=fd_dup] (object obj) {
            std::vector<char> buffer(nbytes);
            ssize_t nbytes_read = read(fd, buffer.data(), nbytes);
            py_fut.attr("set_result")(nbytes_read);
        }, 
        default_call_policies(), boost::mpl::vector<void, object>()));
    return py_fut;
}

object event_loop::sock_sendall(object sock, object data)
{
    int fd = extract<int>(sock.attr("fileno")());
    int fd_dup = dup(fd);
    char const* py_str = extract<char const*>(data.attr("decode")());
    ssize_t py_str_len = len(data);
    object py_fut = _pymod_concurrent_future.attr("Future")();
    add_writer(fd_dup, make_function(
        [py_fut, fd, py_str, py_str_len] (object obj) {
            write(fd, py_str, py_str_len);
            py_fut.attr("set_result")(object());
        }, 
        default_call_policies(), boost::mpl::vector<void, object>()));
    return py_fut;
}

object event_loop::sock_connect(object sock, object address)
{
    
    if (!_hasattr(_pymod_socket, "AF_UNIX") || sock.attr("family") != _pymod_socket.attr("AF_UNIX"))
    {
        // TODO: _ensure_resolve
    }
    object fut = _pymod_concurrent_future.attr("Future")();
    int fd = extract<int>(sock.attr("fileno")());
    try 
    {
        sock.attr("connect")(address);
        fut.attr("set_result")(object());
    }
    catch (const error_already_set& e)
    {
        if (PyErr_ExceptionMatches(PyExc_BlockingIOError)
            || PyErr_ExceptionMatches(PyExc_InterruptedError))
        {
            PyErr_Clear();
            add_writer(dup(fd), make_function(bind(
                _sock_connect_cb, _pymod_socket, fut, sock, address),
                default_call_policies(), boost::mpl::vector<void, object>()));
        }
        else if (PyErr_ExceptionMatches(PyExc_SystemExit)
            || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
        {
            // raise
        }
        else
        {
            PyErr_Clear();
            fut.attr("set_exception")(std::current_exception());
        }
    }
    return fut;
}

object event_loop::sock_accept(object sock)
{
    object fut = _pymod_concurrent_future.attr("Future")();
    _sock_accept(*this, fut, sock);
    return fut;
}

// TODO: implement this
object event_loop::sock_sendfile(object sock, object file, int offset, int count, bool fallback)
{
    PyErr_SetString(PyExc_NotImplementedError, "Not implemented!");
    throw_error_already_set();
    return object();
}

// TODO: implement this
object event_loop::start_tls(object transport, object protocol, object sslcontext, 
    bool server_side, object server_hostname, object ssl_handshake_timeout)
{
    PyErr_SetString(PyExc_NotImplementedError, "Not implemented!");
    throw_error_already_set();
    return object();
}

object event_loop::getaddrinfo(object host, int port, int family, int type, int proto, int flags)
{
    object py_fut = _pymod_concurrent_future.attr("Future")();
    call_soon(make_function(
        [this, py_fut, host, port, family, type, proto, flags] (object obj) {
            object res = _pymod_socket.attr("getaddrinfo")(host, port, family, type, proto, flags);
            py_fut.attr("set_result")(res);
        },
        default_call_policies(), 
        boost::mpl::vector<void, object>()));
    return py_fut;
}

object event_loop::getnameinfo(object sockaddr, int flags)
{
    object py_fut = _pymod_concurrent_future.attr("Future")();
    call_soon(make_function(
        [this, py_fut, sockaddr, flags] (object obj) {
            object res = _pymod_socket.attr("getnameinfo")(sockaddr, flags);
            py_fut.attr("set_result")(res);
        },
        default_call_policies(),
        boost::mpl::vector<void, object>()));
    return py_fut;
}

void event_loop::default_exception_handler(object context)
{
    object message = context.attr("get")(str("message"));
    if (message == object())
    {
        message = str("Unhandled exception in event loop");
    }

    object exception = context.attr("get")(str("exception"));
    object exc_info;
    if (exception != object())
    {
        exc_info = make_tuple(exception.attr("__class__"), exception, exception.attr("__traceback__"));
    }
    else
    {
        exc_info = object(false);
    }
    if (!PyObject_IsTrue(context.attr("__contains__")(str("source_traceback")).ptr()) &&
        _exception_handler != object() &&
        _exception_handler.attr("_source_traceback") != object())
    {
        context["handle_traceback"] = _exception_handler.attr("_source_traceback");
    }

    list log_lines;
    log_lines.append(message);
    list context_keys(context.attr("keys"));
    context_keys.sort();
    for (int i = 0; i < len(context_keys); i++)
    {
        std::string key = extract<std::string>(context_keys[i]);
        if (key == "message" || key == "exception")
            continue;
        str value(context[key]);
        if (key == "source_traceback")
        {
            str tb = str("").join(_pymod_traceback.attr("format_list")(value));
            value = str("Object created at (most recent call last):\n");
            value += tb.rstrip();
        }
        else if (key == "handle_traceback")
        {
            str tb = str("").join(_pymod_traceback.attr("format_list")(value));
            value = str("Handle created at (most recent call last):\n");
            value += tb.rstrip();
        }
        else
        {
            value = str(value.attr("__str__")());
        }
        std::ostringstream stringStream;
        stringStream << key << ": " << value;
        log_lines.append(str(stringStream.str()));
    }
    list args;
    dict kwargs;
    args.append(str("\n").join(log_lines));
    kwargs["exc_info"] = exc_info;
    _pymod_logger.attr("error")(tuple(args), **kwargs);
}

void event_loop::call_exception_handler(object context)
{
    if (_exception_handler == object())
    {
        try
        {
            default_exception_handler(context);
        }
        catch (const error_already_set& e)
        {
            if (PyErr_ExceptionMatches(PyExc_SystemExit)
                || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
            {
                // raise
            }
            else
            {
                PyErr_Clear();
                list args;
                dict kwargs;
                args.append(str("Exception in default exception handler"));
                kwargs["exc_info"] = true;
                _pymod_logger.attr("error")(tuple(args), **kwargs);
            }
        }
    }
    else
    {
        try
        {
            _exception_handler(context);
        }
        catch (const error_already_set& e)
        {
            if (PyErr_ExceptionMatches(PyExc_SystemExit)
                || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
            {
                // raise
            }
            else
            {
                PyObject *ptype, *pvalue, *ptraceback;
                PyErr_Fetch(&ptype, &pvalue, &ptraceback);
                PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);
                object type{handle<>(ptype)};
                object value{handle<>(pvalue)};
                object traceback{handle<>(ptraceback)};
                try
                {
                    dict tmp_dict;
                    tmp_dict["message"] = str("Unhandled error in exception handler");
                    tmp_dict["exception"] = value;
                    tmp_dict["context"] = context;
                    default_exception_handler(tmp_dict);
                }
                catch (const error_already_set& e)
                {
                    if (PyErr_ExceptionMatches(PyExc_SystemExit)
                        || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
                    {
                        // raise
                    }
                    else
                    {
                        boost::python::list args;
                        boost::python::dict kwargs;
                        args.append(str("Exception in default exception handler"));
                        kwargs["exc_info"] = true;
                        _pymod_logger.attr("error")(tuple(args), **kwargs);
                    }
                }
            }
        }
    }
}


}}}