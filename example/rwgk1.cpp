#include <string>

namespace { // Avoid cluttering the global namespace.

  // A couple of simple C++ functions that we want to expose to Python.
  std::string greet() { return "hello, world"; }
  int square(int number) { return number * number; }
}

#include <boost/python/class_builder.hpp>

namespace python = boost::python;

// Python requires an exported function called init<module-name> in every
// extension module. This is where we build the module contents.
extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
initrwgk1()
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("rwgk1");

    // Add regular functions to the module.
    this_module.def(greet, "greet");
    this_module.def(square, "square");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}

// Win32 DLL boilerplate
#if defined(_WIN32)
#include <windows.h>
extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID) { return 1; }
#endif // _WIN32
