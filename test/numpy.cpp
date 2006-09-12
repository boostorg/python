// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python/numeric.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

using namespace boost::python;

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
# define make_tuple boost::python::make_tuple
#endif 

// See if we can invoke array() from C++
object new_array()
{
    return numeric::array(
        make_tuple(
            make_tuple(1,2,3)
          , make_tuple(4,5,6)
          , make_tuple(7,8,9)
            )
        );
}

// test argument conversion
void take_array(numeric::array /*x*/)
{
}

// A separate function to invoke the info() member. Must happen
// outside any doctests since this prints directly to stdout and the
// result text includes the address of the 'self' array.
void info(numeric::array const& z)
{
    z.info();
}

#define CHECK(expr)                                                         \
{                                                                           \
    object result;                                                          \
    try { result = object(expr); }                                          \
    catch(error_already_set)                                                \
    {                                                                       \
        PyObject* type, *value, *traceback;                                 \
        PyErr_Fetch(&type, &value, &traceback);                             \
        handle<> ty(type), v(value), tr(traceback);                         \
        str format("exception type: %s\n");                                 \
        format += "exception value: %s\n";                                  \
        format += "traceback:\n%s" ;                                        \
        result = format % boost::python::make_tuple(ty, v, tr);             \
    }                                                                       \
    check(result);                                                          \
}

// Tests which work on both Numeric and numarray array objects. Of
// course all of the operators "just work" since numeric::array
// inherits that behavior from object.
void exercise(numeric::array& y, object check)
{
    y[make_tuple(2,1)] = 3;
    CHECK(y);
    CHECK(y.astype('D'));
    CHECK(y.copy());
    CHECK(y.typecode());
}

// numarray-specific tests.  check is a callable object which we can
// use to record intermediate results, which are later compared with
// the results of corresponding python operations.
void exercise_numarray(numeric::array& y, object check)
{
    CHECK(y.astype());
    
    CHECK(y.argmax());
    CHECK(y.argmax(0));
    
    CHECK(y.argmin());
    CHECK(y.argmin(0));
    
    CHECK(y.argsort());
    CHECK(y.argsort(1));

    y.byteswap();
    CHECK(y);
    
    CHECK(y.diagonal());
    CHECK(y.diagonal(1));
    CHECK(y.diagonal(0, 1));
    CHECK(y.diagonal(0, 1, 0));

    CHECK(y.is_c_array());
    CHECK(y.isbyteswapped());

    CHECK(y.trace());
    CHECK(y.trace(1));
    CHECK(y.trace(0, 1));
    CHECK(y.trace(0, 1, 0));

    CHECK(y.new_('D'));
    y.sort();
    CHECK(y);
    CHECK(y.type());

    CHECK(y.factory(make_tuple(1.2, 3.4)));
    CHECK(y.factory(make_tuple(1.2, 3.4), "Double"));
    CHECK(y.factory(make_tuple(1.2, 3.4), "Double", make_tuple(1,2,1)));
    CHECK(y.factory(make_tuple(1.2, 3.4), "Double", make_tuple(2,1,1), false));
    CHECK(y.factory(make_tuple(1.2, 3.4), "Double", make_tuple(2), true, true));
}

BOOST_PYTHON_MODULE(numpy_ext)
{
    def("new_array", new_array);
    def("take_array", take_array);
    def("exercise", exercise);
    def("exercise_numarray", exercise_numarray);
    def("set_module_and_type", &numeric::array::set_module_and_type);
    def("info", info);
}

#include "module_tail.cpp"
