# Copyright David Hawkes 2002.
# Permission is hereby granted to copy, use and modify this software
# for any purpose, including commercial distribution, provided this
# copyright notice is not removed. No warranty WHATSOEVER is provided with this
# software. Any user(s) accepts this software "as is" and as such they will not
# bind the author(s) to any claim of suitabilty for any purpose.

# Build python API wrappers for boost python

import re

API_List = [
'PyObject*{new} abs{direct}(int{template})',
'PyObject*{new} abs{direct}(PyObject*)',
'PyObject*{new} abs{direct}(short)',
'PyObject*{new} abs{direct}(int)',
'PyObject*{new} abs{direct}(long)',
'PyObject*{new} abs{direct}(double const &)',
'PyObject*{new,err=NULL} PyObject_CallObject{decl=apply}(PyObject*,PyObject*)',
'PyObject*{new,err=NULL} PyObject_Call{decl=apply}(PyObject*,PyObject*,PyObject*)',
'bool PyCallable_Check{decl=callable}(PyObject*)',
'PyObject*{new} chr{direct}(int{template})',
'PyObject*{new} chr{direct}(PyObject*)',
'PyObject*{new} chr{direct}(short)',
'PyObject*{new} chr{direct}(int)',
'PyObject*{new} chr{direct}(long)',
'int{err=-1} PyObject_Cmp{decl=cmp}(PyObject*{template},PyObject*{template},int{result})',
'int{err=-1} PyObject_Cmp{decl=cmp}(PyObject*,PyObject*,int{result})',
'PyObject*{new} coerce{direct}(PyObject*,PyObject*)',
'PyObject*{new} compile{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} compile{direct}(const char*,const char*,const char*)',
'PyObject*{new} compile{direct}(PyObject*,PyObject*,PyObject*,PyObject*)',
'PyObject*{new} compile{direct}(const char*,const char*,const char*,int)',
'PyObject*{new} compile{direct}(PyObject*,PyObject*,PyObject*,PyObject*,PyObject*)',
'PyObject*{new} compile{direct}(const char*,const char*,const char*,int,int)',
'PyObject*{new} complex{direct}(int{template})',
'PyObject*{new} complex{direct}(PyObject*)',
'PyObject*{new} complex{direct}(double const&)',
'PyObject*{new} complex{direct}(int{template},int{template})',
'PyObject*{new} complex{direct}(PyObject*,PyObject*)',
'PyObject*{new} complex{direct}(double const&,double const&)',
'PyObject*{new} dict{direct}()',
'PyObject*{new} dict{direct}(PyObject*)',
'PyObject*{new} PyObject_Dir{decl=dir}(PyObject*{value=NULL})',
'PyObject*{new} PyObject_Dir{decl=dir}(PyObject*)',
'PyObject*{new} divmod{direct}(int{template},int{template})',
'PyObject*{new} divmod{direct}(PyObject*,PyObject*)',
'PyObject*{new} divmod{direct}(int,int)',
'PyObject*{new} divmod{direct}(long,long)',
'PyObject*{new} divmod{direct}(double const&,double const&)',
'PyObject*{new} PyRun_String{decl=eval}(char*{const},int{value=Py_eval_input},PyObject*{value=globals().ptr()},PyObject*{value=globals().ptr()})',
'PyObject*{new} PyRun_String{decl=eval}(char*{const},int{value=Py_eval_input},PyObject*,PyObject*{value=globals().ptr()})',
'PyObject*{new} PyRun_String{decl=eval}(char*{const},int{value=Py_eval_input},PyObject*,PyObject*)',
'PyObject*{new} PyRun_String{decl=exec}(char*{const},int{value=Py_file_input},PyObject*{value=globals().ptr()},PyObject*{value=globals().ptr()})',
'PyObject*{new} PyRun_String{decl=exec}(char*{const},int{value=Py_file_input},PyObject*,PyObject*{value=globals().ptr()})',
'PyObject*{new} PyRun_String{decl=exec}(char*{const},int{value=Py_file_input},PyObject*,PyObject*)',
'PyObject*{new} execfile{direct}(PyObject*)',
'PyObject*{new} execfile{direct}(PyObject*,PyObject*)',
'PyObject*{new} execfile{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} file{direct}(PyObject*)',
'PyObject*{new} file{direct}(const char*)',
'PyObject*{new} file{direct}(PyObject*,PyObject*)',
'PyObject*{new} file{direct}(const char*,const char*)',
'PyObject*{new} file{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} file{direct}(const char*,const char*,int)',
'PyObject*{new} filter{direct}(PyObject*,PyObject*)',
'PyObject*{new} float{direct,decl=float_}(PyObject*)',
'PyObject*{new} float{direct,decl=float_}(const char*)',
'PyObject*{new} float{direct,decl=float_}(double const&)',
'PyObject*{new} getattr{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} getattr{direct}(PyObject*,const char *,PyObject*)',
'PyObject*{borrowed,err=NULL} PyModule_GetDict{decl=globals}(PyObject*{value=PyImport_AddModule("__main__")})',
'bool PyObject_HasAttr{decl=hasattr}(PyObject*,PyObject*)',
'bool PyObject_HasAttrString{decl=hasattr}(PyObject*,char*{const})',
'long{err=-1} PyObject_Hash{decl=hash}(PyObject*)',
'PyObject*{new} hex{direct}(int{template})',
'PyObject*{new} hex{direct}(PyObject*)',
'PyObject*{new} hex{direct}(char)',
'PyObject*{new} hex{direct}(short)',
'PyObject*{new} hex{direct}(int)',
'PyObject*{new} hex{direct}(long)',
'long id{direct}(PyObject*)',
'PyObject*{new} input{direct}()',
'PyObject*{new} input{direct}(PyObject*)',
'PyObject*{new} input{direct}(const char*)',
'PyObject*{new} int{direct,decl=int_}(PyObject*)',
'PyObject*{new} int{direct,decl=int_}(long)',
'PyObject*{new} int{direct,decl=int_}(const char*)',
'PyObject*{new} intern{direct}(PyObject*)',
'PyObject*{new} intern{direct}(const char*)',
'bool PyObject_IsInstance{decl=isinstance}(PyObject*,PyObject*)',
'bool PyObject_IsSubclass{decl=issubclass}(PyObject*,PyObject*)',
'PyObject*{new} PyObject_GetIter{decl=iter}(PyObject*)',
'PyObject*{new} iter{direct}(PyObject*,PyObject*)',
'long{err=-1} PyObject_Length{decl=len}(PyObject*)',
'PyObject*{new} list{direct}()',
'PyObject*{new} list{direct}(PyObject*)',
'PyObject*{new} long{direct,decl=long_}(PyObject*)',
'PyObject*{new} long{direct,decl=long_}(long)',
'PyObject*{new} long{direct,decl=long_}(const char*)',
'PyObject*{new} map{direct,argrepeat}(PyObject*)',
'PyObject*{new} max{direct,argrepeat}(PyObject*{template})',
'PyObject*{new} max{direct,argrepeat}(PyObject*)',
'PyObject*{new} min{direct,argrepeat}(PyObject*{template})',
'PyObject*{new} min{direct,argrepeat}(PyObject*)',
'PyObject*{new} oct{direct}(int{template})',
'PyObject*{new} oct{direct}(PyObject*)',
'PyObject*{new} oct{direct}(char)',
'PyObject*{new} oct{direct}(short)',
'PyObject*{new} oct{direct}(int)',
'PyObject*{new} oct{direct}(long)',
'PyObject*{new} open{direct}(PyObject*)',
'PyObject*{new} open{direct}(const char*)',
'PyObject*{new} open{direct}(PyObject*,PyObject*)',
'PyObject*{new} open{direct}(const char*,const char*)',
'PyObject*{new} open{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} open{direct}(const char*,const char*,int)',
'long ord{direct}(PyObject*)',
'long ord{direct}(const char*)',
'PyObject*{new} pow{direct}(int{template},int{template})',
'PyObject*{new} pow{direct}(PyObject*,PyObject*)',
'PyObject*{new} pow{direct}(double const&,double const&)',
'PyObject*{new} pow{direct}(double const&,double const&,double const&)',
'PyObject*{new} print{direct,statement=print _1,argrepeat}(int{template})',
'PyObject*{new} print{direct,statement=print _1,argrepeat}(PyObject*)',
'PyObject*{new} print{decl=print_file,direct,statement="print >>_1, _2",argrepeat}(PyObject*,int{template})',
'PyObject*{new} print{decl=print_file,direct,statement="print >>_1, _2",argrepeat}(PyObject*,PyObject*)',
'PyObject*{new} range{direct}(int{template})',
'PyObject*{new} range{direct}(PyObject*)',
'PyObject*{new} range{direct}(int)',
'PyObject*{new} range{direct}(int{template},int{template})',
'PyObject*{new} range{direct}(PyObject*,PyObject*)',
'PyObject*{new} range{direct}(int,int)',
'PyObject*{new} range{direct}(int{template},int{template},int{template})',
'PyObject*{new} range{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} range{direct}(int,int,int)',
'PyObject*{new} raw_input{direct}()',
'PyObject*{new} raw_input{direct}(PyObject*)',
'PyObject*{new} raw_input{direct}(const char*)',
'PyObject*{new} reduce{direct}(PyObject*,PyObject*)',
'PyObject*{new} reduce{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new,err=NULL} PyImport_ReloadModule{decl=reload}(PyObject*)',
'PyObject*{new} PyObject_Repr{decl=repr}(PyObject*)',
'PyObject*{new} round{direct}(int{template})',
'PyObject*{new} round{direct}(PyObject*)',
'PyObject*{new} round{direct}(double const&)',
'PyObject*{new} round{direct}(int{template},int{template})',
'PyObject*{new} round{direct}(PyObject*,PyObject*)',
'PyObject*{new} round{direct}(double const&,double const&)',
'PyObject*{new} slice{direct}(int{template})',
'PyObject*{new} slice{direct}(PyObject*)',
'PyObject*{new} slice{direct}(int)',
'PyObject*{new} slice{direct}(int{template},int{template})',
'PyObject*{new} slice{direct}(PyObject*,PyObject*)',
'PyObject*{new} slice{direct}(int,int)',
'PyObject*{new} slice{direct}(int{template},int{template},int{template})',
'PyObject*{new} slice{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} slice{direct}(int,int,int)',
'PyObject*{new} PyObject_Str{decl=str}(PyObject*)',
'PyObject*{new} tuple{direct}()',
'PyObject*{new} tuple{direct}(PyObject*)',
'PyObject*{new,err=NULL} PyObject_Type{decl=type_}(PyObject*)',
'PyObject*{new} unichr{direct}(int{template})',
'PyObject*{new} unichr{direct}(PyObject*)',
'PyObject*{new} unichr{direct}(short)',
'PyObject*{new} unichr{direct}(int)',
'PyObject*{new} unichr{direct}(long)',
'PyObject*{new} PyObject_Unicode{decl=unicode}(PyObject*)',
'PyObject*{new} unicode{direct}(PyObject*,PyObject*)',
'PyObject*{new} unicode{direct}(PyObject*,const char*)',
'PyObject*{new} unicode{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} unicode{direct}(PyObject*,const char*,const char*)',
'PyObject*{new} vars{direct}()',
'PyObject*{new} vars{direct}(PyObject*)',
'PyObject*{new} xrange{direct}(int{template})',
'PyObject*{new} xrange{direct}(PyObject*)',
'PyObject*{new} xrange{direct}(int)',
'PyObject*{new} xrange{direct}(int{template},int{template})',
'PyObject*{new} xrange{direct}(PyObject*,PyObject*)',
'PyObject*{new} xrange{direct}(int,int)',
'PyObject*{new} xrange{direct}(int{template},int{template},int{template})',
'PyObject*{new} xrange{direct}(PyObject*,PyObject*,PyObject*)',
'PyObject*{new} xrange{direct}(int,int,int)',
'PyObject*{new} zip{direct,argrepeat}(PyObject*)',
'PyObject*{new,err=NULL} Py_CompileString{decl=compile_string}(char*{const},char*{const},int)',
'int{err=-1} PyImport_AppendInittab{decl=import_append_inittab}(char*{const},void(*arg)(void))',
'PyObject*{borrowed,err=NULL} PyImport_AddModule{decl=import_add_module}(char*{const})',
'PyObject*{borrowed,err=NULL} PyImport_GetModuleDict{decl=import_get_module_dict}()',
'PyObject*{new,err=NULL} PyImport_Import{decl=import_import}(PyObject*)',
'PyObject*{new,err=NULL} PyImport_Import{decl=import_import}(const char*{object})',
'PyObject*{new,err=NULL} PyImport_ImportModule{decl=import_import_module}(char*{const})',
'PyObject*{new,err=NULL} PyImport_ImportModuleEx{decl=import_import_module_ex}(char*{const},PyObject*,PyObject*,PyObject*)',
'PyObject*{borrowed,err=NULL} PyModule_GetDict{decl=module_get_dict}(PyObject*)',
'int{err=-1} PyObject_Print{decl=object_print}(PyObject*,FILE*,int)',
'PyObject*{new,err=NULL} PyRun_File{decl=run_file}(FILE*,char*{const},int,PyObject*,PyObject*)',
'int{err=-1} PyRun_SimpleFile{decl=run_simple_file}(FILE*,char*{const})',
'int{err=-1} PyRun_SimpleString{decl=run_simple_string}(char*{const})',
'PyObject*{new,err=NULL} PyRun_String{decl=run_string}(char*{const},int,PyObject*,PyObject*)',
'PyObject*{new} call_statement{statement,direct}(const char*{statement})',
'PyObject*{new} call_statement{statement,direct}(const char*{statement},call_dict_usage{use_gd})',
'PyObject*{new} call_statement{argrepeat,statement,direct}(const char*{statement},int{template})',
'PyObject*{new} call_statement{argrepeat,statement,direct}(const char*{statement},PyObject*)',
'PyObject*{new} call_statement{argrepeat,statement,direct}(const char*{statement},call_dict_usage{use_gd},int{template})',
'PyObject*{new} call_statement{argrepeat,statement,direct}(const char*{statement},call_dict_usage{use_gd},PyObject*)',
]

