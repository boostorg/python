// Based on wrapVector.hh by Mike Owen and Jeff Johnson.
// http://cvs.sourceforge.net/cgi-bin/viewcvs.cgi/spheral/src/src/BPLWraps/CXXWraps/

#ifndef BOOST_PYTHON_EXAMPLE_VECTOR_WRAPPER_H
#define BOOST_PYTHON_EXAMPLE_VECTOR_WRAPPER_H

#include <boost/python/class_builder.hpp>

namespace example {

  // A wrapper is used to define additional constructors. This wrapper
  // is templated on the template parameter for its corresponding vector.
  template <typename T>
  struct vector_wrapper: std::vector<T>
  {
    // Tell the compiler how to convert a base class object to
    // this wrapper object.
    vector_wrapper(PyObject*,
                  const std::vector<T>& vec):
      std::vector<T>(vec) {}

    vector_wrapper(PyObject* self):
      std::vector<T>() {}

    vector_wrapper(PyObject* self,
                   std::size_t n):
      std::vector<T>(n) {}

    vector_wrapper(PyObject* self,
                   boost::python::tuple tuple):
      std::vector<T>(tuple.size())
    {
      std::vector<T>::iterator vec = begin();
      for (std::size_t i = 0; i < tuple.size(); i++)
        vec[i] = BOOST_PYTHON_CONVERSION::from_python(tuple[i].get(),
                                            boost::python::type<T>());
    }
  };

  void raise_vector_IndexError() {
    PyErr_SetString(PyExc_IndexError, "vector index out of range");
    boost::python::throw_error_already_set();
  }

  template <typename T>
  struct vector_access
  {
    static
    T
    getitem(const std::vector<T>& vec,
            std::size_t key)
    {
      if (key >= vec.size()) raise_vector_IndexError();
      return vec[key];
    }

    static
    void
    setitem(std::vector<T>& vec,
            std::size_t key,
            const T &value)
    {
      if (key >= vec.size()) raise_vector_IndexError();
      vec[key] = value;
    }

    static
    void
    delitem(std::vector<T>& vec,
            std::size_t key)
    {
      if (key >= vec.size()) raise_vector_IndexError();
      vec.erase(vec.begin() + key);
    }

    // Convert vector<T> to a regular Python tuple.
    static
    boost::python::tuple
    as_tuple(const std::vector<T>& vec)
    {
      // Create a python type of size vec.size().
      boost::python::tuple t(vec.size());
      for (std::size_t i = 0; i < vec.size(); i++) {
        t.set_item(i,
          boost::python::ref(BOOST_PYTHON_CONVERSION::to_python(vec[i])));
      }
      return t;
    }
  };

  // This function will build a vector<T> and add it to the given
  // module with the given name.
  template <typename T>
  boost::python::class_builder<std::vector<T>, vector_wrapper<T> >
  wrap_vector(boost::python::module_builder& module,
              const std::string& vector_name,
              const T&)
  {
    // Add the vector<T> to the module.
    boost::python::class_builder<std::vector<T>, vector_wrapper<T> >
    py_vector(module, vector_name.c_str());

    // Define constructors and methods for the vector<T>.
    py_vector.def(boost::python::constructor<>());
    py_vector.def(boost::python::constructor<std::size_t>());
    py_vector.def(boost::python::constructor<boost::python::tuple>());
    py_vector.def(&std::vector<T>::size, "__len__");
    py_vector.def(&vector_access<T>::getitem, "__getitem__");
    py_vector.def(&vector_access<T>::setitem, "__setitem__");
    py_vector.def(&vector_access<T>::delitem, "__delitem__");
    py_vector.def(&vector_access<T>::as_tuple, "as_tuple");

    return py_vector;
  }
}

#endif // BOOST_PYTHON_EXAMPLE_VECTOR_WRAPPER_H
