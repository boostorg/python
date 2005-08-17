// Copyright Stefan Seefeld 2005.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python.hpp>
#include <iostream>

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
  virtual std::string hello() { return "Hello from C++!";}
};

// Familiar Boost.Python wrapper class for Base
struct BaseWrap : Base, python::wrapper<Base>
{
  virtual std::string hello() 
  {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    // workaround for VC++ 6.x or 7.0, see
    // http://boost.org/libs/python/doc/tutorial/doc/html/python/exposing.html#python.class_virtual_functions
    return python::call<std::string>(this->get_override("hello").ptr());
#else
    return this->get_override("hello")();
#endif
  }
};

// Pack the Base class wrapper into a module
BOOST_PYTHON_MODULE(embedded_hello)
{
  python::class_<BaseWrap, boost::noncopyable> base("Base");
}


void exec_test()
{
  // Register the module with the interpreter
  if (PyImport_AppendInittab("embedded_hello", initembedded_hello) == -1)
    throw std::runtime_error("Failed to add embedded_hello to the interpreter's "
			     "builtin modules");
  // Retrieve the main module
  python::object main = python::import("__main__");
  
  // Retrieve the main module's namespace
  python::object global(main.attr("__dict__"));

  // Define the derived class in Python.
  python::object result = python::exec(
    "from embedded_hello import *        \n"
    "class PythonDerived(Base):          \n"
    "    def hello(self):                \n"
    "        return 'Hello from Python!' \n",
    global, global);

  python::object PythonDerived = global["PythonDerived"];

  // Creating and using instances of the C++ class is as easy as always.
  CppDerived cpp;
  std::cout << cpp.hello() << std::endl;

  // But now creating and using instances of the Python class is almost
  // as easy!
  python::object py_base = PythonDerived();
  Base& py = python::extract<Base&>(py_base) BOOST_EXTRACT_WORKAROUND;
  std::cout << py.hello() << std::endl;
}

void exec_file_test()
{
  python::object main = python::import("__main__");
  python::dict global(main.attr("__dict__"));
  global.clear();
  python::object result = python::exec_file("exec.py", global, global);
  std::string global_as_string = python::extract<std::string>(python::str(global))
    BOOST_EXTRACT_WORKAROUND;
  std::cout << global_as_string << std::endl;
}

void exec_test_error()
{
  python::object main = python::import("__main__");
  python::dict global(main.attr("__dict__"));
  python::object result = python::exec("print unknown \n", global, global);
}

int main()
{
  bool success = true;
  // Initialize the interpreter
  Py_Initialize();

  if (python::handle_exception(exec_test) ||
      python::handle_exception(exec_file_test))
  {
    if (PyErr_Occurred()) PyErr_Print();
    else
    {
      std::cerr << "A C++ exception was thrown  for which "
		<< "there was no exception handler registered." << std::endl;
    }
    success = false;
  }
  if (python::handle_exception(exec_test_error))
  {
    if (PyErr_Occurred()) PyErr_Print();
    else
    {
      std::cerr << "A C++ exception was thrown  for which "
		<< "there was no exception handler registered." << std::endl;
      success = false;
    }
  }
  else success = false;

  // Boost.Python doesn't support Py_Finalize yet.
  // Py_Finalize();
  return success ? 0 : 1;
}

// Including this file makes sure
// that on Windows, any crashes (e.g. null pointer dereferences) invoke
// the debugger immediately, rather than being translated into structured
// exceptions that can interfere with debugging.
#include "module_tail.cpp"