DeclFile = '../../../boost/python/py_interface.hpp'
ImplFile = 'py_interface.cpp'

DeclFileHeader = '''\
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

'''

DeclFileTrailer = '''\
}}}

#endif // PY_INTERFACE_HPP
'''

ImplFileHeader = '''\
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

'''

ImplFileTrailer = '''\
}}}
'''

def SplitOutList(l):
    vals_list = []
    if l == None:
        return vals_list
    vals_list = re.findall(r'((?:[^,{}]|(?:{[^{}]*}))+),?\s*', l)
    return vals_list

def SplitOutListDict(l):
    vals_dict = {}
    if l == None:
        return vals_dict
    vals = re.findall(r'((?:"[^"]+"|[^,"]+)+)\s*,?', l)
    for val in vals:
        m = re.match(r'(?P<aname>[^\s=]+)\s*(=\s*(?P<qt>"?)(?P<aval>.+)(?P=qt))?', val).groupdict()
        vals_dict[m['aname']] = m['aval']
    return vals_dict

def SplitOutAttrs(a):
    soa = {}
    m = re.match(r'(?P<name>[^{]+)({(?P<attrs>[^}]+)})?', a).groupdict()
    soa['name'] = m['name']
    soa.update(SplitOutListDict(m['attrs']))
    return soa

