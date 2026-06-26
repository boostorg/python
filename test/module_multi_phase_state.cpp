// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python/def.hpp>
#include <boost/python/import.hpp>
#include <boost/python/module.hpp>

using namespace boost::python;

struct TestState
{
    int x;
};

int get_state_x() {
    TestState* state = reinterpret_cast<TestState*>(PyModule_GetState(import("module_multi_phase_state_ext").ptr()));
    if (state != nullptr) {
        return state->x;
    }
    return -1;
}

BOOST_PYTHON_MODULE_WITH_STATE(module_multi_phase_state_ext, TestState)
{
    state->x = 42;
    def("x", get_state_x);
}

#include "module_tail.cpp"
