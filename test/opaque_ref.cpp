// Copyright David Abrahams and Gottfried Ganssauge 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
# include <boost/python/reference_existing_object.hpp>
# include <boost/python/def.hpp>
# include <boost/python/module.hpp>
# include <boost/python/return_value_policy.hpp>

/* This class is "opaque" in the sense that it is declared, but
 * we don't define it's members anywhere. */
struct Opaque
{
public:
    Opaque();
    ~Opaque();
};

void use(const Opaque& op)
{
    /* do nothing */
}

namespace bpl = boost::python;

BOOST_PYTHON_MODULE(opaque_ref_ext)
{
    bpl::def ("use", &::use);
}

# include "module_tail.cpp"
