#include <string.h>

namespace hello {
  class world
  {
   public:
      world(int) {}
      ~world() {}
      const char* get() const { return "hi, world"; }
  };

  size_t length(const world& x) { return strlen(x.get()); }
}

#include <boost/python/class_builder.hpp>

// Python requires an exported function called init<module-name> in every
// extension module. This is where we build the module contents.
extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void inithello()
{
    try
    {
       // create an object representing this extension module
       boost::python::module_builder hello("hello");

       // Create the Python type object for our extension class
       boost::python::class_builder<hello::world> world_class(hello, "world");

       // Add the __init__ function
       world_class.def(boost::python::constructor<int>());
       // Add a regular member function
       world_class.def(&hello::world::get, "get");

       // Add a regular function to the module
       hello.def(hello::length, "length");
    }
    catch(...)
    {
       boost::python::handle_exception();    // Deal with the exception for Python
    }
}

// Win32 DLL boilerplate
#if defined(_WIN32)
#include <windows.h>
extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return 1;
}
#endif // _WIN32
