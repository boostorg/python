#ifndef X_CLASS_BUILDER_HPP
# define X_CLASS_BUILDER_HPP

# include <boost/python/class_builder.hpp>

namespace boost { namespace python {
    struct import_error : error_already_set {};
    struct export_error : error_already_set {};
}}

namespace boost { namespace python { namespace detail {

// Concept: throw exception if api_major is changed
//          show warning on stderr if api_minor is changed
const int export_converters_api_major = 1;
const int export_converters_api_minor = 1;
extern const char* converters_attribute_name;
void* import_converters(const std::string& module_name,
                        const std::string& py_class_name,
                        const std::string& attribute_name);
void check_export_converters_api(const int importing_major,
                                 const int importing_minor,
                                 const int imported_major,
                                 const int imported_minor);

}}}

// forward declaration
namespace boost { namespace python { namespace detail {
template <class T> class import_extension_class;
}}}

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

//QUESTIONMARK
//  This class is a look-alike of class python_extension_class_converters.
//  Is there a way to ensure that the siblings stay in sync?
template <class T>
class python_import_extension_class_converters
{
 public:

    friend python_import_extension_class_converters py_extension_class_converters(boost::python::type<T>)
    {
        return python_import_extension_class_converters();
    }

    PyObject* to_python(const T& x) const
    {
        return boost::python::detail::import_extension_class<T>::get_converters()->to_python(x);
    }

    friend T* from_python(PyObject* obj, boost::python::type<T*>)
    {
        return boost::python::detail::import_extension_class<T>::get_converters()->Tptr_from_python(obj);
    }

    // Convert to const T*
    friend const T* from_python(PyObject* p, boost::python::type<const T*>)
        { return from_python(p, boost::python::type<T*>()); }

    // Convert to const T* const&
    friend const T* from_python(PyObject* p, boost::python::type<const T*const&>)
         { return from_python(p, boost::python::type<const T*>()); }

    // Convert to T* const&
    friend T* from_python(PyObject* p, boost::python::type<T* const&>)
         { return from_python(p, boost::python::type<T*>()); }

    // Convert to T&
    friend T& from_python(PyObject* p, boost::python::type<T&>)
        { return *boost::python::detail::check_non_null(from_python(p, boost::python::type<T*>())); }

    // Convert to const T&
    friend const T& from_python(PyObject* p, boost::python::type<const T&>)
        { return from_python(p, boost::python::type<T&>()); }

    // Convert to T
    friend const T& from_python(PyObject* p, boost::python::type<T>)
        { return from_python(p, boost::python::type<T&>()); }

  // *****************************************************************
  // THIS IS OUT OF SYNC WITH class python_extension_class_converters!
  // WE MIGHT NEED TO DEFINE MORE FUNCTIONS.
  // *****************************************************************
    friend std::auto_ptr<T>& from_python(PyObject* p, boost::python::type<std::auto_ptr<T>&>) {
        return boost::python::detail::import_extension_class<T>::get_converters()->auto_ptr_from_python(p);
    }

    friend std::auto_ptr<T>& from_python(PyObject* p, boost::python::type<std::auto_ptr<T> >) {
        return boost::python::detail::import_extension_class<T>::get_converters()->auto_ptr_from_python(p);
    }

    friend const std::auto_ptr<T>& from_python(PyObject* p, boost::python::type<const std::auto_ptr<T>&>) {
        return boost::python::detail::import_extension_class<T>::get_converters()->auto_ptr_from_python(p);
    }

    friend PyObject* to_python(std::auto_ptr<T> x) {
        return boost::python::detail::import_extension_class<T>::get_converters()->to_python(x);
    }

    friend boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<boost::shared_ptr<T>&>) {
        return boost::python::detail::import_extension_class<T>::get_converters()->shared_ptr_from_python(p);
    }

    friend boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<boost::shared_ptr<T> >) {
        return boost::python::detail::import_extension_class<T>::get_converters()->shared_ptr_from_python(p);
    }

    friend const boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<const boost::shared_ptr<T>&>) {
        return boost::python::detail::import_extension_class<T>::get_converters()->shared_ptr_from_python(p);
    }

    friend PyObject* to_python(boost::shared_ptr<T> x) {
        return boost::python::detail::import_extension_class<T>::get_converters()->to_python(x);
    }
};

BOOST_PYTHON_END_CONVERSION_NAMESPACE

