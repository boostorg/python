// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef CHAR_ARRAY_DWA2002129_HPP
# define CHAR_ARRAY_DWA2002129_HPP

namespace boost { namespace python { namespace detail { 

// This little package is used to transmit the number of arguments
// from the helper functions below to the sizeof() expression below.
// Because we can never have an array of fewer than 1 element, we
// add 1 to n and then subtract 1 from the result of sizeof() below.
template <int n>
struct char_array
{
    char elements[n+1];
};

}}} // namespace boost::python::detail

#endif // CHAR_ARRAY_DWA2002129_HPP
