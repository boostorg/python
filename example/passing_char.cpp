#include <iostream>

namespace { // Avoid cluttering the global namespace.

  // In C++, char, signed char and unsigned char are three distinct types.
  // The Boost Python Library maps signed & unsigned char to
  // Python integers. Plain char is mapped to a Python string with
  // exactly one character.

  // Plain char.
  char get_char() { return 'ÿ'; }
  void use_char(char c) {
    std::cout << c << std::endl;
  }

  // signed char.
  signed char get_signed_char() { return -128; }
  void use_signed_char(signed char c) {
    std::cout << c << " " << static_cast<int>(c) << std::endl;
  }

  // unsigned char.
  unsigned char get_unsigned_char() { return 128; }
  void use_unsigned_char(unsigned char c) {
    std::cout << c << " " << static_cast<unsigned int>(c) << std::endl;
  }
}

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

extern "C"
DL_EXPORT(void)
initpassing_char()
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("passing_char");

    this_module.def(get_char, "get_char");
    this_module.def(use_char, "use_char");
    this_module.def(get_signed_char, "get_signed_char");
    this_module.def(use_signed_char, "use_signed_char");
    this_module.def(get_unsigned_char, "get_unsigned_char");
    this_module.def(use_unsigned_char, "use_unsigned_char");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
