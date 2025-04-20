// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python/module.hpp>
#include <boost/python/scope.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE_MULTI_PHASE(module_multi_phase_ext)
{
    scope().attr("x") = "x";
}

#include "module_tail.cpp"
