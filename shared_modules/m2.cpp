#include "boost/python/module_builder.hpp"
#include "boost/python/class_builder.hpp"
#include "shared.hpp"

struct M2 : Shared
{
    char const * name() const { return "M2"; }
};

namespace py = boost::python;

extern "C" void initm2()
{
    py::module_builder m2("m2");
    
    py::class_builder<M2> m2_class(m2, "M2");
    m2_class.def(py::constructor<>());
    m2_class.declare_base(py::type<Shared>());
}
