// Automatically generated from py_api_gen.py

#include <boost/python/py_interface.hpp>

namespace boost { namespace python { namespace api {

namespace api_detail {

BOOST_PYTHON_DECL object get_func(const char* name) {
    object __builtin__((python::detail::borrowed_reference)::PyImport_AddModule(const_cast<char *>("__builtin__")));
    return object(__builtin__.attr(name));
}

inline handle<> get_current_frame()
{
    return handle<>(allow_null(borrowed((PyObject*)(PyThreadState_Get()->frame))));
}

inline object get_global_dict(call_dict_usage cdu, handle<> const& frame)
{
    if(frame.get())
        return object(object(frame).attr("f_globals"));
    else
        return api::globals();
}

object get_local_dict(call_dict_usage cdu, handle<> const& frame, object const& global_dict)
{
    switch(cdu) {
        case use_new_dict:
            return api::dict();
        case use_global_dict:
            return global_dict;
        default:
            if(frame.get())
                return object(object(frame).attr("f_locals"));
            else
                return api::dict();
    }
}

inline object call_statement(const char *stmt, object const& global_dict, object& local_dict)
{
    local_dict["_0"] = object((python::detail::borrowed_reference)Py_None);
    api::run_string(stmt, Py_file_input, global_dict, local_dict);
    return object(local_dict["_0"]);
}

object call_statement(const char *stmt)
{
    handle<> frame(get_current_frame());
    if(frame.get()) {
        object f(frame);
        object gd(f.attr("f_globals"));
        object ld(f.attr("f_locals"));
        return call_statement(stmt, gd, ld);
    } else {
        object gd(api::globals());
        object ld(api::dict());
        return call_statement(stmt, gd, ld);
    }
}

object call_statement_du(const char *stmt, call_dict_usage cdu)
{
    handle<> frame(get_current_frame());
    object gd(get_global_dict(cdu, frame));
    return call_statement(stmt, gd, get_local_dict(cdu, frame, gd));
}

inline object call_statement(const char *stmt, object const& global_dict, object& local_dict, int n, va_list mk)
{
    static const char *(idx[]) = { "_1", "_2", "_3", "_4", "_5", "_6", "_7", "_8", "_9", "_10" };
    local_dict["_0"] = object((python::detail::borrowed_reference)Py_None);
    for(int i = 0; i < n; ++i)
    {
        object const* p_arg = va_arg(mk, object const*);
        object const& arg = *p_arg;
        if(i < (int) (sizeof(idx) / sizeof(idx[0])))
            local_dict[idx[i]] = arg;
        else {
            local_dict[object("_") + object((python::detail::new_reference)PyObject_Str(object(i + 1).ptr()))] = arg;
        }
    }
    va_end(mk);
    api::run_string(stmt, Py_file_input, global_dict, local_dict);
    return object(local_dict["_0"]);
}

BOOST_PYTHON_DECL object call_statement(const char *stmt, int n, ...)
{
    va_list mk;
    va_start(mk, n);
    handle<> frame(get_current_frame());
    if(frame.get()) {
        object f(frame);
        object gd(f.attr("f_globals"));
        object ld(f.attr("f_locals"));
        return call_statement(stmt, gd, ld, n, mk);
    } else {
        object gd(api::globals());
        object ld(api::dict());
        return call_statement(stmt, gd, ld, n, mk);
    }
}

BOOST_PYTHON_DECL object call_statement_du(const char *stmt, call_dict_usage cdu, int n, ...)
{
    handle<> frame(get_current_frame());
    object gd(get_global_dict(cdu, frame));
    va_list mk;
    va_start(mk, n);
    return call_statement(stmt, gd, get_local_dict(cdu, frame, gd), n, mk);
}

}

BOOST_PYTHON_DECL object locals()
{
    handle<> frame(api_detail::get_current_frame());
    if(frame.get())
        return object(object(frame).attr("f_locals"));
    else
        return api::dict();
}


BOOST_PYTHON_DECL object abs(object const& a0) {
    return api_detail::get_func("abs")(a0);
}

BOOST_PYTHON_DECL object abs(short a0) {
    return api_detail::get_func("abs")(object(a0));
}

BOOST_PYTHON_DECL object abs(int a0) {
    return api_detail::get_func("abs")(object(a0));
}

BOOST_PYTHON_DECL object abs(long a0) {
    return api_detail::get_func("abs")(object(a0));
}

BOOST_PYTHON_DECL object abs(double const & a0) {
    return api_detail::get_func("abs")(object(a0));
}

BOOST_PYTHON_DECL object apply(object const& a0, object const& a1) {
    return object((python::detail::new_reference)::PyObject_CallObject(a0.ptr(), a1.ptr()));
}

BOOST_PYTHON_DECL object apply(object const& a0, object const& a1, object const& a2) {
    return object((python::detail::new_reference)::PyObject_Call(a0.ptr(), a1.ptr(), a2.ptr()));
}

BOOST_PYTHON_DECL bool callable(object const& a0) {
    return ::PyCallable_Check(a0.ptr());
}

BOOST_PYTHON_DECL object chr(object const& a0) {
    return api_detail::get_func("chr")(a0);
}

BOOST_PYTHON_DECL object chr(short a0) {
    return api_detail::get_func("chr")(object(a0));
}

BOOST_PYTHON_DECL object chr(int a0) {
    return api_detail::get_func("chr")(object(a0));
}

BOOST_PYTHON_DECL object chr(long a0) {
    return api_detail::get_func("chr")(object(a0));
}

BOOST_PYTHON_DECL int cmp(object const& a0, object const& a1) {
    int rslt;
    int r = ::PyObject_Cmp(a0.ptr(), a1.ptr(), &rslt);
    if(r == -1)
        throw_error_already_set();
    return rslt;
}

BOOST_PYTHON_DECL object coerce(object const& a0, object const& a1) {
    return api_detail::get_func("coerce")(a0, a1);
}

BOOST_PYTHON_DECL object compile(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("compile")(a0, a1, a2);
}

BOOST_PYTHON_DECL object compile(const char* a0, const char* a1, const char* a2) {
    return api_detail::get_func("compile")(object(a0), object(a1), object(a2));
}

BOOST_PYTHON_DECL object compile(object const& a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::get_func("compile")(a0, a1, a2, a3);
}

BOOST_PYTHON_DECL object compile(const char* a0, const char* a1, const char* a2, int a3) {
    return api_detail::get_func("compile")(object(a0), object(a1), object(a2), object(a3));
}

BOOST_PYTHON_DECL object compile(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::get_func("compile")(a0, a1, a2, a3, a4);
}

BOOST_PYTHON_DECL object compile(const char* a0, const char* a1, const char* a2, int a3, int a4) {
    return api_detail::get_func("compile")(object(a0), object(a1), object(a2), object(a3), object(a4));
}

BOOST_PYTHON_DECL object complex(object const& a0) {
    return api_detail::get_func("complex")(a0);
}

BOOST_PYTHON_DECL object complex(double const& a0) {
    return api_detail::get_func("complex")(object(a0));
}

BOOST_PYTHON_DECL object complex(object const& a0, object const& a1) {
    return api_detail::get_func("complex")(a0, a1);
}

BOOST_PYTHON_DECL object complex(double const& a0, double const& a1) {
    return api_detail::get_func("complex")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object dict() {
    return api_detail::get_func("dict")();
}

BOOST_PYTHON_DECL object dict(object const& a0) {
    return api_detail::get_func("dict")(a0);
}

BOOST_PYTHON_DECL object dir() {
    return object((python::detail::new_reference)::PyObject_Dir(NULL));
}

BOOST_PYTHON_DECL object dir(object const& a0) {
    return object((python::detail::new_reference)::PyObject_Dir(a0.ptr()));
}

BOOST_PYTHON_DECL object divmod(object const& a0, object const& a1) {
    return api_detail::get_func("divmod")(a0, a1);
}

BOOST_PYTHON_DECL object divmod(int a0, int a1) {
    return api_detail::get_func("divmod")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object divmod(long a0, long a1) {
    return api_detail::get_func("divmod")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object divmod(double const& a0, double const& a1) {
    return api_detail::get_func("divmod")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object eval(const char* a0) {
    return object((python::detail::new_reference)::PyRun_String(const_cast<char*>(a0), Py_eval_input, globals().ptr(), globals().ptr()));
}

BOOST_PYTHON_DECL object eval(const char* a0, object const& a2) {
    return object((python::detail::new_reference)::PyRun_String(const_cast<char*>(a0), Py_eval_input, a2.ptr(), globals().ptr()));
}

BOOST_PYTHON_DECL object eval(const char* a0, object const& a2, object const& a3) {
    return object((python::detail::new_reference)::PyRun_String(const_cast<char*>(a0), Py_eval_input, a2.ptr(), a3.ptr()));
}

BOOST_PYTHON_DECL object exec(const char* a0) {
    return object((python::detail::new_reference)::PyRun_String(const_cast<char*>(a0), Py_file_input, globals().ptr(), globals().ptr()));
}

BOOST_PYTHON_DECL object exec(const char* a0, object const& a2) {
    return object((python::detail::new_reference)::PyRun_String(const_cast<char*>(a0), Py_file_input, a2.ptr(), globals().ptr()));
}

BOOST_PYTHON_DECL object exec(const char* a0, object const& a2, object const& a3) {
    return object((python::detail::new_reference)::PyRun_String(const_cast<char*>(a0), Py_file_input, a2.ptr(), a3.ptr()));
}

BOOST_PYTHON_DECL object execfile(object const& a0) {
    return api_detail::get_func("execfile")(a0);
}

BOOST_PYTHON_DECL object execfile(object const& a0, object const& a1) {
    return api_detail::get_func("execfile")(a0, a1);
}

BOOST_PYTHON_DECL object execfile(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("execfile")(a0, a1, a2);
}

BOOST_PYTHON_DECL object file(object const& a0) {
    return api_detail::get_func("file")(a0);
}

BOOST_PYTHON_DECL object file(const char* a0) {
    return api_detail::get_func("file")(object(a0));
}

BOOST_PYTHON_DECL object file(object const& a0, object const& a1) {
    return api_detail::get_func("file")(a0, a1);
}

BOOST_PYTHON_DECL object file(const char* a0, const char* a1) {
    return api_detail::get_func("file")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object file(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("file")(a0, a1, a2);
}

BOOST_PYTHON_DECL object file(const char* a0, const char* a1, int a2) {
    return api_detail::get_func("file")(object(a0), object(a1), object(a2));
}

BOOST_PYTHON_DECL object filter(object const& a0, object const& a1) {
    return api_detail::get_func("filter")(a0, a1);
}

BOOST_PYTHON_DECL object float_(object const& a0) {
    return api_detail::get_func("float")(a0);
}

BOOST_PYTHON_DECL object float_(const char* a0) {
    return api_detail::get_func("float")(object(a0));
}

BOOST_PYTHON_DECL object float_(double const& a0) {
    return api_detail::get_func("float")(object(a0));
}

BOOST_PYTHON_DECL object getattr(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("getattr")(a0, a1, a2);
}

BOOST_PYTHON_DECL object getattr(object const& a0, const char * a1, object const& a2) {
    return api_detail::get_func("getattr")(a0, object(a1), a2);
}

BOOST_PYTHON_DECL object globals() {
    return object((python::detail::borrowed_reference)::PyModule_GetDict(PyImport_AddModule("__main__")));
}

BOOST_PYTHON_DECL bool hasattr(object const& a0, object const& a1) {
    return ::PyObject_HasAttr(a0.ptr(), a1.ptr());
}

BOOST_PYTHON_DECL bool hasattr(object const& a0, const char* a1) {
    return ::PyObject_HasAttrString(a0.ptr(), const_cast<char*>(a1));
}

BOOST_PYTHON_DECL long hash(object const& a0) {
    long r = ::PyObject_Hash(a0.ptr());
    if(r == -1)
        throw_error_already_set();
    return r;
}

BOOST_PYTHON_DECL object hex(object const& a0) {
    return api_detail::get_func("hex")(a0);
}

BOOST_PYTHON_DECL object hex(char a0) {
    return api_detail::get_func("hex")(object(a0));
}

BOOST_PYTHON_DECL object hex(short a0) {
    return api_detail::get_func("hex")(object(a0));
}

BOOST_PYTHON_DECL object hex(int a0) {
    return api_detail::get_func("hex")(object(a0));
}

BOOST_PYTHON_DECL object hex(long a0) {
    return api_detail::get_func("hex")(object(a0));
}

BOOST_PYTHON_DECL long id(object const& a0) {
    object r(api_detail::get_func("id")(a0));
    return boost::python::arg_from_python<long>(r.ptr())(r.ptr());
}

BOOST_PYTHON_DECL object input() {
    return api_detail::get_func("input")();
}

BOOST_PYTHON_DECL object input(object const& a0) {
    return api_detail::get_func("input")(a0);
}

BOOST_PYTHON_DECL object input(const char* a0) {
    return api_detail::get_func("input")(object(a0));
}

BOOST_PYTHON_DECL object int_(object const& a0) {
    return api_detail::get_func("int")(a0);
}

BOOST_PYTHON_DECL object int_(long a0) {
    return api_detail::get_func("int")(object(a0));
}

BOOST_PYTHON_DECL object int_(const char* a0) {
    return api_detail::get_func("int")(object(a0));
}

BOOST_PYTHON_DECL object intern(object const& a0) {
    return api_detail::get_func("intern")(a0);
}

BOOST_PYTHON_DECL object intern(const char* a0) {
    return api_detail::get_func("intern")(object(a0));
}

BOOST_PYTHON_DECL bool isinstance(object const& a0, object const& a1) {
    return ::PyObject_IsInstance(a0.ptr(), a1.ptr());
}

BOOST_PYTHON_DECL bool issubclass(object const& a0, object const& a1) {
    return ::PyObject_IsSubclass(a0.ptr(), a1.ptr());
}

BOOST_PYTHON_DECL object iter(object const& a0) {
    return object((python::detail::new_reference)::PyObject_GetIter(a0.ptr()));
}

BOOST_PYTHON_DECL object iter(object const& a0, object const& a1) {
    return api_detail::get_func("iter")(a0, a1);
}

BOOST_PYTHON_DECL long len(object const& a0) {
    long r = ::PyObject_Length(a0.ptr());
    if(r == -1)
        throw_error_already_set();
    return r;
}

BOOST_PYTHON_DECL object list() {
    return api_detail::get_func("list")();
}

BOOST_PYTHON_DECL object list(object const& a0) {
    return api_detail::get_func("list")(a0);
}

BOOST_PYTHON_DECL object long_(object const& a0) {
    return api_detail::get_func("long")(a0);
}

BOOST_PYTHON_DECL object long_(long a0) {
    return api_detail::get_func("long")(object(a0));
}

BOOST_PYTHON_DECL object long_(const char* a0) {
    return api_detail::get_func("long")(object(a0));
}

BOOST_PYTHON_DECL object map(object const& a0) {
    return api_detail::get_func("map")(a0);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1) {
    return api_detail::get_func("map")(a0, a1);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("map")(a0, a1, a2);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::get_func("map")(a0, a1, a2, a3);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::get_func("map")(a0, a1, a2, a3, a4);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::get_func("map")(a0, a1, a2, a3, a4, a5);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::get_func("map")(a0, a1, a2, a3, a4, a5, a6);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::get_func("map")(a0, a1, a2, a3, a4, a5, a6, a7);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::get_func("map")(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}

BOOST_PYTHON_DECL object map(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::get_func("map")(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

BOOST_PYTHON_DECL object max(object const& a0) {
    return api_detail::get_func("max")(a0);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1) {
    return api_detail::get_func("max")(a0, a1);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("max")(a0, a1, a2);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::get_func("max")(a0, a1, a2, a3);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::get_func("max")(a0, a1, a2, a3, a4);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::get_func("max")(a0, a1, a2, a3, a4, a5);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::get_func("max")(a0, a1, a2, a3, a4, a5, a6);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::get_func("max")(a0, a1, a2, a3, a4, a5, a6, a7);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::get_func("max")(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}

BOOST_PYTHON_DECL object max(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::get_func("max")(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

BOOST_PYTHON_DECL object min(object const& a0) {
    return api_detail::get_func("min")(a0);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1) {
    return api_detail::get_func("min")(a0, a1);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("min")(a0, a1, a2);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::get_func("min")(a0, a1, a2, a3);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::get_func("min")(a0, a1, a2, a3, a4);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::get_func("min")(a0, a1, a2, a3, a4, a5);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::get_func("min")(a0, a1, a2, a3, a4, a5, a6);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::get_func("min")(a0, a1, a2, a3, a4, a5, a6, a7);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::get_func("min")(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}

BOOST_PYTHON_DECL object min(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::get_func("min")(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

BOOST_PYTHON_DECL object oct(object const& a0) {
    return api_detail::get_func("oct")(a0);
}

BOOST_PYTHON_DECL object oct(char a0) {
    return api_detail::get_func("oct")(object(a0));
}

BOOST_PYTHON_DECL object oct(short a0) {
    return api_detail::get_func("oct")(object(a0));
}

BOOST_PYTHON_DECL object oct(int a0) {
    return api_detail::get_func("oct")(object(a0));
}

BOOST_PYTHON_DECL object oct(long a0) {
    return api_detail::get_func("oct")(object(a0));
}

BOOST_PYTHON_DECL object open(object const& a0) {
    return api_detail::get_func("open")(a0);
}

BOOST_PYTHON_DECL object open(const char* a0) {
    return api_detail::get_func("open")(object(a0));
}

BOOST_PYTHON_DECL object open(object const& a0, object const& a1) {
    return api_detail::get_func("open")(a0, a1);
}

BOOST_PYTHON_DECL object open(const char* a0, const char* a1) {
    return api_detail::get_func("open")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object open(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("open")(a0, a1, a2);
}

BOOST_PYTHON_DECL object open(const char* a0, const char* a1, int a2) {
    return api_detail::get_func("open")(object(a0), object(a1), object(a2));
}

BOOST_PYTHON_DECL long ord(object const& a0) {
    object r(api_detail::get_func("ord")(a0));
    return boost::python::arg_from_python<long>(r.ptr())(r.ptr());
}

BOOST_PYTHON_DECL long ord(const char* a0) {
    object r(api_detail::get_func("ord")(object(a0)));
    return boost::python::arg_from_python<long>(r.ptr())(r.ptr());
}

BOOST_PYTHON_DECL object pow(object const& a0, object const& a1) {
    return api_detail::get_func("pow")(a0, a1);
}

BOOST_PYTHON_DECL object pow(double const& a0, double const& a1) {
    return api_detail::get_func("pow")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object pow(double const& a0, double const& a1, double const& a2) {
    return api_detail::get_func("pow")(object(a0), object(a1), object(a2));
}

BOOST_PYTHON_DECL object print(object const& a0) {
    return api_detail::call_statement_du("print _1", use_new_dict, 1, &a0);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1) {
    return api_detail::call_statement_du("print _1, _2", use_new_dict, 2, &a0, &a1);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2) {
    return api_detail::call_statement_du("print _1, _2, _3", use_new_dict, 3, &a0, &a1, &a2);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::call_statement_du("print _1, _2, _3, _4", use_new_dict, 4, &a0, &a1, &a2, &a3);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5", use_new_dict, 5, &a0, &a1, &a2, &a3, &a4);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6", use_new_dict, 6, &a0, &a1, &a2, &a3, &a4, &a5);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7", use_new_dict, 7, &a0, &a1, &a2, &a3, &a4, &a5, &a6);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7, _8", use_new_dict, 8, &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7, _8, _9", use_new_dict, 9, &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
}

BOOST_PYTHON_DECL object print(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::call_statement_du("print _1, _2, _3, _4, _5, _6, _7, _8, _9, _10", use_new_dict, 10, &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1) {
    return api_detail::call_statement_du("print >>_1, _2", use_new_dict, 2, &a0, &a1);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2) {
    return api_detail::call_statement_du("print >>_1, _2, _3", use_new_dict, 3, &a0, &a1, &a2);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4", use_new_dict, 4, &a0, &a1, &a2, &a3);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5", use_new_dict, 5, &a0, &a1, &a2, &a3, &a4);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6", use_new_dict, 6, &a0, &a1, &a2, &a3, &a4, &a5);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7", use_new_dict, 7, &a0, &a1, &a2, &a3, &a4, &a5, &a6);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8", use_new_dict, 8, &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8, _9", use_new_dict, 9, &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8, _9, _10", use_new_dict, 10, &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9);
}

BOOST_PYTHON_DECL object print_file(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10) {
    return api_detail::call_statement_du("print >>_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11", use_new_dict, 11, &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10);
}

BOOST_PYTHON_DECL object range(object const& a0) {
    return api_detail::get_func("range")(a0);
}

BOOST_PYTHON_DECL object range(int a0) {
    return api_detail::get_func("range")(object(a0));
}

BOOST_PYTHON_DECL object range(object const& a0, object const& a1) {
    return api_detail::get_func("range")(a0, a1);
}

BOOST_PYTHON_DECL object range(int a0, int a1) {
    return api_detail::get_func("range")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object range(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("range")(a0, a1, a2);
}

BOOST_PYTHON_DECL object range(int a0, int a1, int a2) {
    return api_detail::get_func("range")(object(a0), object(a1), object(a2));
}

BOOST_PYTHON_DECL object raw_input() {
    return api_detail::get_func("raw_input")();
}

BOOST_PYTHON_DECL object raw_input(object const& a0) {
    return api_detail::get_func("raw_input")(a0);
}

BOOST_PYTHON_DECL object raw_input(const char* a0) {
    return api_detail::get_func("raw_input")(object(a0));
}

BOOST_PYTHON_DECL object reduce(object const& a0, object const& a1) {
    return api_detail::get_func("reduce")(a0, a1);
}

BOOST_PYTHON_DECL object reduce(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("reduce")(a0, a1, a2);
}

BOOST_PYTHON_DECL object reload(object const& a0) {
    return object((python::detail::new_reference)::PyImport_ReloadModule(a0.ptr()));
}

BOOST_PYTHON_DECL object repr(object const& a0) {
    return object((python::detail::new_reference)::PyObject_Repr(a0.ptr()));
}

BOOST_PYTHON_DECL object round(object const& a0) {
    return api_detail::get_func("round")(a0);
}

BOOST_PYTHON_DECL object round(double const& a0) {
    return api_detail::get_func("round")(object(a0));
}

BOOST_PYTHON_DECL object round(object const& a0, object const& a1) {
    return api_detail::get_func("round")(a0, a1);
}

BOOST_PYTHON_DECL object round(double const& a0, double const& a1) {
    return api_detail::get_func("round")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object slice(object const& a0) {
    return api_detail::get_func("slice")(a0);
}

BOOST_PYTHON_DECL object slice(int a0) {
    return api_detail::get_func("slice")(object(a0));
}

BOOST_PYTHON_DECL object slice(object const& a0, object const& a1) {
    return api_detail::get_func("slice")(a0, a1);
}

BOOST_PYTHON_DECL object slice(int a0, int a1) {
    return api_detail::get_func("slice")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object slice(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("slice")(a0, a1, a2);
}

BOOST_PYTHON_DECL object slice(int a0, int a1, int a2) {
    return api_detail::get_func("slice")(object(a0), object(a1), object(a2));
}

BOOST_PYTHON_DECL object str(object const& a0) {
    return object((python::detail::new_reference)::PyObject_Str(a0.ptr()));
}

BOOST_PYTHON_DECL object tuple() {
    return api_detail::get_func("tuple")();
}

BOOST_PYTHON_DECL object tuple(object const& a0) {
    return api_detail::get_func("tuple")(a0);
}

BOOST_PYTHON_DECL object type_(object const& a0) {
    return object((python::detail::new_reference)::PyObject_Type(a0.ptr()));
}

BOOST_PYTHON_DECL object unichr(object const& a0) {
    return api_detail::get_func("unichr")(a0);
}

BOOST_PYTHON_DECL object unichr(short a0) {
    return api_detail::get_func("unichr")(object(a0));
}

BOOST_PYTHON_DECL object unichr(int a0) {
    return api_detail::get_func("unichr")(object(a0));
}

BOOST_PYTHON_DECL object unichr(long a0) {
    return api_detail::get_func("unichr")(object(a0));
}

BOOST_PYTHON_DECL object unicode(object const& a0) {
    return object((python::detail::new_reference)::PyObject_Unicode(a0.ptr()));
}

BOOST_PYTHON_DECL object unicode(object const& a0, object const& a1) {
    return api_detail::get_func("unicode")(a0, a1);
}

BOOST_PYTHON_DECL object unicode(object const& a0, const char* a1) {
    return api_detail::get_func("unicode")(a0, object(a1));
}

BOOST_PYTHON_DECL object unicode(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("unicode")(a0, a1, a2);
}

BOOST_PYTHON_DECL object unicode(object const& a0, const char* a1, const char* a2) {
    return api_detail::get_func("unicode")(a0, object(a1), object(a2));
}

BOOST_PYTHON_DECL object vars() {
    return api_detail::get_func("vars")();
}

BOOST_PYTHON_DECL object vars(object const& a0) {
    return api_detail::get_func("vars")(a0);
}

BOOST_PYTHON_DECL object xrange(object const& a0) {
    return api_detail::get_func("xrange")(a0);
}

BOOST_PYTHON_DECL object xrange(int a0) {
    return api_detail::get_func("xrange")(object(a0));
}

BOOST_PYTHON_DECL object xrange(object const& a0, object const& a1) {
    return api_detail::get_func("xrange")(a0, a1);
}

BOOST_PYTHON_DECL object xrange(int a0, int a1) {
    return api_detail::get_func("xrange")(object(a0), object(a1));
}

BOOST_PYTHON_DECL object xrange(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("xrange")(a0, a1, a2);
}

BOOST_PYTHON_DECL object xrange(int a0, int a1, int a2) {
    return api_detail::get_func("xrange")(object(a0), object(a1), object(a2));
}

BOOST_PYTHON_DECL object zip(object const& a0) {
    return api_detail::get_func("zip")(a0);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1) {
    return api_detail::get_func("zip")(a0, a1);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2) {
    return api_detail::get_func("zip")(a0, a1, a2);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::get_func("zip")(a0, a1, a2, a3);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::get_func("zip")(a0, a1, a2, a3, a4);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::get_func("zip")(a0, a1, a2, a3, a4, a5);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::get_func("zip")(a0, a1, a2, a3, a4, a5, a6);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::get_func("zip")(a0, a1, a2, a3, a4, a5, a6, a7);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::get_func("zip")(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}

BOOST_PYTHON_DECL object zip(object const& a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::get_func("zip")(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

BOOST_PYTHON_DECL object compile_string(const char* a0, const char* a1, int a2) {
    return object((python::detail::new_reference)::Py_CompileString(const_cast<char*>(a0), const_cast<char*>(a1), a2));
}

BOOST_PYTHON_DECL int import_append_inittab(const char* a0, void(*a1)(void)) {
    int r = ::PyImport_AppendInittab(const_cast<char*>(a0), a1);
    if(r == -1)
        throw_error_already_set();
    return r;
}

BOOST_PYTHON_DECL object import_add_module(const char* a0) {
    return object((python::detail::borrowed_reference)::PyImport_AddModule(const_cast<char*>(a0)));
}

BOOST_PYTHON_DECL object import_get_module_dict() {
    return object((python::detail::borrowed_reference)::PyImport_GetModuleDict());
}

BOOST_PYTHON_DECL object import_import(object const& a0) {
    return object((python::detail::new_reference)::PyImport_Import(a0.ptr()));
}

BOOST_PYTHON_DECL object import_import(const char* a0) {
    return object((python::detail::new_reference)::PyImport_Import(object(a0).ptr()));
}

BOOST_PYTHON_DECL object import_import_module(const char* a0) {
    return object((python::detail::new_reference)::PyImport_ImportModule(const_cast<char*>(a0)));
}

BOOST_PYTHON_DECL object import_import_module_ex(const char* a0, object const& a1, object const& a2, object const& a3) {
    return object((python::detail::new_reference)::PyImport_ImportModuleEx(const_cast<char*>(a0), a1.ptr(), a2.ptr(), a3.ptr()));
}

BOOST_PYTHON_DECL object module_get_dict(object const& a0) {
    return object((python::detail::borrowed_reference)::PyModule_GetDict(a0.ptr()));
}

BOOST_PYTHON_DECL int object_print(object const& a0, FILE* a1, int a2) {
    int r = ::PyObject_Print(a0.ptr(), a1, a2);
    if(r == -1)
        throw_error_already_set();
    return r;
}

BOOST_PYTHON_DECL object run_file(FILE* a0, const char* a1, int a2, object const& a3, object const& a4) {
    return object((python::detail::new_reference)::PyRun_File(a0, const_cast<char*>(a1), a2, a3.ptr(), a4.ptr()));
}

BOOST_PYTHON_DECL int run_simple_file(FILE* a0, const char* a1) {
    int r = ::PyRun_SimpleFile(a0, const_cast<char*>(a1));
    if(r == -1)
        throw_error_already_set();
    return r;
}

BOOST_PYTHON_DECL int run_simple_string(const char* a0) {
    int r = ::PyRun_SimpleString(const_cast<char*>(a0));
    if(r == -1)
        throw_error_already_set();
    return r;
}

BOOST_PYTHON_DECL object run_string(const char* a0, int a1, object const& a2, object const& a3) {
    return object((python::detail::new_reference)::PyRun_String(const_cast<char*>(a0), a1, a2.ptr(), a3.ptr()));
}

BOOST_PYTHON_DECL object call_statement(const char* a0) {
    return api_detail::call_statement(a0);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1) {
    return api_detail::call_statement_du(a0, a1);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1) {
    return api_detail::call_statement(a0, 1, &a1);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2) {
    return api_detail::call_statement(a0, 2, &a1, &a2);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3) {
    return api_detail::call_statement(a0, 3, &a1, &a2, &a3);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::call_statement(a0, 4, &a1, &a2, &a3, &a4);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::call_statement(a0, 5, &a1, &a2, &a3, &a4, &a5);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::call_statement(a0, 6, &a1, &a2, &a3, &a4, &a5, &a6);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::call_statement(a0, 7, &a1, &a2, &a3, &a4, &a5, &a6, &a7);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::call_statement(a0, 8, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::call_statement(a0, 9, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, object const& a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10) {
    return api_detail::call_statement(a0, 10, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2) {
    return api_detail::call_statement_du(a0, a1, 1, &a2);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3) {
    return api_detail::call_statement_du(a0, a1, 2, &a2, &a3);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4) {
    return api_detail::call_statement_du(a0, a1, 3, &a2, &a3, &a4);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5) {
    return api_detail::call_statement_du(a0, a1, 4, &a2, &a3, &a4, &a5);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6) {
    return api_detail::call_statement_du(a0, a1, 5, &a2, &a3, &a4, &a5, &a6);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7) {
    return api_detail::call_statement_du(a0, a1, 6, &a2, &a3, &a4, &a5, &a6, &a7);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8) {
    return api_detail::call_statement_du(a0, a1, 7, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9) {
    return api_detail::call_statement_du(a0, a1, 8, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10) {
    return api_detail::call_statement_du(a0, a1, 9, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10);
}

BOOST_PYTHON_DECL object call_statement(const char* a0, call_dict_usage a1, object const& a2, object const& a3, object const& a4, object const& a5, object const& a6, object const& a7, object const& a8, object const& a9, object const& a10, object const& a11) {
    return api_detail::call_statement_du(a0, a1, 10, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10, &a11);
}


}}}

