// Example by Ullrich Koethe
#include "boost/python/class_builder.hpp"
#include <string>

struct Abstract
{
    virtual std::string test() = 0;
};

struct Abstract_callback: Abstract
{
    Abstract_callback(PyObject * self)
    : m_self(self)
    {}

    std::string test()
    {
      return boost::python::callback<std::string>::call_method(m_self, "test");
    }

    PyObject * m_self;
};

extern "C"
DL_EXPORT(void)
initabstract()
{
    boost::python::module_builder a("abstract");

    boost::python::class_builder<Abstract, Abstract_callback>
        a_class(a, "Abstract");
    a_class.def(boost::python::constructor<>()); // wrap a constructor
    a_class.def(&Abstract::test, "test");
}
