# include <boost/python/detail/import_extension_class.hpp>
namespace python = boost::python;
# include <stdio.h> // MSVC6.0SP4 does not know std::fprintf
# include <string.h> // MSVC6.0SP4 does not know std::strcmp

namespace {

  PyObject *get_module_dict(const char *module_name)
  {
    python::ref module_obj(PyImport_ImportModule((char*) module_name));
    PyObject *module_dict = PyModule_GetDict(module_obj.get());
    if (module_dict == 0) throw python::import_error();
    return module_dict;
  }
}

namespace boost { namespace python { namespace detail {

#ifndef SPECIAL_PYCVTSOBJECT

void *import_converters(const std::string& module_name,
                        const std::string& klass_name,
                        const std::string& attribute_name)
{
  static std::string err;
  PyObject *module_dict
    = get_module_dict(const_cast<char*>(module_name.c_str()));
  PyObject *klass
    = PyDict_GetItemString(module_dict, const_cast<char*>(klass_name.c_str()));
  if (klass == 0) {
    err = std::string("module ") + module_name + " has no attribute "
          + klass_name;
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
    throw python::import_error();
  }
  python::ref c_obj(PyObject_GetAttrString(klass,
    const_cast<char*>(attribute_name.c_str())), ref::null_ok);
  if (c_obj.get() == 0) {
    err = std::string("object ") + module_name + "." + klass_name
          + " has no attribute " + attribute_name;
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
    throw python::import_error();
  }
  if (! PyCObject_Check(c_obj.get())) {
    err = std::string("object ") + module_name + "." + klass_name + "."
          + attribute_name + " is not a PyCObject";
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
    throw python::import_error();
  }
  return PyCObject_AsVoidPtr(c_obj.get());
}

#else

PyObject *new_import_converters(const std::string& module_name,
                                const std::string& klass_name,
                                const std::string& attribute_name)
{
  static std::string err;
  PyObject *module_dict
    = get_module_dict(const_cast<char*>(module_name.c_str()));
  PyObject *klass
    = PyDict_GetItemString(module_dict, const_cast<char*>(klass_name.c_str()));
  if (klass == 0) {
    err = std::string("module ") + module_name + " has no attribute "
          + klass_name;
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
    throw python::import_error();
  }
  python::ref cvts_obj(PyObject_GetAttrString(klass,
    const_cast<char*>(attribute_name.c_str())), ref::null_ok);
  if (cvts_obj.get() == 0) {
    err = std::string("object ") + module_name + "." + klass_name
          + " has no attribute " + attribute_name;
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
    throw python::import_error();
  }
  // Weak point: direct access to ob_type->tp_name
  if (strcmp(cvts_obj->ob_type->tp_name, "PyCvtsObject") != 0) {
    err = std::string("object ") + module_name + "." + klass_name + "."
          + attribute_name + " is not a PyCvtsObject";
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
    throw python::import_error();
  }
  return cvts_obj.release();
}

#endif // SPECIAL_PYCVTSOBJECT

void check_export_converters_api(const int importing_major,
                                 const int importing_minor,
                                 const int imported_major,
                                 const int imported_minor)
{
  if (importing_major != imported_major) {
    // Python uses fprintf(stderr, ...) for API warnings.
    fprintf(stderr,
      "Fatal: EXPORT_CONVERTERS_API mismatch:"
      " Importing module = %d.%d"
      " Imported module = %d.%d\n",
      importing_major, importing_minor,
      imported_major, imported_minor);
    PyErr_SetString(PyExc_RuntimeError,
      "Fatal: EXPORT_CONVERTERS_API mismatch");
    throw import_error();
  }
  if (importing_minor != imported_minor) {
    // Python uses fprintf(stderr, ...) for API warnings.
    fprintf(stderr,
      "Warning: EXPORT_CONVERTERS_API mismatch:"
      " Importing module = %d.%d"
      " Imported module = %d.%d\n",
      importing_major, importing_minor,
      imported_major, imported_minor);
  }
}

}}} // namespace boost::python::detail
