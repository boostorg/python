#include "boost/python/module_builder.hpp"
#include "boost/python/class_builder.hpp"
#include "shared.hpp"
#include "Python.h"

struct M1 : Shared
{
    char const * name() const { return "M1"; }
};

namespace py = boost::python;

char const * test(Shared const & m)
{
    return m.name();
}

extern "C" void initm1()
{
    try {
        py::module_builder m1("m1");


        py::class_builder<M1> m1_class(m1, "M1");
        m1_class.def(py::constructor<>());
        
        try {
            m1_class.declare_base(py::type<Shared>());
        }
        catch(std::runtime_error & )
        {
            throw std::runtime_error("You must load module `shared' before module `m1'");
        }

        m1.def(&test, "test");
    }
    catch(...)
    {
        py::handle_exception();
    }
}
