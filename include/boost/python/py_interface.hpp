// Automatically generated from py_api_gen.py
#ifndef PY_INTERFACE_HPP
#define PY_INTERFACE_HPP

#include <boost/python/object.hpp>
#include <boost/python/arg_from_python.hpp>

namespace boost { namespace python { namespace api {

enum call_dict_usage { use_new_dict, use_local_dict, use_global_dict };

namespace api_detail {

BOOST_PYTHON_DECL object get_func(const char* name);
BOOST_PYTHON_DECL object call_statement(const char *stmt, int n, ...);
BOOST_PYTHON_DECL object call_statement_du(const char *stmt, call_dict_usage cdu, int n, ...);

template<class A>
struct get_arg
{
    get_arg(A const &a) : h(a) {}
    object h;
    operator object const& () { return h; }
    operator object const* () { return &h; }
};

template<>
struct get_arg<object>
{
    get_arg(object const &a) : h(a) {}
    object const &h;
    operator object const& () { return h; }
    operator object const* () { return &h; }
};

template<>
struct get_arg<PyObject*>
{
    get_arg(PyObject* a) : h((python::detail::borrowed_reference)a) {}
    object h;
    operator object const& () { return h; }
    operator object const* () { return &h; }
};

}

BOOST_PYTHON_DECL object locals();


template<class A0>
object abs(A0 const& a0)
{
    return api_detail::get_func("abs")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object abs(object const& a0);
BOOST_PYTHON_DECL object abs(short a0);
BOOST_PYTHON_DECL object abs(int a0);
BOOST_PYTHON_DECL object abs(long a0);
BOOST_PYTHON_DECL object abs(double const & a0);
BOOST_PYTHON_DECL object apply(object const& a0, object const& a1);
BOOST_PYTHON_DECL object apply(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL bool callable(object const& a0);
template<class A0>
object chr(A0 const& a0)
{
    return api_detail::get_func("chr")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object chr(object const& a0);
BOOST_PYTHON_DECL object chr(short a0);
BOOST_PYTHON_DECL object chr(int a0);
BOOST_PYTHON_DECL object chr(long a0);
template<class A0, class A1>
int cmp(A0 const& a0, A1 const& a1)
{
    int rslt;
    int r = ::PyObject_Cmp(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), &rslt);
    if(r == -1)
        throw_error_already_set();
    return rslt;
}
BOOST_PYTHON_DECL int cmp(object const& a0, object const& a1);
BOOST_PYTHON_DECL object coerce(object const& a0, object const& a1);
BOOST_PYTHON_DECL object compile(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object compile(const char* a0, const char* a1, const char* a2);
BOOST_PYTHON_DECL object compile(object const& a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object compile(const char* a0, const char* a1, const char* a2, int a3);
BOOST_PYTHON_DECL object compile(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object compile(const char* a0, const char* a1, const char* a2, int a3, int a4);
template<class A0>
object complex(A0 const& a0)
{
    return api_detail::get_func("complex")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object complex(object const& a0);
BOOST_PYTHON_DECL object complex(double const& a0);
template<class A0, class A1>
object complex(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("complex")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
BOOST_PYTHON_DECL object complex(object const& a0, object const& a1);
BOOST_PYTHON_DECL object complex(double const& a0, double const& a1);
BOOST_PYTHON_DECL object dict();
BOOST_PYTHON_DECL object dict(object const& a0);
BOOST_PYTHON_DECL object dir();
BOOST_PYTHON_DECL object dir(object const& a0);
template<class A0, class A1>
object divmod(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("divmod")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
BOOST_PYTHON_DECL object divmod(object const& a0, object const& a1);
BOOST_PYTHON_DECL object divmod(int a0, int a1);
BOOST_PYTHON_DECL object divmod(long a0, long a1);
BOOST_PYTHON_DECL object divmod(double const& a0, double const& a1);
BOOST_PYTHON_DECL object eval(const char* a0);
BOOST_PYTHON_DECL object eval(const char* a0, object const& a2);
BOOST_PYTHON_DECL object eval(const char* a0, object const& a2, object const& a3);
BOOST_PYTHON_DECL object exec(const char* a0);
BOOST_PYTHON_DECL object exec(const char* a0, object const& a2);
BOOST_PYTHON_DECL object exec(const char* a0, object const& a2, object const& a3);
BOOST_PYTHON_DECL object execfile(object const& a0);
BOOST_PYTHON_DECL object execfile(object const& a0, object const& a1);
BOOST_PYTHON_DECL object execfile(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object file(object const& a0);
BOOST_PYTHON_DECL object file(const char* a0);
BOOST_PYTHON_DECL object file(object const& a0, object const& a1);
BOOST_PYTHON_DECL object file(const char* a0, const char* a1);
BOOST_PYTHON_DECL object file(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object file(const char* a0, const char* a1, int a2);
BOOST_PYTHON_DECL object filter(object const& a0, object const& a1);
BOOST_PYTHON_DECL object float_(object const& a0);
BOOST_PYTHON_DECL object float_(const char* a0);
BOOST_PYTHON_DECL object float_(double const& a0);
BOOST_PYTHON_DECL object getattr(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object getattr(object const& a0, const char * a1, object const& a2);
BOOST_PYTHON_DECL object globals();
BOOST_PYTHON_DECL bool hasattr(object const& a0, object const& a1);
BOOST_PYTHON_DECL bool hasattr(object const& a0, const char* a1);
BOOST_PYTHON_DECL long hash(object const& a0);
template<class A0>
object hex(A0 const& a0)
{
    return api_detail::get_func("hex")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object hex(object const& a0);
BOOST_PYTHON_DECL object hex(char a0);
BOOST_PYTHON_DECL object hex(short a0);
BOOST_PYTHON_DECL object hex(int a0);
BOOST_PYTHON_DECL object hex(long a0);
BOOST_PYTHON_DECL long id(object const& a0);
BOOST_PYTHON_DECL object input();
BOOST_PYTHON_DECL object input(object const& a0);
BOOST_PYTHON_DECL object input(const char* a0);
BOOST_PYTHON_DECL object int_(object const& a0);
BOOST_PYTHON_DECL object int_(long a0);
BOOST_PYTHON_DECL object int_(const char* a0);
BOOST_PYTHON_DECL object intern(object const& a0);
BOOST_PYTHON_DECL object intern(const char* a0);
BOOST_PYTHON_DECL bool isinstance(object const& a0, object const& a1);
BOOST_PYTHON_DECL bool issubclass(object const& a0, object const& a1);
BOOST_PYTHON_DECL object iter(object const& a0);
BOOST_PYTHON_DECL object iter(object const& a0, object const& a1);
BOOST_PYTHON_DECL long len(object const& a0);
BOOST_PYTHON_DECL object list();
BOOST_PYTHON_DECL object list(object const& a0);
BOOST_PYTHON_DECL object long_(object const& a0);
BOOST_PYTHON_DECL object long_(long a0);
BOOST_PYTHON_DECL object long_(const char* a0);
BOOST_PYTHON_DECL object map(object const& a0);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
template<class A0>
object max(A0 const& a0)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0));
}
template<class A0, class A1>
object max(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
template<class A0, class A1, class A2>
object max(A0 const& a0, A1 const& a1, A2 const& a2)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2));
}
template<class A0, class A1, class A2, class A3>
object max(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3));
}
template<class A0, class A1, class A2, class A3, class A4>
object max(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4));
}
template<class A0, class A1, class A2, class A3, class A4, class A5>
object max(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6>
object max(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
object max(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6), api_detail::get_arg<A7>(a7));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
object max(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6), api_detail::get_arg<A7>(a7), api_detail::get_arg<A8>(a8));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
object max(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
{
    return api_detail::get_func("max")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6), api_detail::get_arg<A7>(a7), api_detail::get_arg<A8>(a8), api_detail::get_arg<A9>(a9));
}
BOOST_PYTHON_DECL object max(object const& a0);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
template<class A0>
object min(A0 const& a0)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0));
}
template<class A0, class A1>
object min(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
template<class A0, class A1, class A2>
object min(A0 const& a0, A1 const& a1, A2 const& a2)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2));
}
template<class A0, class A1, class A2, class A3>
object min(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3));
}
template<class A0, class A1, class A2, class A3, class A4>
object min(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4));
}
template<class A0, class A1, class A2, class A3, class A4, class A5>
object min(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6>
object min(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
object min(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6), api_detail::get_arg<A7>(a7));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
object min(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6), api_detail::get_arg<A7>(a7), api_detail::get_arg<A8>(a8));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
object min(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
{
    return api_detail::get_func("min")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2), api_detail::get_arg<A3>(a3), api_detail::get_arg<A4>(a4), api_detail::get_arg<A5>(a5), api_detail::get_arg<A6>(a6), api_detail::get_arg<A7>(a7), api_detail::get_arg<A8>(a8), api_detail::get_arg<A9>(a9));
}
BOOST_PYTHON_DECL object min(object const& a0);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
template<class A0>
object oct(A0 const& a0)
{
    return api_detail::get_func("oct")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object oct(object const& a0);
BOOST_PYTHON_DECL object oct(char a0);
BOOST_PYTHON_DECL object oct(short a0);
BOOST_PYTHON_DECL object oct(int a0);
BOOST_PYTHON_DECL object oct(long a0);
BOOST_PYTHON_DECL object open(object const& a0);
BOOST_PYTHON_DECL object open(const char* a0);
BOOST_PYTHON_DECL object open(object const& a0, object const& a1);
BOOST_PYTHON_DECL object open(const char* a0, const char* a1);
BOOST_PYTHON_DECL object open(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object open(const char* a0, const char* a1, int a2);
BOOST_PYTHON_DECL long ord(object const& a0);
BOOST_PYTHON_DECL long ord(const char* a0);
template<class A0, class A1>
object pow(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("pow")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
BOOST_PYTHON_DECL object pow(object const& a0, object const& a1);
BOOST_PYTHON_DECL object pow(double const& a0, double const& a1);
BOOST_PYTHON_DECL object pow(double const& a0, double const& a1, double const& a2);
template<class A0>
object print(A0 const& a0)
{
    return api_detail::call_statement_du("print _1", use_new_dict, 1, (object const*)api_detail::get_arg<A0>(a0));
}
template<class A0, class A1>
object print(A0 const& a0, A1 const& a1)
{
    return api_detail::call_statement_du("print _1, _2", use_new_dict, 2, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1));
}
template<class A0, class A1, class A2>
object print(A0 const& a0, A1 const& a1, A2 const& a2)
{
    return api_detail::call_statement_du("print _1, _2, _3", use_new_dict, 3, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2));
}
template<class A0, class A1, class A2, class A3>
object print(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3)
{
    return api_detail::call_statement_du("print _1, _2, _3, _4", use_new_dict, 4, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3));
}
template<class A0, class A1, class A2, class A3, class A4>
object print(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
{
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5", use_new_dict, 5, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4));
}
template<class A0, class A1, class A2, class A3, class A4, class A5>
object print(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
{
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6", use_new_dict, 6, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6>
object print(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
{
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7", use_new_dict, 7, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
object print(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
{
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7, _8", use_new_dict, 8, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
object print(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
{
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7, _8, _9", use_new_dict, 9, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8));
}
template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
object print(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
{
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7, _8, _9, _10", use_new_dict, 10, (object const*)api_detail::get_arg<A0>(a0), (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9));
}
BOOST_PYTHON_DECL object print(object const& a0);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
template<class A1>
object print_file(object const& a0, A1 const& a1)
{
    return api_detail::call_statement_du("print >>_1, _2", use_new_dict, 2, a0, (object const*)api_detail::get_arg<A1>(a1));
}
template<class A1, class A2>
object print_file(object const& a0, A1 const& a1, A2 const& a2)
{
    return api_detail::call_statement_du("print >>_1, _2, _3", use_new_dict, 3, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2));
}
template<class A1, class A2, class A3>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4", use_new_dict, 4, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3));
}
template<class A1, class A2, class A3, class A4>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5", use_new_dict, 5, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4));
}
template<class A1, class A2, class A3, class A4, class A5>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6", use_new_dict, 6, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5));
}
template<class A1, class A2, class A3, class A4, class A5, class A6>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7", use_new_dict, 7, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8", use_new_dict, 8, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8, _9", use_new_dict, 9, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8, _9, _10", use_new_dict, 10, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
object print_file(object const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9, A10 const& a10)
{
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11", use_new_dict, 11, a0, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9), (object const*)api_detail::get_arg<A10>(a10));
}
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10);
template<class A0>
object range(A0 const& a0)
{
    return api_detail::get_func("range")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object range(object const& a0);
BOOST_PYTHON_DECL object range(int a0);
template<class A0, class A1>
object range(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("range")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
BOOST_PYTHON_DECL object range(object const& a0, object const& a1);
BOOST_PYTHON_DECL object range(int a0, int a1);
template<class A0, class A1, class A2>
object range(A0 const& a0, A1 const& a1, A2 const& a2)
{
    return api_detail::get_func("range")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2));
}
BOOST_PYTHON_DECL object range(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object range(int a0, int a1, int a2);
BOOST_PYTHON_DECL object raw_input();
BOOST_PYTHON_DECL object raw_input(object const& a0);
BOOST_PYTHON_DECL object raw_input(const char* a0);
BOOST_PYTHON_DECL object reduce(object const& a0, object const& a1);
BOOST_PYTHON_DECL object reduce(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object reload(object const& a0);
BOOST_PYTHON_DECL object repr(object const& a0);
template<class A0>
object round(A0 const& a0)
{
    return api_detail::get_func("round")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object round(object const& a0);
BOOST_PYTHON_DECL object round(double const& a0);
template<class A0, class A1>
object round(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("round")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
BOOST_PYTHON_DECL object round(object const& a0, object const& a1);
BOOST_PYTHON_DECL object round(double const& a0, double const& a1);
template<class A0>
object slice(A0 const& a0)
{
    return api_detail::get_func("slice")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object slice(object const& a0);
BOOST_PYTHON_DECL object slice(int a0);
template<class A0, class A1>
object slice(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("slice")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
BOOST_PYTHON_DECL object slice(object const& a0, object const& a1);
BOOST_PYTHON_DECL object slice(int a0, int a1);
template<class A0, class A1, class A2>
object slice(A0 const& a0, A1 const& a1, A2 const& a2)
{
    return api_detail::get_func("slice")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2));
}
BOOST_PYTHON_DECL object slice(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object slice(int a0, int a1, int a2);
BOOST_PYTHON_DECL object str(object const& a0);
BOOST_PYTHON_DECL object tuple();
BOOST_PYTHON_DECL object tuple(object const& a0);
BOOST_PYTHON_DECL object type_(object const& a0);
template<class A0>
object unichr(A0 const& a0)
{
    return api_detail::get_func("unichr")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object unichr(object const& a0);
BOOST_PYTHON_DECL object unichr(short a0);
BOOST_PYTHON_DECL object unichr(int a0);
BOOST_PYTHON_DECL object unichr(long a0);
BOOST_PYTHON_DECL object unicode(object const& a0);
BOOST_PYTHON_DECL object unicode(object const& a0, object const& a1);
BOOST_PYTHON_DECL object unicode(object const& a0, const char* a1);
BOOST_PYTHON_DECL object unicode(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object unicode(object const& a0, const char* a1, const char* a2);
BOOST_PYTHON_DECL object vars();
BOOST_PYTHON_DECL object vars(object const& a0);
template<class A0>
object xrange(A0 const& a0)
{
    return api_detail::get_func("xrange")(api_detail::get_arg<A0>(a0));
}
BOOST_PYTHON_DECL object xrange(object const& a0);
BOOST_PYTHON_DECL object xrange(int a0);
template<class A0, class A1>
object xrange(A0 const& a0, A1 const& a1)
{
    return api_detail::get_func("xrange")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1));
}
BOOST_PYTHON_DECL object xrange(object const& a0, object const& a1);
BOOST_PYTHON_DECL object xrange(int a0, int a1);
template<class A0, class A1, class A2>
object xrange(A0 const& a0, A1 const& a1, A2 const& a2)
{
    return api_detail::get_func("xrange")(api_detail::get_arg<A0>(a0), api_detail::get_arg<A1>(a1), api_detail::get_arg<A2>(a2));
}
BOOST_PYTHON_DECL object xrange(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object xrange(int a0, int a1, int a2);
BOOST_PYTHON_DECL object zip(object const& a0);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
BOOST_PYTHON_DECL object compile_string(const char* a0, const char* a1, int a2);
BOOST_PYTHON_DECL int import_append_inittab(const char* a0, void(*a1)(void));
BOOST_PYTHON_DECL object import_add_module(const char* a0);
BOOST_PYTHON_DECL object import_get_module_dict();
BOOST_PYTHON_DECL object import_import(object const& a0);
BOOST_PYTHON_DECL object import_import(const char* a0);
BOOST_PYTHON_DECL object import_import_module(const char* a0);
BOOST_PYTHON_DECL object import_import_module_ex(const char* a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object module_get_dict(object const& a0);
BOOST_PYTHON_DECL int object_print(object const& a0, FILE* a1, int a2);
BOOST_PYTHON_DECL object run_file(FILE* a0, const char* a1, int a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL int run_simple_file(FILE* a0, const char* a1);
BOOST_PYTHON_DECL int run_simple_string(const char* a0);
BOOST_PYTHON_DECL object run_string(const char* a0, int a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object call_statement(const char* a0);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1);
template<class A1>
object call_statement(const char* a0, A1 const& a1)
{
    return api_detail::call_statement(a0, 1, (object const*)api_detail::get_arg<A1>(a1));
}
template<class A1, class A2>
object call_statement(const char* a0, A1 const& a1, A2 const& a2)
{
    return api_detail::call_statement(a0, 2, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2));
}
template<class A1, class A2, class A3>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3)
{
    return api_detail::call_statement(a0, 3, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3));
}
template<class A1, class A2, class A3, class A4>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
{
    return api_detail::call_statement(a0, 4, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4));
}
template<class A1, class A2, class A3, class A4, class A5>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
{
    return api_detail::call_statement(a0, 5, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5));
}
template<class A1, class A2, class A3, class A4, class A5, class A6>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
{
    return api_detail::call_statement(a0, 6, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
{
    return api_detail::call_statement(a0, 7, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
{
    return api_detail::call_statement(a0, 8, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
{
    return api_detail::call_statement(a0, 9, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9));
}
template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
object call_statement(const char* a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9, A10 const& a10)
{
    return api_detail::call_statement(a0, 10, (object const*)api_detail::get_arg<A1>(a1), (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9), (object const*)api_detail::get_arg<A10>(a10));
}
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10);
template<class A2>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2)
{
    return api_detail::call_statement_du(a0, a1, 1, (object const*)api_detail::get_arg<A2>(a2));
}
template<class A2, class A3>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3)
{
    return api_detail::call_statement_du(a0, a1, 2, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3));
}
template<class A2, class A3, class A4>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4)
{
    return api_detail::call_statement_du(a0, a1, 3, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4));
}
template<class A2, class A3, class A4, class A5>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5)
{
    return api_detail::call_statement_du(a0, a1, 4, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5));
}
template<class A2, class A3, class A4, class A5, class A6>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
{
    return api_detail::call_statement_du(a0, a1, 5, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6));
}
template<class A2, class A3, class A4, class A5, class A6, class A7>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
{
    return api_detail::call_statement_du(a0, a1, 6, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7));
}
template<class A2, class A3, class A4, class A5, class A6, class A7, class A8>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8)
{
    return api_detail::call_statement_du(a0, a1, 7, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8));
}
template<class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9)
{
    return api_detail::call_statement_du(a0, a1, 8, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9));
}
template<class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9, A10 const& a10)
{
    return api_detail::call_statement_du(a0, a1, 9, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9), (object const*)api_detail::get_arg<A10>(a10));
}
template<class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
object call_statement(const char* a0, call_dict_usage a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7, A8 const& a8, A9 const& a9, A10 const& a10, A11 const& a11)
{
    return api_detail::call_statement_du(a0, a1, 10, (object const*)api_detail::get_arg<A2>(a2), (object const*)api_detail::get_arg<A3>(a3), (object const*)api_detail::get_arg<A4>(a4), (object const*)api_detail::get_arg<A5>(a5), (object const*)api_detail::get_arg<A6>(a6), (object const*)api_detail::get_arg<A7>(a7), (object const*)api_detail::get_arg<A8>(a8), (object const*)api_detail::get_arg<A9>(a9), (object const*)api_detail::get_arg<A10>(a10), (object const*)api_detail::get_arg<A11>(a11));
}
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10);
BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10, object const& a11);

}}}

#endif // PY_INTERFACE_HPP