def is_object(name):
    if re.match(r'PyObject\s*\*', name['name']):
        return 1
    return 0

def is_arg_really_const(arg):
    return arg.has_key('const')

def get_actual_rtn_type(rtn, args):
    i = 0
    for a in args:
        if a.has_key('result'):
            true_rtn = dict(rtn)
            true_rtn['name'] = a['name']
            true_rtn['arg_number'] = i
            return true_rtn
        i += 1
    return rtn

def is_template(name):
    return name.has_key('template')

def decl_func_arg(arg, p):
    if arg.has_key('value'):
        return ''
    elif arg.has_key('result'):
        return ''
    elif is_object(arg):
        if is_template(arg):
            sn = str(p)
            return 'A' + sn +' const& a' + sn
        else:
            return 'object const& a' + str(p)
    elif is_arg_really_const(arg):
        return 'const ' + arg['name'] + ' a' + str(p)
    elif re.search(r'arg', arg['name']):
        return re.sub(r'arg', 'a' + str(p), arg['name'])
    else:
        if is_template(arg):
            sn = str(p)
            return 'A' + sn +' const& a' + sn
        else:
            return arg['name'] + ' a' + str(p)

def decl_func_args(name, args):
    if not len(args):
        return ''
    d_args = reduce(lambda x,y : x + (y and (', ' + y) or ''), map(decl_func_arg, args, xrange(len(args))))
    return d_args

