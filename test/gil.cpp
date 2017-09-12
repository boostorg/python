// Copyright John Zwinck 2012.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/gil.hpp>

int main()
{
    {
        // test building a guard without Python threads initialized
        // this isn't a common thing to do, but we do support it "just in case"
        boost::python::gil_guard_release release1;
    }

    {
        Py_InitializeEx(false);
        boost::python::gil_guard_release release2;
        boost::python::gil_guard_release release3; // should do nothing
        boost::python::gil_guard_acquire acquire1; // re-acquires the lock
        boost::python::gil_guard_acquire acquire2; // should do nothing
    }
}
