// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

// This file just defines the rest of the tests that MSVC6 can't
// compile unless we break the file up. It's a hack, I'll admit...
#define BOOST_PYTHON_WRAP_MORE_BUILTIN_CONVERTERS
#include "test_builtin_converters.cpp"
