// -*- mode:c++ -*-
//
// Header file workaround.hpp
//
// Indexing-specific workarounds for compiler problems.
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/21   rmg     File creation
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_WORKAROUND_HPP
#define BOOST_PYTHON_INDEXING_WORKAROUND_HPP

#include <boost/detail/workaround.hpp>

# if (BOOST_WORKAROUND (__GNUC__, < 3))
#   // gcc versions before 3 (like 2.95.3) don't have the "at" member
#   // function in std::vector or std::deque
#   define BOOST_INDEXING_AT operator[]
# else
#   define BOOST_INDEXING_AT at
# endif

#endif // BOOST_PYTHON_INDEXING_WORKAROUND_HPP