def call_func_arg(arg, p):
    if arg.has_key('value'):
        return arg['value']
    elif arg.has_key('result'):
        return '&rslt'
    elif arg.has_key('template'):
        sn = str(p)
        return 'api_detail::get_arg<A%s>(a%s)' % (sn, sn)
    elif arg.has_key('object'):
        return 'object(a%s).ptr()' % str(p)
    elif is_object(arg):
        return 'a' + str(p) + '.ptr()'
    elif is_arg_really_const(arg):
        return 'const_cast<%s>(%s)' % (arg['name'], 'a' + str(p))
    else:
        return 'a' + str(p)

def call_func_args(args):
    if not len(args):
        return ''
    d_args = reduce(lambda x,y : x + (y and ((x and ', ' or '') + y) or ''), map(call_func_arg, args, xrange(len(args))))
    return d_args

def call_func(name, args):
    return '::%s(%s)' % (name['name'], call_func_args(args))

def call_func_direct_arg(arg, p):
    if arg.has_key('use_gd'):
        return ''
    elif arg.has_key('statement'):
        return ''
    elif arg.has_key('value'):
        return arg['value']
    elif arg.has_key('template'):
        sn = str(p)
        if arg.has_key('addr'):
            return '(object const*)api_detail::get_arg<A%s>(a%s)' % (sn, sn)
        else:
            return 'api_detail::get_arg<A%s>(a%s)' % (sn, sn)
    elif is_object(arg):
        if arg.has_key('addr'):
            return '&a' + str(p)
        else:
            return 'a' + str(p)
    else:
        if arg.has_key('addr'):
            return '&object(a%s)' % str(p)
        else:
            return 'object(a%s)' % str(p)
    
