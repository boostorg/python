//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_arg_tuple_size.python

#ifndef ARG_TUPLE_SIZE_DWA20011201_HPP
# define ARG_TUPLE_SIZE_DWA20011201_HPP

# include <boost/python/detail/char_array.hpp>

namespace boost { namespace python { namespace detail {

// Computes (at compile-time) the number of elements that a Python
// argument tuple must have in order to be passed to a wrapped C++
// (member) function of the given type.
template <class F> struct arg_tuple_size;

# if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(__BORLANDC__)

template <class R>
struct arg_tuple_size<R (*)()>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 0);
};

template <class R, class A1>
struct arg_tuple_size<R (*)(A1)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 1);
};

template <class R, class A1, class A2>
struct arg_tuple_size<R (*)(A1, A2)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 2);
};

template <class R, class A1, class A2, class A3>
struct arg_tuple_size<R (*)(A1, A2, A3)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 3);
};

template <class R, class A1, class A2, class A3, class A4>
struct arg_tuple_size<R (*)(A1, A2, A3, A4)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 4);
};

template <class R, class A1, class A2, class A3, class A4, class A5>
struct arg_tuple_size<R (*)(A1, A2, A3, A4, A5)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 5);
};

template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
struct arg_tuple_size<R (*)(A1, A2, A3, A4, A5, A6)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 6);
};


template <class R, class A0>
struct arg_tuple_size<R (A0::*)()>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 1);
};

template <class R, class A0, class A1>
struct arg_tuple_size<R (A0::*)(A1)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 2);
};

template <class R, class A0, class A1, class A2>
struct arg_tuple_size<R (A0::*)(A1, A2)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 3);
};

template <class R, class A0, class A1, class A2, class A3>
struct arg_tuple_size<R (A0::*)(A1, A2, A3)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 4);
};

template <class R, class A0, class A1, class A2, class A3, class A4>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 5);
};

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4, A5)>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 6);
};


// Metrowerks thinks this creates ambiguities
# if !defined(__MWERKS__) || __MWERKS__ > 0x2406

template <class R, class A0>
struct arg_tuple_size<R (A0::*)() const>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 1);
};

template <class R, class A0, class A1>
struct arg_tuple_size<R (A0::*)(A1) const>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 2);
};

template <class R, class A0, class A1, class A2>
struct arg_tuple_size<R (A0::*)(A1, A2) const>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 3);
};

template <class R, class A0, class A1, class A2, class A3>
struct arg_tuple_size<R (A0::*)(A1, A2, A3) const>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 4);
};

template <class R, class A0, class A1, class A2, class A3, class A4>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4) const>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 5);
};

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4, A5) const>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 6);
};


template <class R, class A0>
struct arg_tuple_size<R (A0::*)() volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 1);
};

template <class R, class A0, class A1>
struct arg_tuple_size<R (A0::*)(A1) volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 2);
};

template <class R, class A0, class A1, class A2>
struct arg_tuple_size<R (A0::*)(A1, A2) volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 3);
};

template <class R, class A0, class A1, class A2, class A3>
struct arg_tuple_size<R (A0::*)(A1, A2, A3) volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 4);
};

template <class R, class A0, class A1, class A2, class A3, class A4>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4) volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 5);
};

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4, A5) volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 6);
};


template <class R, class A0>
struct arg_tuple_size<R (A0::*)() const volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 1);
};

template <class R, class A0, class A1>
struct arg_tuple_size<R (A0::*)(A1) const volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 2);
};

template <class R, class A0, class A1, class A2>
struct arg_tuple_size<R (A0::*)(A1, A2) const volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 3);
};

template <class R, class A0, class A1, class A2, class A3>
struct arg_tuple_size<R (A0::*)(A1, A2, A3) const volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 4);
};

template <class R, class A0, class A1, class A2, class A3, class A4>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4) const volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 5);
};

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
struct arg_tuple_size<R (A0::*)(A1, A2, A3, A4, A5) const volatile>
{
    BOOST_STATIC_CONSTANT(std::size_t, value = 6);
};


# endif // __MWERKS__
# else