namespace boost { namespace python {

BOOST_PYTHON_IMPORT_CONVERSION(python_import_extension_class_converters);

// A pointer to this class is exported/imported via the Python API.
// All functions are virtual. This is, what we really export/import
// is essentially just a pointer to a vtbl.
template <class T>
struct export_converters_base
{
  virtual const int get_api_major() const {
    return detail::export_converters_api_major; }
  virtual const int get_api_minor() const {
    return detail::export_converters_api_minor; }
  virtual PyObject* to_python(const T& x) = 0;
  virtual PyObject* to_python(std::auto_ptr<T> x) = 0;
  virtual PyObject* to_python(boost::shared_ptr<T> x) = 0;
  virtual T* Tptr_from_python(PyObject* obj) = 0;
  virtual std::auto_ptr<T>& auto_ptr_from_python(PyObject* obj) = 0;
  virtual boost::shared_ptr<T>& shared_ptr_from_python(PyObject* obj) = 0;
};

// Converters to be used if T is not copyable.
template <class T>
struct export_ptr_converters : export_converters_base<T>
{
  virtual PyObject* to_python(const T& x) {
    PyErr_SetString(PyExc_RuntimeError,
      "to_python(const T&) converter not exported");
    throw import_error();
  }
  virtual PyObject* to_python(std::auto_ptr<T> x) {
    return BOOST_PYTHON_CONVERSION::to_python(x);
  }
  virtual PyObject* to_python(boost::shared_ptr<T> x) {
    return BOOST_PYTHON_CONVERSION::to_python(x);
  }
  virtual T* Tptr_from_python(PyObject* obj) {
    return BOOST_PYTHON_CONVERSION::from_python(obj, boost::python::type<T*>());
  }
  // *****************************************************************
  // THIS IS OUT OF SYNC WITH class python_extension_class_converters!
  // WE MIGHT NEED TO DEFINE MORE FUNCTIONS.
  // *****************************************************************
  virtual std::auto_ptr<T>& auto_ptr_from_python(PyObject* obj) {
    return BOOST_PYTHON_CONVERSION::python_extension_class_converters<T>::smart_ptr_reference(obj, boost::python::type<std::auto_ptr<T> >());
  }
  virtual boost::shared_ptr<T>& shared_ptr_from_python(PyObject* obj) {
    return BOOST_PYTHON_CONVERSION::python_extension_class_converters<T>::smart_ptr_reference(obj, boost::python::type<boost::shared_ptr<T> >());
  }
};

// The addditional to_python() converter that can be used if T is copyable.
template <class T>
struct export_converters : export_ptr_converters<T>
{
  virtual PyObject* to_python(const T& x) {
    BOOST_PYTHON_CONVERSION::python_extension_class_converters<T> cv;
    return cv.to_python(x);
  }
};

namespace detail {

//QUESTIONMARK
//  A stripped-down, modified version of class extension_class.
//  Would it make sense to establish a formal relationship
//  between the two classes?
template <class T>
class import_extension_class
    : public python_import_extension_class_converters<T>
{
 public:
    inline import_extension_class(const char* module, const char* py_class) {
      m_module = module;
      m_py_class = py_class;
    }

    static boost::python::export_converters_base<T>* get_converters();

  private:
    static std::string m_module;
    static std::string m_py_class;
    static boost::python::export_converters_base<T>* imported_converters;
};

template <class T> std::string import_extension_class<T>::m_module;
template <class T> std::string import_extension_class<T>::m_py_class;
template <class T>
boost::python::export_converters_base<T>*
import_extension_class<T>::imported_converters = 0;

template <class T>
boost::python::export_converters_base<T>*
import_extension_class<T>::get_converters() {
  if (imported_converters == 0) {
    void* cobject
      = import_converters(m_module, m_py_class, converters_attribute_name);
    imported_converters
      = static_cast<boost::python::export_converters_base<T>*>(cobject);
    check_export_converters_api(
      export_converters_api_major,
      export_converters_api_minor,
      imported_converters->get_api_major(),
      imported_converters->get_api_minor());
  }
  return imported_converters;
}

}}} // namespace boost::python::detail

namespace boost { namespace python {

//QUESTIONMARK
//  A stripped-down, modified version of class class_builder.
//  Would it make sense to establish a formal relationship
//  between the two classes?
template <class T>
class import_class_builder
    : python_import_extension_class_converters<T>
{
 public:
    import_class_builder(const char* module, const char* py_class)
        : m_class(new detail::import_extension_class<T>(module, py_class))
    { }
 private:

    //QUESTIONMARK
    //reference<detail::import_extension_class<T> > m_class;
    boost::shared_ptr<detail::import_extension_class<T> > m_class;
};

}} // namespace boost::python

namespace boost { namespace python {

// A class_builder that exports the converter functions.
template <class T, class U = detail::held_instance<T>,
          class C = export_converters<T> >
class x_class_builder
    : public class_builder<T, U>
{
  private:
    static C export_cvts;

  public:
    x_class_builder(module_builder& module, const char* name)
        : class_builder<T, U>(module, name) {
    add(
      ref(PyCObject_FromVoidPtr(reinterpret_cast<void*>(&export_cvts), NULL)),
      detail::converters_attribute_name);
  }
};

template <class T, class U, class C>
C x_class_builder<T, U, C>::export_cvts;

//QUESTIONMARK
//  Is there a better way of making it easy for the end-user
//  to choose between x_class_builder and xptr_class_builder?
template <class T, class U = detail::held_instance<T>,
          class C = export_ptr_converters<T> >
class xptr_class_builder : public x_class_builder<T, U, C>
{
  public:
    xptr_class_builder(module_builder& module, const char* name)
        : x_class_builder<T, U, C >(module, name) { }
};

}} // namespace boost::python

#endif // X_CLASS_BUILDER_HPP
