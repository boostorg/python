// Copyright Pan Yue 2021.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
// 1. posix::stream_descriptor need windows version
// 2. call_* need return async.Handle

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/python.hpp>
#include <boost/python/eventloop.hpp>


namespace boost { namespace python { namespace asio {

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

void event_loop::sock_recv(object sock, int bytes)
{

}

void event_loop::sock_recv_into(object sock, object buffer)
{

}

void event_loop::sock_sendall(object sock, object data)
{

}

void event_loop::sock_connect(object sock, object address)
{

}

void event_loop::sock_accept(object sock)
{

}

void event_loop::sock_sendfile(object sock, object file, int offset, int count, bool fallback)
{

}

}}}