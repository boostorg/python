#ifndef SHARED_HPP
#define SHARED_HPP

#include "boost/python/module_builder.hpp"
#include "boost/python/class_builder.hpp"

struct Shared
{
    virtual char const * name() const { return "Shared"; }
};


char const * test(Shared const & m);

struct DefineFromPythonForShared
: python_extension_class_converters<Shared>
{};

#endif /* SHARED_HPP */