def call_func_direct_args(args):
    if not len(args):
        return ''
    d_args = reduce(lambda x,y : x + (y and ((x and ', ' or '') + y) or ''), map(call_func_direct_arg, args, xrange(len(args))))
    return d_args

def get_statement_arg(args):
    i = 0
    for arg in args:
        if arg.has_key('statement'):
            return i
        i = i + 1
    return -1

def get_use_gd_arg(args):
    i = 0
    for arg in args:
        if arg.has_key('use_gd'):
            return i
        i = i + 1
    return -1

def call_func_direct(name, args):
    if name.has_key('statement'):
        na = len(args)
        ugd = get_use_gd_arg(args)
        sa = get_statement_arg(args)
        if ugd >= 0:
            ugd = 'a' + str(ugd)
            na = na - 1
        else:
            if (sa < 0) and (na > 0):
                ugd = 'use_new_dict'
            else:
                ugd = None
        if sa >= 0:
            na = na - 1
            if na > 0:
                if ugd:
                    return 'api_detail::call_statement_du(%s, %s, %s, %s)' % ('a' + str(sa), ugd, na, call_func_direct_args(args))
                else:
                    return 'api_detail::call_statement(%s, %s, %s)' % ('a' + str(sa), na, call_func_direct_args(args))
            else:
                if ugd:
                    return 'api_detail::call_statement_du(%s, %s)' % ('a' + str(sa), ugd)
                else:
                    return 'api_detail::call_statement(%s)' % ('a' + str(sa))
        else:
            if na > 0:
                if ugd:
                    return 'api_detail::call_statement_du("%s", %s, %s, %s)' % (name['statement'], ugd, na, call_func_direct_args(args))
                else:
                    return 'api_detail::call_statement("%s", %s, %s)' % (name['statement'], na, call_func_direct_args(args))
            else:
                if ugd:
                    return 'api_detail::call_statement_du("%s", %s)' % (name['statement'], ugd)
                else:
                    return 'api_detail::call_statement("%s")' % (name['statement'])
    else:
        return 'api_detail::get_func("%s")(%s)' % (name['name'], call_func_direct_args(args))

