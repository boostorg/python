/* (C) Copyright Ralf W. Grosse-Kunstleve 2001. Permission to copy, use,
   modify, sell and distribute this software is granted provided this
   copyright notice appears in all copies. This software is provided
   "as is" without express or implied warranty, and with no claim as to
   its suitability for any purpose.

   Revision History:
     17 Apr 01 merged into boost CVS trunk (Ralf W. Grosse-Kunstleve)
*/

/* Implementation of Boost.Python cross-module support.
   See root/libs/python/doc/cross_module.html for details.
*/

#ifndef CROSS_MODULE_HPP
# define CROSS_MODULE_HPP

# include <boost/python/class_builder.hpp>

namespace boost { namespace python {
    struct import_error : error_already_set {};
    struct export_error : error_already_set {};
}}

namespace boost { namespace python { namespace detail {

// Concept: throw exception if api_major is changed
//          show warning on stderr if api_minor is changed
const int export_converters_api_major = 4;
const int export_converters_api_minor = 1;
extern const char* converters_attribute_name;
void* import_converter_object(const std::string& module_name,
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

/* This class template is instantiated by import_converters<T>.
   This class is a look-alike of class python_extension_class_converters.
   The converters in this class are wrappers that call converters
   imported from another module.
   To ensure that the dynamic loader resolves all symbols in the
   intended way, the signature of all friend functions is changed with
   respect to the original functions in class
   python_extension_class_converters by adding an arbitrary additional
   parameter with a default value, in this case "bool sig = false".
   See also: comments for class export_converter_object_base below.
 */
template <class T>
class python_import_extension_class_converters
{
 public:

    friend python_import_extension_class_converters py_extension_class_converters(boost::python::type<T>, bool sig = false) {
        return python_import_extension_class_converters();
    }

    PyObject* member_to_python(const T& x) const {
        return boost::python::detail::import_extension_class<T>::get_converters()->dispatcher_to_python(x);
    }

    friend T* from_python(PyObject* p, boost::python::type<T*> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_Ts(p, t);
    }
    friend const T* from_python(PyObject* p, boost::python::type<const T*> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_cTs(p, t);
    }
    friend const T* from_python(PyObject* p, boost::python::type<const T*const&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_cTscr(p, t);
    }
    friend T* from_python(PyObject* p, boost::python::type<T* const&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_Tscr(p, t);
    }
    friend T& from_python(PyObject* p, boost::python::type<T&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_Tr(p, t);
    }
    friend const T& from_python(PyObject* p, boost::python::type<const T&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_cTr(p, t);
    }
    friend const T& from_python(PyObject* p, boost::python::type<T> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_T(p, t);
    }

    friend std::auto_ptr<T>& from_python(PyObject* p, boost::python::type<std::auto_ptr<T>&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_aTr(p, t);
    }
    friend std::auto_ptr<T> from_python(PyObject* p, boost::python::type<std::auto_ptr<T> > t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_aT(p, t);
    }
    friend const std::auto_ptr<T>& from_python(PyObject* p, boost::python::type<const std::auto_ptr<T>&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_caTr(p, t);
    }
    friend PyObject* to_python(boost::python::semantics, std::auto_ptr<T> x, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->dispatcher_to_python(x);
    }

    friend boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<boost::shared_ptr<T>&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_sTr(p, t);
    }
    friend const boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<boost::shared_ptr<T> > t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_sT(p, t);
    }
    friend const boost::shared_ptr<T>& from_python(PyObject* p, boost::python::type<const boost::shared_ptr<T>&> t, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->from_python_csTr(p, t);
    }
    friend PyObject* to_python(boost::python::semantics, boost::shared_ptr<T> x, bool sig = false) {
        return boost::python::detail::import_extension_class<T>::get_converters()->dispatcher_to_python(x);
    }
};

BOOST_PYTHON_END_CONVERSION_NAMESPACE

namespace boost { namespace python {

/* This class template is instantiated by export_converters().
   A pointer to this class is exported/imported via the Python API.
   Using the Python API ensures maximum portability.
   All member functions are virtual. This is, what we export/import
   is essentially just a pointer to a vtbl.
   To work around a deficiency of Visual C++ 6.0, the name of each
   from_python() member functions is made unique by appending a few
   characters (derived in a ad-hoc manner from the corresponding type).
 */
template <class T>
struct export_converter_object_base
{
    virtual int get_api_major() const { return detail::export_converters_api_major; }
    virtual int get_api_minor() const { return detail::export_converters_api_minor; }

    virtual PyObject* dispatcher_to_python(const T& x) = 0;

    virtual T* from_python_Ts(PyObject* p, type<T*> t) = 0;
    virtual const T* from_python_cTs(PyObject* p, type<const T*> t) = 0;
    virtual const T* from_python_cTscr(PyObject* p, type<const T*const&> t) = 0;
    virtual T* from_python_Tscr(PyObject* p, type<T* const&> t) = 0;
    virtual T& from_python_Tr(PyObject* p, type<T&> t) = 0;
    virtual const T& from_python_cTr(PyObject* p, type<const T&> t) = 0;
    virtual const T& from_python_T(PyObject* p, type<T> t) = 0;

    virtual std::auto_ptr<T>& from_python_aTr(PyObject* p, type<std::auto_ptr<T>&> t) = 0;
    virtual std::auto_ptr<T> from_python_aT(PyObject* p, type<std::auto_ptr<T> > t) = 0;
    virtual const std::auto_ptr<T>& from_python_caTr(PyObject* p, type<const std::auto_ptr<T>&> t) = 0;
    virtual PyObject* dispatcher_to_python(std::auto_ptr<T> x) = 0;

