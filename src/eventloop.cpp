// Copyright Pan Yue 2021.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
// 1. posix::stream_descriptor need windows version
// 2. call_* need return async.Handle
// 3. _ensure_fd_no_transport
// 4. _ensure_resolve

#include <errno.h>
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

void raise_dup_error()
{
    PyErr_SetString(PyExc_OSError, std::system_category().message(errno).c_str());
    throw_error_already_set();
}

} // namespace

void event_loop::_sock_connect_cb(object pymod_socket, object fut, object sock, object addr)
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

void event_loop::_sock_accept(event_loop& loop, object fut, object sock)
{
    int fd = extract<int>(sock.attr("fileno")());
    object conn, address;
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
            loop._async_wait_fd(fd, bind(_sock_accept, boost::ref(loop), fut, sock), loop._write_key(fd));
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

void event_loop::call_later(double delay, object f)
{
    auto p_timer = std::make_shared<boost::asio::steady_timer>(
        _strand.context(),
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(delay)));
    p_timer->async_wait(boost::asio::bind_executor(_strand,
        [f, p_timer] (const boost::system::error_code& ec) {f();}));
}

void event_loop::call_at(double when, object f)
{
    using sc = std::chrono::steady_clock;
    auto p_timer = std::make_shared<boost::asio::steady_timer>(
        _strand.context(),
        sc::duration(static_cast<sc::time_point::rep>(when)));
    p_timer->async_wait(boost::asio::bind_executor(_strand, 
        [f, p_timer] (const boost::system::error_code& ec) {f();}));
}

object event_loop::sock_recv(object sock, size_t nbytes)
{
    int fd = extract<int>(sock.attr("fileno")());
    int fd_dup = dup(fd);
    if (fd_dup == -1)
        raise_dup_error();
    object py_fut = create_future();
    _async_wait_fd(fd_dup, 
        [py_fut, nbytes, fd=fd_dup] {
            std::vector<char> buffer(nbytes);
            read(fd, buffer.data(), nbytes);
            py_fut.attr("set_result")(object(handle<>(PyBytes_FromStringAndSize(buffer.data(), nbytes))));
        },
        _read_key(fd));
    return py_fut;
}

object event_loop::sock_recv_into(object sock, object buffer)
{
    int fd = extract<int>(sock.attr("fileno")());
    int fd_dup = dup(fd);
    if (fd_dup == -1)
        raise_dup_error();
    ssize_t nbytes = len(buffer);
    object py_fut = create_future();
    _async_wait_fd(fd_dup, 
        [py_fut, nbytes, fd=fd_dup] {
            std::vector<char> buffer(nbytes);
            ssize_t nbytes_read = read(fd, buffer.data(), nbytes);
            py_fut.attr("set_result")(nbytes_read);
        },
        _read_key(fd));
    return py_fut;
}

object event_loop::sock_sendall(object sock, object data)
{
    int fd = extract<int>(sock.attr("fileno")());
    int fd_dup = dup(fd);
    if (fd_dup == -1)
        raise_dup_error();
    char const* py_str = extract<char const*>(data.attr("decode")());
    ssize_t py_str_len = len(data);
    object py_fut = create_future();
    _async_wait_fd(fd_dup, 
        [py_fut, fd, py_str, py_str_len] {
            write(fd, py_str, py_str_len);
            py_fut.attr("set_result")(object());
        },
        _write_key(fd));
    return py_fut;
}

object event_loop::sock_connect(object sock, object address)
{
    
