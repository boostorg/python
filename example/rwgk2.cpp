#include <iostream>
#include <string>

namespace { // Avoid cluttering the global namespace.

  // A friendly class.
  class world
  {
    private:
      std::string country;
    public:
      world(const std::string& country) { this->country = country; }
      std::string greet() const { return "Hello from " + country + "!"; }
  };

  // A function taking a world object as an argument.
  std::string invite(const world& w) {
    return w.greet() + " Please come soon!";
  }
}

#include <py_cpp/class_wrapper.h>

// Python requires an exported function called init<module-name> in every
// extension module. This is where we build the module contents.
BOOST_PYTHON_MODULE_INIT(example2)
{
    // Create an object representing this extension module.
    py::Module this_module("example2");

    // Create the Python type object for our extension class.
    py::ClassWrapper<world> world_class(this_module, "world");

    // Add the __init__ function.
    world_class.def(py::Constructor<std::string>());
    // Add a regular member function.
    world_class.def(&world::greet, "greet");

    // Add invite() as a regular function to the module.
    this_module.def(invite, "invite");

    // Even better, invite() can also be made a member of world_class!!!
    world_class.def(invite, "invite");
}

// Win32 DLL boilerplate
#if defined(_WIN32)
#include <windows.h>
extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID) { return 1; }
#endif // _WIN32
