// Copyright Pan Yue 2021.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
// 1. posix::stream_descriptor need windows version
// 2. call_* need return async.Handle
// 3. _ensure_fd_no_transport
// 4. _ensure_resolve

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

void _sock_recv_handler(
    std::promise<std::vector<char>>& prom_data, 
    std::promise<size_t>& prom_nbytes_read, 
    size_t nbytes, 
    int fd)
{
    std::vector<char> buffer(nbytes);
    prom_nbytes_read.set_value(read(fd, buffer.data(), nbytes));
    prom_data.set_value(std::move(buffer));
}

void _sock_send_handler(std::promise<size_t>& prom, int fd, const char *py_str, ssize_t len)
{
    size_t nwrite = write(fd, py_str, len);
    prom.set_value(nwrite);
}

void _sock_connect_cb(object pymod_socket, std::promise<void>& prom, std::future<void>& fut, object sock, object addr)
{
    try 
    {
        object err = sock.attr("getsockopt")(
            pymod_socket.attr("SOL_SOCKET"), pymod_socket.attr("SO_ERROR"));
        if (err != object(0)) {
            // TODO: print the address
            PyErr_SetString(PyExc_OSError, "Connect call failed {address}");
        }
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
        else if (PyErr_ExceptionMatches(PyExc_BaseException))
        {
            PyErr_Clear();
            prom.set_exception(std::current_exception());
        }
        else
        {
            PyErr_Clear();
            prom.set_value();
        }
    }
}

void _sock_accept(event_loop& loop, std::promise<object>& prom, std::future<object>& fut, object sock)
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
    }
    catch (const error_already_set& e)
    {
        if (PyErr_ExceptionMatches(PyExc_BlockingIOError)
            || PyErr_ExceptionMatches(PyExc_InterruptedError))
        {
            PyErr_Clear();
            loop.add_reader(fd, make_function(bind(
                _sock_accept, boost::ref(loop), boost::ref(prom), boost::ref(fut), sock),
                default_call_policies(), boost::mpl::vector<void, object>()));
        }
        else if (PyErr_ExceptionMatches(PyExc_SystemExit)
            || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
        {
            // raise
        }
        else if (PyErr_ExceptionMatches(PyExc_BaseException))
        {
            PyErr_Clear();
            prom.set_exception(std::current_exception());
        }
        else
        {
            PyErr_Clear();
            prom.set_value(make_tuple(conn, address));
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
    // add timer
    _id_to_timer_map.emplace(_timer_id,
        std::move(std::make_unique<boost::asio::steady_timer>(_strand.context(),
            std::chrono::steady_clock::now() + std::chrono::nanoseconds(int64_t(delay * 1e9))))
    );

    _id_to_timer_map.find(_timer_id)->second->async_wait(
        // remove timer
        boost::asio::bind_executor(_strand, [id=_timer_id, f, loop=this] (const boost::system::error_code& ec)
        {
            loop->_id_to_timer_map.erase(id);
            loop->call_soon(f);
        }));
    _timer_id++;
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
    std::promise<std::vector<char>> prom_data;
    std::future<std::vector<char>> fut_data = prom_data.get_future();
    std::promise<size_t> prom_nbytes_read;
    std::future<size_t> fut_nbytes_read = prom_nbytes_read.get_future();
    add_reader(fd, make_function(bind(_sock_recv_handler, 
        boost::ref(prom_data), boost::ref(prom_nbytes_read), nbytes, fd), 
        default_call_policies(), boost::mpl::vector<void, object>()));
    return object(handle<>(PyBytes_FromStringAndSize(fut_data.get().data(), nbytes)));
}

size_t event_loop::sock_recv_into(object sock, object buffer)
{
    int fd = extract<int>(sock.attr("fileno")());
    ssize_t nbytes = len(buffer);
    std::promise<std::vector<char>> prom_data;
    std::future<std::vector<char>> fut_data = prom_data.get_future();
    std::promise<size_t> prom_nbytes_read;
    std::future<size_t> fut_nbytes_read = prom_nbytes_read.get_future();
    add_reader(fd, make_function(bind(_sock_recv_handler, 
        boost::ref(prom_data), boost::ref(prom_nbytes_read), nbytes, fd), 
        default_call_policies(), boost::mpl::vector<void, object>()));
    buffer = object(handle<>(PyBytes_FromStringAndSize(fut_data.get().data(), nbytes)));
    return fut_nbytes_read.get();
}

object event_loop::sock_sendall(object sock, object data)
{
    int fd = extract<int>(sock.attr("fileno")());
    char const* py_str = extract<char const*>(data.attr("decode")());
    ssize_t py_str_len = len(data);
    std::promise<size_t> prom;
    std::future<size_t> fut = prom.get_future();
    add_writer(fd, make_function(bind(_sock_send_handler, std::ref(prom), fd, py_str, py_str_len), 
        default_call_policies(), boost::mpl::vector<void, object>()));
    fut.wait();
    return object();
}

void event_loop::sock_connect(object sock, object address)
{
    
    if (!_hasattr(_pymod_socket, "AF_UNIX") || sock.attr("family") != _pymod_socket.attr("AF_UNIX"))
    {
        // TODO: _ensure_resolve
    }
    std::promise<void> prom;
    std::future<void> fut = prom.get_future();
    int fd = extract<int>(sock.attr("fileno")());
    try 
    {
        sock.attr("connect")(address);
    }
    catch (const error_already_set& e)
    {
        if (PyErr_ExceptionMatches(PyExc_BlockingIOError)
            || PyErr_ExceptionMatches(PyExc_InterruptedError))
        {
            PyErr_Clear();
            add_writer(fd, make_function(bind(
                _sock_connect_cb, _pymod_socket, boost::ref(prom), boost::ref(fut), sock, address),
                default_call_policies(), boost::mpl::vector<void, object>()));
        }
        else if (PyErr_ExceptionMatches(PyExc_SystemExit)
            || PyErr_ExceptionMatches(PyExc_KeyboardInterrupt))
        {
            // raise
        }
        else if (PyErr_ExceptionMatches(PyExc_BaseException))
        {
            PyErr_Clear();
            prom.set_exception(std::current_exception());
        }
        else
        {
            PyErr_Clear();
            prom.set_value();
        }
    }
    fut.wait();
}

object event_loop::sock_accept(object sock)
{
    std::promise<object> prom;
    std::future<object> fut = prom.get_future();
    _sock_accept(*this, prom, fut, sock);
    return fut.get();
}

// TODO: implement this
void event_loop::sock_sendfile(object sock, object file, int offset, int count, bool fallback)
{
    PyErr_SetString(PyExc_NotImplementedError, "Not implemented!");
}

}}}