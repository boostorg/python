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
    event_loop(boost::asio::io_context& ctx): 
        _strand{ctx}, _created_time{std::chrono::steady_clock::now()}
    {
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


    void sock_recv(object sock, int bytes);

    void sock_recv_into(object sock, object buffer);

    void sock_sendall(object sock, object data);

    void sock_connect(object sock, object address);

    void sock_accept(object sock);
    
    void sock_sendfile(object sock, object file, int offset = 0, int count = 0, bool fallback = true);

private:
    int64_t _timer_id = 0;
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