def decl_template_arg(arg, p):
    if arg.has_key('value'):
        return ''
    elif arg.has_key('result'):
        return ''
    elif is_template(arg):
        return 'class A' + str(p)
    else:
        return ''

def decl_template_args(args):
    if not len(args):
        return ''
    d_args = reduce(lambda x,y : x + (y and ((x and ', ' or '') + y) or ''), map(decl_template_arg, args, xrange(len(args))))
    return d_args

def is_rtn_borrowed_object(rtn):
    if is_object(rtn):
        return rtn.has_key('borrowed')
    else:
        return 0

def is_rtn_new_object(rtn):
    if is_object(rtn):
        return not rtn.has_key('borrowed')
    else:
        return 0

def is_func_direct(name):
    return name.has_key('direct')

def rtn_call_func_direct(rtn, name, args):
    if rtn['name'] == 'void':
        direct_code = '    %s;' % call_func_direct(name, args)
    elif is_object(rtn):
        direct_code = '    return %s;' % call_func_direct(name, args)
    else:
        r = '''\
    object r(%s);
    return boost::python::arg_from_python<%s>(r.ptr())(r.ptr());'''
        direct_code = r % (call_func_direct(name, args), rtn['name'])
    return direct_code

def rtn_call_func(rtn, name, args):
    if is_func_direct(name):
        return rtn_call_func_direct(rtn, name, args)
    true_rtn = get_actual_rtn_type(rtn, args)
    err = true_rtn.get('err')
    arg_number = true_rtn.get('arg_number')
    if rtn['name'] == 'void':
        return '    %s;' % call_func(name, args)
    elif is_rtn_new_object(rtn):
        if err and (err != 'NULL'):
            r = '''\
    PyObject* r = %s;
    if(r == %s)
        throw_error_already_set();
    return object((python::detail::new_reference)r);'''
            return r % (call_func(name, args), err)
        else:
            return '    return object((python::detail::new_reference)%s);' % call_func(name, args)
    elif is_rtn_borrowed_object(rtn):
        if err and (err != 'NULL'):
            r = '''\
    PyObject* r = %s;
    if(r == %s)
        throw_error_already_set();
    return object((python::detail::borrowed_reference)r);'''
            return r % (call_func(name, args), err)
        else:
            return '    return object((python::detail::borrowed_reference)%s);' % call_func(name, args)
    else:
        if err:
            if arg_number == None:
                r = '''\
    %s r = %s;
    if(r == %s)
        throw_error_already_set();
    return r;'''
                return r % (rtn['name'], call_func(name, args), err)
            else:
                r = '''\
    %s rslt;
    %s r = %s;
    if(r == %s)
        throw_error_already_set();
    return rslt;'''
                return r % (true_rtn['name'], rtn['name'], call_func(name, args), err)
        else:
            return '    return %s;' % call_func(name, args)

def decl_func(name, args):
    return '%s(%s)' % (name.get('decl', name['name']), decl_func_args(name, args))