    virtual boost::shared_ptr<T>& from_python_sTr(PyObject* p, type<boost::shared_ptr<T>&> t) = 0;
    virtual const boost::shared_ptr<T>& from_python_sT(PyObject* p, type<boost::shared_ptr<T> > t) = 0;
    virtual const boost::shared_ptr<T>& from_python_csTr(PyObject* p, type<const boost::shared_ptr<T>&> t) = 0;
    virtual PyObject* dispatcher_to_python(boost::shared_ptr<T> x) = 0;
};

// Converters to be used if T is not copyable.
template <class T>
struct export_converter_object_noncopyable : export_converter_object_base<T>
{
    virtual PyObject* dispatcher_to_python(const T& x) {
        PyErr_SetString(PyExc_RuntimeError,
        "to_python(boost::python::semantics, const T&) converter not exported");
        throw import_error();
    }

    virtual T* from_python_Ts(PyObject* p, type<T*> t) {
        return from_python(p, t);
    }
    virtual const T* from_python_cTs(PyObject* p, type<const T*> t) {
        return from_python(p, t);
    }
    virtual const T* from_python_cTscr(PyObject* p, type<const T*const&> t) {
        return from_python(p, t);
    }
    virtual T* from_python_Tscr(PyObject* p, type<T* const&> t) {
        return from_python(p, t);
    }
    virtual T& from_python_Tr(PyObject* p, type<T&> t) {
        return from_python(p, t);
    }
    virtual const T& from_python_cTr(PyObject* p, type<const T&> t) {
        return from_python(p, t);
    }
    virtual const T& from_python_T(PyObject* p, type<T> t) {
        return from_python(p, t);
    }

    virtual std::auto_ptr<T>& from_python_aTr(PyObject* p, type<std::auto_ptr<T>&> t) {
        return from_python(p, t);
    }
    virtual std::auto_ptr<T> from_python_aT(PyObject* p, type<std::auto_ptr<T> > t) {
        return from_python(p, t);
    }
    virtual const std::auto_ptr<T>& from_python_caTr(PyObject* p, type<const std::auto_ptr<T>&> t) {
        return from_python(p, t);
    }
    virtual PyObject* dispatcher_to_python(std::auto_ptr<T> x) {
        return to_python(search_namespace, x);
    }

    virtual boost::shared_ptr<T>& from_python_sTr(PyObject* p, type<boost::shared_ptr<T>&> t) {
        return from_python(p, t);
    }
    virtual const boost::shared_ptr<T>& from_python_sT(PyObject* p, type<boost::shared_ptr<T> > t) {
        return from_python(p, t);
    }
    virtual const boost::shared_ptr<T>& from_python_csTr(PyObject* p, type<const boost::shared_ptr<T>&> t) {
        return from_python(p, t);
    }
    virtual PyObject* dispatcher_to_python(boost::shared_ptr<T> x) {
        return to_python(search_namespace, x);
    }
};

// The addditional to_python() converter that can be used if T is copyable.
template <class T>
struct export_converter_object : export_converter_object_noncopyable<T>
{
    virtual PyObject* dispatcher_to_python(const T& x) {
        return py_extension_class_converters(type<T>()).member_to_python(x);
    }
};

namespace detail {

/* This class template is instantiated by import_converters<T>.
   Its purpose is to import the converter_object via the Python API.
   The actual import is only done once. The pointer to the
   imported converter object is kept in the static data member
   imported_converters.
 */
template <class T>
class import_extension_class
    : public python_import_extension_class_converters<T>
{
 public:
    inline import_extension_class(const char* module, const char* py_class) {
      m_module = module;
      m_py_class = py_class;
    }

    static export_converter_object_base<T>* get_converters();

  private:
    static std::string m_module;
    static std::string m_py_class;
    static export_converter_object_base<T>* imported_converters;
};

template <class T> std::string import_extension_class<T>::m_module;
template <class T> std::string import_extension_class<T>::m_py_class;
template <class T>
export_converter_object_base<T>*
import_extension_class<T>::imported_converters = 0;

template <class T>
export_converter_object_base<T>*
import_extension_class<T>::get_converters() {
  if (imported_converters == 0) {
    void* cobject
      = import_converter_object(m_module, m_py_class,
                                converters_attribute_name);
    imported_converters
      = static_cast<export_converter_object_base<T>*>(cobject);
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

// Implementation of export_converters().
template <class T, class U>
void export_converters(class_builder<T, U>& cb)
{
    static export_converter_object<T> export_cvts;
    cb.add(
      ref(PyCObject_FromVoidPtr(reinterpret_cast<void*>(&export_cvts), NULL)),
      detail::converters_attribute_name);
}

// Implementation of export_converters_noncopyable().
template <class T, class U>
void export_converters_noncopyable(class_builder<T, U>& cb)
{
    static export_converter_object_noncopyable<T> export_cvts;
    cb.add(
      ref(PyCObject_FromVoidPtr(reinterpret_cast<void*>(&export_cvts), NULL)),
      detail::converters_attribute_name);
}

// Implementation of import_converters<T>.
template <class T>
class import_converters
    : python_import_extension_class_converters<T> // Works around MSVC6.x/GCC2.95.2 bug described
                                                  // at the bottom of class_builder.hpp.
{
 public:
    import_converters(const char* module, const char* py_class)
        : m_class(new detail::import_extension_class<T>(module, py_class))
    { }
 private:
    boost::shared_ptr<detail::import_extension_class<T> > m_class;
};

}} // namespace boost::python

#endif // CROSS_MODULE_HPP
