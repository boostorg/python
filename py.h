//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef METHOD_DWA122899_H_
# define METHOD_DWA122899_H_

# include "wrap_python.h"
# include "none.h"
# include "signatures.h"
# include <boost/smart_ptr.hpp>
# include "errors.h"
# include <string>

namespace py {

template <class P, class T> class WrappedPointer;

//#pragma warn_possunwant off
inline void decref_impl(PyObject* p) { Py_DECREF(p); }
inline void xdecref_impl(PyObject* p) { Py_XDECREF(p); }
//#pragma warn_possunwant reset

template <class T>
inline void decref(T* p)
{
	char* const raw_p = reinterpret_cast<char*>(p);
	char* const p_base = raw_p - offsetof(PyObject, ob_refcnt);
	decref_impl(reinterpret_cast<PyObject*>(p_base));
}

template <class T>
inline void xdecref(T* p)
{
	char* const raw_p = reinterpret_cast<char*>(p);
	char* const p_base = raw_p - offsetof(PyObject, ob_refcnt);
	xdecref_impl(reinterpret_cast<PyObject*>(p_base));
}

#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
}
#endif

//
// Converters
//
PyObject* to_python(long);
long from_python(PyObject* p, py::Type<long>);
long from_python(PyObject* p, py::Type<const long&>);

PyObject* to_python(unsigned long);
unsigned long from_python(PyObject* p, py::Type<unsigned long>);
unsigned long from_python(PyObject* p, py::Type<const unsigned long&>);

PyObject* to_python(int);
int from_python(PyObject*, py::Type<int>);
int from_python(PyObject*, py::Type<const int&>);
    
PyObject* to_python(unsigned int);
unsigned int from_python(PyObject*, py::Type<unsigned int>);
unsigned int from_python(PyObject*, py::Type<const unsigned int&>);

PyObject* to_python(short);
short from_python(PyObject*, py::Type<short>);
short from_python(PyObject*, py::Type<const short&>);
    
PyObject* to_python(unsigned short);
unsigned short from_python(PyObject*, py::Type<unsigned short>);
unsigned short from_python(PyObject*, py::Type<const unsigned short&>);

PyObject* to_python(float);
float from_python(PyObject*, py::Type<float>);
float from_python(PyObject*, py::Type<const float&>);
    
PyObject* to_python(double);
double from_python(PyObject*, py::Type<double>);
double from_python(PyObject*, py::Type<const double&>);
    
PyObject* to_python(bool);
bool from_python(PyObject*, py::Type<bool>);
bool from_python(PyObject*, py::Type<const bool&>);

PyObject* to_python(void);
void from_python(PyObject*, py::Type<void>);

PyObject* to_python(const char* s);
const char* from_python(PyObject*, py::Type<const char*>);

PyObject* to_python(const std::string& s);
std::string from_python(PyObject*, py::Type<std::string>);
std::string from_python(PyObject*, py::Type<const std::string&>);

// For when your C++ function really wants to pass/return a PyObject*
PyObject* to_python(PyObject*);
PyObject* from_python(PyObject*, py::Type<PyObject*>);

// Some standard conversions to/from smart pointer types. You can add your own
// from these examples.  These are not generated using the friend technique from
// WrappedPointer because:
//
//      1. We want to be able to extend conversion to/from WrappedPointers using
//      arbitrary smart pointer types.
//
//      2. It helps with compilation independence. This way, code which creates
//      wrappers for functions accepting and returning smart_ptr<T> does not
//      have to have already seen the invocation of WrappedType<T>.
//

// Unfortunately, MSVC6 is so incredibly lame that we have to rely on the friend
// technique to auto_generate standard pointer conversions for wrapped
// types. This means that you need to write a non-templated function for each
// specific smart_ptr<T> which you want to convert from_python. For example,
//
// namespace py {
// #ifdef MUST_SUPPORT_MSVC
//
// MyPtr<Foo> from_python(PyObject*p, Type<MyPtr<Foo> >)
//     { return smart_ptr_from_python(p, Type<MyPtr<Foo> >(), Type<Foo>());}
// }
// 
// MyPtr<Bar> from_python(PyObject*p, Type<MyPtr<Bar> >)
//     { return smart_ptr_from_python(p, Type<MyPtr<Bar> >(), Type<Bar>());}
// 
// ... // definitions for MyPtr<Baz>, MyPtr<Mumble>, etc.
//
// #else
//
// // Just once for all MyPtr<T>
// template <class T>
// MyPtr<T> from_python(PyObject*p, Type<MyPtr<T> >)
// {
//    return smart_ptr_from_python(p, Type<MyPtr<T> >(), Type<T>());
// }
//
// #endif
// }

#if !defined(PY_MSVC6_OR_EARLIER)
template <class T>
boost::shared_ptr<T> from_python(PyObject*p, py::Type<boost::shared_ptr<T> >)
{
    return smart_ptr_from_python(p, py::Type<boost::shared_ptr<T> >(), py::Type<T>());
}
#endif

#if 0
template <class T>
PyObject* to_python(std::auto_ptr<T> p)
{
    return new py::WrappedPointer<std::auto_ptr<T>, T>(p);
}

template <class T>
PyObject* to_python(boost::shared_ptr<T> p)
{
    return new py::WrappedPointer<boost::shared_ptr<T>, T>(p);
}
#endif

//
// inline implementations
//

inline PyObject* to_python(long l)
{
	return PyInt_FromLong(l);
}

inline PyObject* to_python(int x)
{
	return PyInt_FromLong(x);
}

inline int from_python(PyObject* p, py::Type<const int&>)
{
    return from_python(p, py::Type<int>());
}

inline PyObject* to_python(short x)
{
	return PyInt_FromLong(x);
}

inline short from_python(PyObject* p, py::Type<const short&>)
{
    return from_python(p, py::Type<short>());
}

inline PyObject* to_python(bool b)
{
	return PyInt_FromLong(b);
}

inline bool from_python(PyObject* p, py::Type<const bool&>)
{
    return from_python(p, py::Type<bool>());
}

inline PyObject* to_python(void)
{
    return py::none();
}

// const char*
inline PyObject* to_python(const char* s)
{
	return PyString_FromString(s);
}

inline std::string from_python(PyObject* p, py::Type<const std::string&>)
{
    return from_python(p, py::Type<std::string>());
}

inline PyObject* to_python(PyObject* p)
{
    Py_INCREF(p);
    return p;
}

inline PyObject* from_python(PyObject* p, py::Type<PyObject*>)
{
    return p;
}

inline unsigned int from_python(PyObject* p, py::Type<const unsigned int&>)
{
    return from_python(p, py::Type<unsigned int>());
}

inline unsigned short from_python(PyObject* p, py::Type<const unsigned short&>)
{
    return from_python(p, py::Type<unsigned short>());
}

inline unsigned long from_python(PyObject* p, py::Type<const unsigned long&>)
{
    return from_python(p, py::Type<unsigned long>());
}

inline long from_python(PyObject* p, py::Type<const long&>)
{
    return from_python(p, py::Type<long>());
}


#ifdef PY_NO_INLINE_FRIENDS_IN_NAMESPACE
namespace py {
namespace converters { // bringing these into namespace py tended to confuse gcc;
using ::to_python;       // they are in namespace py::converters for use by clients
using ::from_python;
}
#else
namespace converters {
using ::py::to_python;
using ::py::from_python;
}
#endif

} // namespace py

#endif