def rtn_decl_func(rtn, name, args):
    true_rtn = get_actual_rtn_type(rtn, args)
    ta = decl_template_args(args)
    if ta:
        decl = 'template<%s>\n' % ta
    else:
        decl = 'BOOST_PYTHON_DECL '
    if is_object(true_rtn):
        return decl + 'object %s' % decl_func(name, args)
    else:
        return decl + '%s %s' % (true_rtn['name'], decl_func(name, args))

def is_info_template(fn_info):
    for arg in fn_info['args']:
        if is_template(arg):
            return 1
    return 0

def parse_func(func):
    fn_info = {}
    fnm = re.match(r'(?P<rtn>\S+)\s+(?P<fname>[^\s\(\){}]+({[^{}]*})?)\s*\((?P<args>(({[^{}]*})+|(\([^\(\)]*\))+|[^\(\)]+)*)\)', func).groupdict()
    fn_info['fname'] = SplitOutAttrs(fnm['fname'])
    fn_info['rtn'] = SplitOutAttrs(fnm['rtn'])
    fn_info['args'] = map(SplitOutAttrs, SplitOutList(fnm['args']))
    if fn_info['fname'].has_key('statement'):
        if is_info_template(fn_info):
            for arg in fn_info['args']:
                if is_template(arg):
                    arg['addr'] = None
        else:
            for arg in fn_info['args']:
                if is_object(arg):
                    arg['addr'] = None
    return fn_info

def get_argrepeat(fn_info):
    if fn_info['fname'].has_key('argrepeat'):
        argrepeat = fn_info['fname']['argrepeat']
        if argrepeat == None:
            argrepeat = 10
    else:
        argrepeat = 1
    return argrepeat

def do_arg_repeat(fn_info):
    fn_info['args'] = fn_info['args'] + [fn_info['args'][len(fn_info['args']) - 1],]
    if fn_info['fname'].has_key('statement'):
        stmt = fn_info['fname']['statement']
        if stmt:
            s_args = re.findall(r'[\s,\(](?:_([0-9]+))(?=$|[\s,\)])', stmt)
            if s_args:
                mx = reduce(max, map(int, s_args), 0)
                mx_arg = '_' + str(mx)
                next_arg = '_' + str(mx + 1)
                stmt = re.sub(r'(?<=[\s,\(])' + mx_arg + '(?=$|[\s,\)])', mx_arg + ', ' + next_arg, stmt, 1)
                fn_info['fname']['statement'] = stmt
    
def decl_funcs(fn_list):
    fn_defs = ''
    for fn in fn_list:
        fn_info = parse_func(fn)
        argrepeat = get_argrepeat(fn_info)
        for ar in xrange(argrepeat):
            fn_defs += rtn_decl_func(fn_info['rtn'], fn_info['fname'], fn_info['args'])
            if is_info_template(fn_info):
                fn_defs += '\n{\n' + rtn_call_func(fn_info['rtn'], fn_info['fname'], fn_info['args']) + '\n}\n'
            else:
                fn_defs += ';\n'
            if ar != (argrepeat - 1):
                do_arg_repeat(fn_info)
    return fn_defs
    
def impl_funcs(fn_list):
    fn_defs = ''
    for fn in fn_list:
        fn_info = parse_func(fn)
        if is_info_template(fn_info):
            continue
        argrepeat = get_argrepeat(fn_info)
        for ar in xrange(argrepeat):
            fn_defs += rtn_decl_func(fn_info['rtn'], fn_info['fname'], fn_info['args']) + ' {\n'
            fn_defs += rtn_call_func(fn_info['rtn'], fn_info['fname'], fn_info['args']) + '\n}\n\n'
            if ar != (argrepeat - 1):
                do_arg_repeat(fn_info)
    return fn_defs

if __name__ == '__main__':
    f = file(DeclFile, 'w')
    print >>f, DeclFileHeader
    print >>f, decl_funcs(API_List)
    print >>f, DeclFileTrailer
    f.close()

    f = file(ImplFile, 'w')
    print >>f, ImplFileHeader
    print >>f, impl_funcs(API_List)
    print >>f, ImplFileTrailer
    f.close()
