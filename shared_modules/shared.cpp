#include "boost/python/module_builder.hpp"
#include "boost/python/class_builder.hpp"
#include "shared.hpp"

namespace py = boost::python;

char const * test(Shared const & m)
{
    return m.name();
}

extern "C" void initshared()
{
    py::module_builder shared("shared");
    py::class_builder<Shared> shared_class(shared, "Shared");
    shared_class.def(py::constructor<>());
    shared_class.def(&Shared::name, "name");
    shared.def(&test, "test");
}