// We will use the "sizeof() trick" to work around the lack of
// partial specialization in MSVC6 and its broken-ness in borland.
// See http://opensource.adobe.com  or
// http://groups.yahoo.com/group/boost/message/5441 for
// more examples

// The following helper functions are never actually called, since
// they are only used within a sizeof() expression, but the type of
// their return value is used to discriminate between various free
// and member function pointers at compile-time.

template <class R>
char_array<0> arg_tuple_size_helper(R (*)());

template <class R, class A1>
char_array<1> arg_tuple_size_helper(R (*)(A1));

template <class R, class A1, class A2>
char_array<2> arg_tuple_size_helper(R (*)(A1, A2));

template <class R, class A1, class A2, class A3>
char_array<3> arg_tuple_size_helper(R (*)(A1, A2, A3));

template <class R, class A1, class A2, class A3, class A4>
char_array<4> arg_tuple_size_helper(R (*)(A1, A2, A3, A4));

template <class R, class A1, class A2, class A3, class A4, class A5>
char_array<5> arg_tuple_size_helper(R (*)(A1, A2, A3, A4, A5));

template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
char_array<6> arg_tuple_size_helper(R (*)(A1, A2, A3, A4, A5, A6));

template <class R, class A0>
char_array<1> arg_tuple_size_helper(R (A0::*)());

template <class R, class A0, class A1>
char_array<2> arg_tuple_size_helper(R (A0::*)(A1));

template <class R, class A0, class A1, class A2>
char_array<3> arg_tuple_size_helper(R (A0::*)(A1, A2));

template <class R, class A0, class A1, class A2, class A3>
char_array<4> arg_tuple_size_helper(R (A0::*)(A1, A2, A3));

template <class R, class A0, class A1, class A2, class A3, class A4>
char_array<5> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4));

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
char_array<6> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4, A5));


template <class R, class A0>
char_array<1> arg_tuple_size_helper(R (A0::*)() const);

template <class R, class A0, class A1>
char_array<2> arg_tuple_size_helper(R (A0::*)(A1) const);

template <class R, class A0, class A1, class A2>
char_array<3> arg_tuple_size_helper(R (A0::*)(A1, A2) const);

template <class R, class A0, class A1, class A2, class A3>
char_array<4> arg_tuple_size_helper(R (A0::*)(A1, A2, A3) const);

template <class R, class A0, class A1, class A2, class A3, class A4>
char_array<5> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4) const);

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
char_array<6> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4, A5) const);


template <class R, class A0>
char_array<1> arg_tuple_size_helper(R (A0::*)() volatile);

template <class R, class A0, class A1>
char_array<2> arg_tuple_size_helper(R (A0::*)(A1) volatile);

template <class R, class A0, class A1, class A2>
char_array<3> arg_tuple_size_helper(R (A0::*)(A1, A2) volatile);

template <class R, class A0, class A1, class A2, class A3>
char_array<4> arg_tuple_size_helper(R (A0::*)(A1, A2, A3) volatile);

template <class R, class A0, class A1, class A2, class A3, class A4>
char_array<5> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4) volatile);

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
char_array<6> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4, A5) volatile);


template <class R, class A0>
char_array<1> arg_tuple_size_helper(R (A0::*)() const volatile);

template <class R, class A0, class A1>
char_array<2> arg_tuple_size_helper(R (A0::*)(A1) const volatile);

template <class R, class A0, class A1, class A2>
char_array<3> arg_tuple_size_helper(R (A0::*)(A1, A2) const volatile);

template <class R, class A0, class A1, class A2, class A3>
char_array<4> arg_tuple_size_helper(R (A0::*)(A1, A2, A3) const volatile);

template <class R, class A0, class A1, class A2, class A3, class A4>
char_array<5> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4) const volatile);

template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
char_array<6> arg_tuple_size_helper(R (A0::*)(A1, A2, A3, A4, A5) const volatile);


template <class F>
struct arg_tuple_size
{
    // The sizeof() magic happens here
    BOOST_STATIC_CONSTANT(std::size_t, value
      = sizeof(arg_tuple_size_helper(F(0)).elements) - 1);
};
# endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}}} // namespace boost::python::detail

#endif // ARG_TUPLE_SIZE_DWA20011201_HPP

