#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

using namespace boost::python;

struct X // a container element
{
    std::string s;
    X():s("default") {}
    X(std::string s):s(s) {}
    std::string repr() const { return s; }
    void reset() { s = "reset"; }
    void foo() { s = "foo"; }
    bool operator==(X const& x) const { return s == x.s; }
    bool operator!=(X const& x) const { return s != x.s; }
};

std::string x_value(X const& x)
{
    return "gotya " + x.s;
}

std::string
print_xmap_entry(std::pair<std::string const, X> const& e)
{
    std::string r;
    r += '(';
    r += e.first;
    r += ", ";
    r += e.second.s;
    r += ')';
    return r;
}

X&
get_xmap_entry(std::pair<std::string const, X>& e)
{
    return e.second;
}

BOOST_PYTHON_MODULE(map_indexing_suite_ext)
{    
    class_<X>("X")
        .def(init<>())
        .def(init<X>())
        .def(init<std::string>())
        .def("__repr__", &X::repr)
        .def("reset", &X::reset)
        .def("foo", &X::foo)
    ;

    def("x_value", x_value);
    implicitly_convertible<std::string, X>();
    
    class_<std::pair<std::string const, X> >("XMapEntry")
        .def("__repr__", &print_xmap_entry)
        .def("data", &get_xmap_entry, return_internal_reference<>())
    ;

    class_<std::map<std::string, X> >("XMap")
        .def(map_indexing_suite<std::map<std::string, X> >())
    ;
        
    // Compile check only...
    class_<std::map<int, int> >("IntMap")
        .def(map_indexing_suite<std::map<int, int> >())
    ;
}

