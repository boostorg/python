// Example by Ralf W. Grosse-Kunstleve
// This example shows how to use rich comparisons for a type that
// does not support all six operators (<, <=, ==, !=, >, >=).
// To keep the example simple, we are using a "code" type does
// not really require rich comparisons. __cmp__ would be sufficient.
// However, with a more complicated type the main point of this
// example would be in danger of getting lost.

#include <boost/python/class_builder.hpp>

namespace {

  // suppose operator< and operator> are not meaningful for code
  class code {
    public:
      code(int c = 0) : m_code(c) {}
      inline friend bool operator==(const code& lhs, const code& rhs) {
        return lhs.m_code == rhs.m_code;
      }
      inline friend bool operator!=(const code& lhs, const code& rhs) {
        return lhs.m_code != rhs.m_code;
      }
    private:
      int m_code;
  };

  boost::python::ref
  NotImplemented(const code&, const code&) {
    return
    boost::python::ref(Py_NotImplemented, boost::python::ref::increment_count);
  }
}

namespace {

  void init_module(boost::python::module_builder& this_module)
  {
    boost::python::class_builder<code> py_code(this_module, "code");

    py_code.def(boost::python::constructor<>());
    py_code.def(boost::python::constructor<int>());
    py_code.def(boost::python::operators<(  boost::python::op_eq
                                          | boost::python::op_ne)>());
    py_code.def(NotImplemented, "__lt__");
    py_code.def(NotImplemented, "__le__");
    py_code.def(NotImplemented, "__gt__");
    py_code.def(NotImplemented, "__ge__");
  }

} // namespace <anonymous>

BOOST_PYTHON_MODULE_INIT(richcmp2)
{
  try {
    boost::python::module_builder this_module("richcmp2");
    // The actual work is done in a separate function in order
    // to suppress a bogus VC60 warning.
    init_module(this_module);
  }
  catch (...) { boost::python::handle_exception(); }
}
