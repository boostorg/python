#include <py_cpp/class_wrapper.h>
#include <py_cpp/objects.h>

#define rangei(n)          for (int i = 0; i < n; i++)

namespace { // Avoid cluttering the global namespace.

  // A wrapper is used to define additional constructors.
  //
  struct vector_double_wrapper: std::vector<double>
  {
    // Tell the compiler how to convert a base class object to
    // this wrapper object.
    vector_double_wrapper(PyObject*, const std::vector<double>& vd)
      : std::vector<double>(vd) {}

    vector_double_wrapper(PyObject* self)
      : std::vector<double>() {}

    vector_double_wrapper(PyObject* self, const int n)
      : std::vector<double>(n) {}

    vector_double_wrapper(PyObject* self, py::Tuple tuple)
      : std::vector<double>(tuple.size())
    {
      std::vector<double>::iterator vd = begin();
      rangei(tuple.size())
        vd[i] = from_python(tuple[i].get(), py::Type<double>()); // GCC BUG
    }
  };

  double getitem(const std::vector<double>& vd, const std::size_t key) {
    return vd[key];
  }

  void setitem(std::vector<double>& vd, const std::size_t key,
               const double &d) {
    std::vector<double>::iterator vditer = vd.begin();
    vditer[key] = d;
  }

  void delitem(std::vector<double>& vd, const std::size_t key) {
    std::vector<double>::iterator vditer = vd.begin();
    vd.erase(&vditer[key]);
  }

  // Convert vector_double to a regular Python tuple.
  //
  py::Tuple as_tuple(const std::vector<double>& vd)
  {
    py::Tuple t(vd.size());
    rangei(vd.size()) t.set_item(i, py::Ptr(py::to_python(vd[i]))); // GCC BUG
    return t;
  }

  // Function returning a vector_double object to Python.
  //
  std::vector<double> foo(const int n)
  {
    std::vector<double> vd(n);
    std::vector<double>::iterator vditer = vd.begin();
    rangei(n) vditer[i] = double(i);
    return vd;
  }

  // Same as foo(), but avoid copying on return.
  //
  std::auto_ptr<std::vector<double> > bar(const int n)
  {
    std::auto_ptr<std::vector<double> > vdptr(new std::vector<double>(n));
    std::vector<double>::iterator vditer = vdptr->begin();
    rangei(n) vditer[i] = double(10 * i);
    return vdptr;
  }
}

BOOST_PYTHON_MODULE_INIT(example3)
{
    py::Module this_module("example3");

    py::ClassWrapper<std::vector<double>, vector_double_wrapper>
      vector_double(this_module, "vector_double");

    vector_double.def(py::Constructor<>());
    vector_double.def(py::Constructor<const int>());
    vector_double.def(py::Constructor<py::Tuple>());
    vector_double.def(&std::vector<double>::size, "__len__");
    vector_double.def(getitem, "__getitem__");
    vector_double.def(setitem, "__setitem__");
    vector_double.def(delitem, "__delitem__");
    vector_double.def(as_tuple, "as_tuple");

    this_module.def(foo, "foo");
    this_module.def(bar, "bar");
}

// Win32 DLL boilerplate
#if defined(_WIN32)
#include <windows.h>
extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID) { return 1; }
#endif // _WIN32
