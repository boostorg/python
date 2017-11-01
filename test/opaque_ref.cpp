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

static union
{
    char x[sizeof(Opaque)];
    void* v;
}  pseudo_Opaque;

const Opaque& get() { return *reinterpret_cast<const Opaque*> (&pseudo_Opaque); }

void use(const Opaque& op)
{
    if (&op != reinterpret_cast<const Opaque*> (&pseudo_Opaque))
        throw std::runtime_error (std::string ("failed"));
}

int useany(const Opaque& op)
{
    return &op ? 1 : 0;
}

void failuse (const Opaque& op)
{
    if (&op == reinterpret_cast<const Opaque*> (&pseudo_Opaque))
        throw std::runtime_error (std::string ("success"));
}

namespace bpl = boost::python;

BOOST_PYTHON_MODULE(opaque_ref_ext)
{
    bpl::def (
        "get", &::get, bpl::return_value_policy<bpl::reference_existing_object>());
    bpl::def ("use", &::use);
    bpl::def ("useany", &::useany);
    bpl::def ("failuse", &::failuse);
}

# include "module_tail.cpp"
