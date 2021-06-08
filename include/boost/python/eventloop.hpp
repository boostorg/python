// Copyright Pan Yue 2021.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
// 1. posix::stream_descriptor need windows version
// 2. call_* need return async.Handle
# ifndef EVENT_LOOP_PY2021_H_
# define EVENT_LOOP_PY2021_H_

#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/python.hpp>

namespace a = boost::asio;
namespace c = std::chrono;
namespace py = boost::python;

namespace boost { namespace python { namespace eventloop {

class EventLoop
{
private:
    int64_t _timer_id = 0;
    a::io_context::strand _strand;
    std::unordered_map<int, std::unique_ptr<a::steady_timer>> _id_to_timer_map;
    // read: key = fd * 2 + 0, write: key = fd * 2 + 1
    std::unordered_map<int, std::unique_ptr<a::posix::stream_descriptor>> _descriptor_map;
    std::chrono::steady_clock::time_point _created_time;

    void _add_reader_or_writer(int fd, py::object f, int key);
    void _remove_reader_or_writer(int key);

public:
    EventLoop(a::io_context& ctx): 
        _strand{ctx}, _created_time{std::chrono::steady_clock::now()}
    {
    }

    // TODO: An instance of asyncio.Handle is returned, which can be used later to cancel the callback.
    inline void call_soon(py::object f)
    {
        _strand.post([f, loop=this] {
            f(boost::ref(*loop));
        });
        return;
    }

    // TODO: implement this
    inline void call_soon_thread_safe(py::object f) {};

    // Schedule callback to be called after the given delay number of seconds
    // TODO: An instance of asyncio.Handle is returned, which can be used later to cancel the callback.
    void call_later(double delay, py::object f);

    void call_at(double when, py::object f);

    inline double time()
    {
        return static_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - _created_time).count();
    }

    // week 2 ......start......

    inline void add_reader(int fd, py::object f)
    {
        _add_reader_or_writer(fd, f, fd * 2);
    }

    inline void remove_reader(int fd)
    {
        _remove_reader_or_writer(fd * 2);
    }

    inline void add_writer(int fd, py::object f)
    {
        _add_reader_or_writer(fd, f, fd * 2 + 1);
    }

    inline void remove_writer(int fd)
    {
        _remove_reader_or_writer(fd * 2 + 1);
    }


    void sock_recv(py::object sock, int bytes);

    void sock_recv_into(py::object sock, py::object buffer);

    void sock_sendall(py::object sock, py::object data);

    void sock_connect(py::object sock, py::object address);

    void sock_accept(py::object sock);
    
    void sock_sendfile(py::object sock, py::object file, int offset = 0, int count = 0, bool fallback = true);

    // week 2 ......end......

    void run() 
    {
        _strand.context().run();
    }
};


}}}


# endif