    if (!_hasattr(_pymod_socket, "AF_UNIX") || sock.attr("family") != _pymod_socket.attr("AF_UNIX"))
    {
        // TODO: _ensure_resolve
    }
    object py_fut = create_future();
    int fd = extract<int>(sock.attr("fileno")());
    try 
    {
        sock.attr("connect")(address);
        py_fut.attr("set_result")(object());
    }
    catch (const error_already_set& e)
    {
        if (PyErr_ExceptionMatches(PyExc_BlockingIOError)
            || PyErr_ExceptionMatches(PyExc_InterruptedError))
        {
            PyErr_Clear();
            int fd_dup = dup(fd);
            if (fd_dup == -1)
                raise_dup_error();
            _async_wait_fd(fd_dup, bind(_sock_connect_cb, _pymod_socket, py_fut, sock, address), _write_key(fd));
        }
        else if (PyErr_ExceptionMatches(PyExc_SystemExit)
            || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
        {
            // raise
        }
        else
        {
            PyErr_Clear();
            py_fut.attr("set_exception")(std::current_exception());
        }
    }
    return py_fut;
}

object event_loop::sock_accept(object sock)
{
    object py_fut = create_future();
    _sock_accept(*this, py_fut, sock);
    return py_fut;
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
    object py_fut = create_future();
    _strand.post(
        [this, py_fut, host, port, family, type, proto, flags] {
            object res = _pymod_socket.attr("getaddrinfo")(host, port, family, type, proto, flags);
            py_fut.attr("set_result")(res);
        });
    return py_fut;
}

object event_loop::getnameinfo(object sockaddr, int flags)
{
    object py_fut = create_future();
    _strand.post(
        [this, py_fut, sockaddr, flags] {
            object res = _pymod_socket.attr("getnameinfo")(sockaddr, flags);
            py_fut.attr("set_result")(res);
        });
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
    _py_logger.attr("error")(tuple(args), **kwargs);
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
                _py_logger.attr("error")(tuple(args), **kwargs);
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
                        _py_logger.attr("error")(tuple(args), **kwargs);
                    }
                }
            }
        }
    }
}

object event_loop::create_future()
{
    boost::python::dict kwargs;
    kwargs["loop"] = boost::ref(*this);
    return _pymod_asyncio_futures.attr("Future")(*boost::python::tuple(), **kwargs);
}

void set_default_event_loop(const boost::asio::io_context::strand& strand)
{
    class_<event_loop, boost::noncopyable>("BoostAsioEventLoop", init<boost::asio::io_context::strand&>())
        .def("call_soon", &event_loop::call_soon)
        .def("call_soon_thread_safe", &event_loop::call_soon_thread_safe)
        .def("call_later", &event_loop::call_later)
        .def("call_at", &event_loop::call_at)
        .def("time", &event_loop::time)
        .def("add_reader", &event_loop::add_reader)
        .def("remove_reader", &event_loop::remove_reader)
        .def("add_writer", &event_loop::add_writer)
        .def("remove_writer", &event_loop::remove_writer)
        .def("sock_recv", &event_loop::sock_recv)
        .def("sock_recv_into", &event_loop::sock_recv_into)
        .def("sock_sendall", &event_loop::sock_sendall)
        .def("sock_connect", &event_loop::sock_connect)
        .def("sock_accept", &event_loop::sock_accept)
        .def("sock_sendfile", &event_loop::sock_sendfile)
        .def("start_tls", &event_loop::start_tls)
        .def("getaddrinfo", &event_loop::getaddrinfo)
        .def("getnameinfo", &event_loop::getnameinfo)
        .def("set_exception_handler", &event_loop::set_exception_handler)
        .def("get_exception_handler", &event_loop::get_exception_handler)
        .def("default_exception_handler", &event_loop::default_exception_handler)
        .def("call_exception_handler", &event_loop::call_exception_handler)
        .def("create_future", &event_loop::create_future)
        .def("get_debug", &event_loop::get_debug);

    object asyncio = import("asyncio");
    object abstract_policy = asyncio.attr("AbstractEventLoopPolicy");

    dict method_dict;
    std::shared_ptr<event_loop> p_loop = std::make_shared<event_loop>(strand);

    method_dict["get_event_loop"] = make_function(
        [p_loop] (object e) {return object(boost::ref(*p_loop));},
        default_call_policies(),
        boost::mpl::vector<object, object>()
    );

    object class_boost_policy = call<object>(
        (PyObject*)&PyType_Type, 
        str("BoostEventLoopPolicy"),
        boost::python::make_tuple(abstract_policy),
        method_dict);

    object boost_policy_instance = class_boost_policy.attr("__call__")();
    asyncio.attr("set_event_loop_policy")(boost_policy_instance);
}

}}} // namespace boost::python