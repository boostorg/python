// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

// embedded_hello -- A simple Boost.Python embedding example -- by
// Dirk Gerrits

#include <iostream>
#include <boost/python.hpp>
#include <boost/scoped_ptr.hpp>

namespace python = boost::python;

// An abstract base class
class Base : public boost::noncopyable
{
public:
    virtual ~Base() {};

    virtual std::string hello() = 0;
};

// C++ derived class
class CppDerived : public Base
{
public:
    virtual ~CppDerived() {}
    
    std::string hello()
    {
        return "Hello from C++!";
    }
};

// Familiar Boost.Python wrapper class for Base
struct BaseWrap : public Base
{
    BaseWrap(PyObject* self_)
        : self(self_) {}

    std::string hello() { return python::call_method<std::string>(self, "hello"); }

    PyObject* self;
};

// Pack the Base class wrapper into a module
BOOST_PYTHON_MODULE(embedded_hello)
{
    python::class_<Base, BaseWrap, boost::noncopyable>("Base")
        ;

}


void test()
{
//- INITIALIZATION -----------------------------------------------------------//

    // Register the module with the interpreter
    PyImport_AppendInittab("embedded_hello", initembedded_hello);

    // Initialize the interpreter
    Py_Initialize();

    // Load the module
    PyObject* main_module    = PyImport_AddModule("__main__");
    PyObject* main_namespace = PyModule_GetDict(main_module);
    Py_INCREF(main_namespace);

    // Define the derived class in Python.
    // (You'll normally want to put this in a .py file.)
    PyObject* result = PyRun_String(
        "from embedded_hello import *        \n"
        "class PythonDerived(Base):          \n"
        "    def hello(self):                \n"
        "        return 'Hello from Python!' \n", 
        Py_file_input, main_namespace, main_namespace);
    Py_XDECREF(result);

    // Extract the raw Python object representing the just defined derived class
    python::handle<PyObject> class_ptr(PyRun_String("PythonDerived\n", Py_eval_input, 
                                                    main_namespace, main_namespace));

    // Wrap the raw Python object in a Boost.Python object using a handle
    python::object PythonDerived(class_ptr);

//- MAIN PROGRAM -------------------------------------------------------------//

    // Creating and using instances of the C++ class is as easy as always.
    CppDerived cpp;
    std::cout << cpp.hello() << std::endl;

    // But now creating and using instances of the Python class is just
    // as easy!
    python::object py_base = PythonDerived();
    Base& py = python::extract<Base&>(py_base)();
    std::cout << py.hello() << std::endl;
}

int main()
{
    if (python::handle_exception(test))
    {
        if (PyErr_Occurred())
            PyErr_Print();
        return 1;
    }
    return 0;
}
#include "module_tail.cpp"
