// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.


#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/return_value_policy.hpp>

class Bar { int x; }

class Foo
{
 public:
    Foo(int x) : b(x) {}
    Bar const& get_bar() const { return b; }
 private:
    Bar b;
};

using namespace boost::python;
BOOST_PYTHON_MODULE_INIT(my_module)
{
    module m("my_module")
        .add(
            class_<Bar>()
            )
        .add(
            class_<Foo>()
                .def_init(args<int>())
                .def("get_bar", &Foo::get_bar
                     , return_value_policy<copy_const_reference>())
            )
}

using namespace boost::python;
ref foo =
class_<Foo,bases<Bar,Baz> >()
    .def_init(args<int,char const*>())
    .def_init(args<double>())
    .def("get_name", &Foo::get_name, return_internal_reference<>())
    .def("set_name", &Foo::set_name)
    .object();


<blockquote><pre>
#include &lt;string&gt;
#include &lt;boost/python/errors.hpp&gt;
#include &lt;boost/python/reference.hpp&gt;

// Returns a std::string which has the same value as obj's "__name__"
// attribute.
std::string get_name(boost::python::ref obj)
{
    // throws if there's no __name__ attribute
    PyObject* p = boost::python::expect_non_null(
        PyObject_GetAttrString(obj.get(), "__name__"));

    // throws if it's not a Python string
    std::string result(
        boost::python::expect_non_null(
            PyString_AsString(p)));

    Py_XDECREF(p); // Done with p
    
    return result;
}

//
// Demonstrate form 1 of handle_exception
//

// Place a Python Int object whose value is 1 if a and b have
// identical "__name__" attributes, 0 otherwise.
void same_name_impl(PyObject*&amp; result, PyObject* a, PyObject* b)
{
    result = PyInt_FromLong(
        get_name(boost::python::ref(a1)) == get_name(boost::python::ref(a2)));
}

// This is an example Python 'C' API interface function
extern "C" PyObject*
same_name(PyObject* args, PyObject* keywords)
{
    PyObject* a1;
    PyObject* a2;
    PyObject* result = 0;

    if (!PyArg_ParseTuple(args, const_cast&lt;char*&gt;("OO"), &amp;a1, &amp;a2))
        return 0;
    
    // Use boost::bind to make an object compatible with
    // boost::Function0&lt;void&gt;
    if (boost::python::handle_exception(
            boost::bind&lt;void&gt;(same_name_impl, boost::ref(result), a1, a2)))
    {
        // an exception was thrown; the Python error was set by
        // handle_exception()
        return 0;
    }

    return result;
}

//
// Demonstrate form 2 of handle_exception. Not well-supported by all
// compilers.
//
extern "C" PyObject*
same_name2(PyObject* args, PyObject* keywords)
{
    PyObject* a1;
    PyObject* a2;
    PyObject* result = 0;

    if (!PyArg_ParseTuple(args, const_cast&lt;char*&gt;("OO"), &amp;a1, &amp;a2))
        return 0;
    try {
        return PyInt_FromLong(
            get_name(boost::python::ref(a1)) == get_name(boost::python::ref(a2)));
    }
    catch(...)
    {
        // If an exception was thrown, translate it to Python
        boost::python::handle_exception();
        return 0;
    }
}

</pre></blockquote>


template <class T>
struct from_python
{
    from_python(PyObject*);
    bool convertible() const;
    X operator()(PyObject*) const;
};
