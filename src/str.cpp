#include <boost/python/str.hpp>
#include <boost/python/extract.hpp>

namespace boost { namespace python {

detail::new_reference str::call(object const& arg_)
{
    return (detail::new_reference)PyObject_CallFunction(
        (PyObject*)&PyString_Type, "(O)", 
        arg_.ptr());
} 

str::str()
    : object(detail::new_reference(PyString_FromString("")))
{}

str::str(const char* s)
    : object(detail::new_reference(PyString_FromString(s)))
{}

str::str(object_cref other)
    : object(str::call(other))
{}

namespace
{
  // When returning str objects from methods, it may turn out that the
  // derived class is returning something else, perhaps something not
  // even derived from str. Since it is generally harmless for a
  // Boost.Python wrapper object to hold an object of a different
  // type, and because calling str() with an object may in fact
  // perform a conversion, the least-bad alternative is to assume that
  // we have a Python str object and stuff it into the str result.
  str assume_str(object const& o)
  {
      return str(detail::borrowed_reference(o.ptr()));
  }
}
str str::capitalize() const
{
    return assume_str(this->attr("capitalize")());
}

str str::center(object_cref width) const
{
    return assume_str(
        this->attr("center")(width)
        );
}

long str::count(object_cref sub) const
{
    return extract<long>(this->attr("count")(sub));
}

long str::count(object_cref sub, object_cref start) const
{
    return extract<long>(this->attr("count")(sub,start));
}

long str::count(object_cref sub, object_cref start, object_cref end) const
{
    return extract<long>(this->attr("count")(sub,start,end));
}

object str::decode() const
{
    return this->attr("decode")();
}

object str::decode(object_cref encoding) const
{
    return this->attr("decode")(encoding);
}

object str::decode(object_cref encoding, object_cref errors) const
{
    return this->attr("decode")(encoding,errors);
}

object str::encode() const
{
    return this->attr("encode")();
}

object str::encode(object_cref encoding) const
{
    return this->attr("encode")(encoding);
}

object str::encode(object_cref encoding, object_cref errors) const
{
    return this->attr("encode")(encoding,errors);
}

bool str::endswith(object_cref suffix) const
{
    bool result = PyInt_AsLong(this->attr("endswith")(suffix).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

str str::expandtabs() const
{
    return assume_str(this->attr("expandtabs")());
}

str str::expandtabs(object_cref tabsize) const
{
    return assume_str(this->attr("expandtabs")(tabsize));
}

long str::find(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("find")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::find(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("find")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::find(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("find")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::index(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("index")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::index(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("index")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::index(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("index")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::isalnum() const
{
    bool result = PyInt_AsLong(this->attr("isalnum")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::isalpha() const
{
    bool result = PyInt_AsLong(this->attr("isalpha")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::isdigit() const
{
    bool result = PyInt_AsLong(this->attr("isdigit")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::islower() const
{
    bool result = PyInt_AsLong(this->attr("islower")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::isspace() const
{
    bool result = PyInt_AsLong(this->attr("isspace")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::istitle() const
{
    bool result = PyInt_AsLong(this->attr("istitle")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::isupper() const
{
    bool result = PyInt_AsLong(this->attr("isupper")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

str str::join(object_cref sequence) const
{
    return assume_str(this->attr("join")(sequence));
}

str str::ljust(object_cref width) const
{
    return assume_str(this->attr("ljust")(width));
}

str str::lower() const
{
    return assume_str(this->attr("lower")());
}

str str::lstrip() const
{
    return assume_str(this->attr("lstrip")());
}

str str::replace(object_cref old, object_cref new_) const 
{
    return assume_str(this->attr("replace")(old,new_));
}

str str::replace(object_cref old, object_cref new_, object_cref maxsplit) const {
    return assume_str(this->attr("replace")(old,new_,maxsplit));
}

long str::rfind(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("rfind")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::rfind(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("rfind")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::rfind(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("rfind")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::rindex(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("rindex")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::rindex(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("rindex")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

long str::rindex(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("rindex")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

str str::rjust(object_cref width) const
{
    return assume_str(this->attr("rjust")(width));
}

str str::rstrip() const
{
    return assume_str(this->attr("rstrip")());
}

list str::split() const
{
    return list(this->attr("split")());
}

list str::split(object_cref sep) const
{
    return list(this->attr("split")(sep));
}

list str::split(object_cref sep, object_cref maxsplit) const
{
    return list(this->attr("split")(sep,maxsplit));
}

list str::splitlines() const
{
    return list(this->attr("splitlines")());
}

list str::splitlines(object_cref keepends) const
{
    return list(this->attr("splitlines")(keepends));
}

bool str::startswith(object_cref prefix) const
{
    bool result = PyInt_AsLong(this->attr("startswith")(prefix).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::startswith(object_cref prefix, object_cref start) const
{
    bool result = PyInt_AsLong(this->attr("startswith")(prefix,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

bool str::startswith(object_cref prefix, object_cref start, object_cref end) const
{
    bool result = PyInt_AsLong(this->attr("startswith")(prefix,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

str str::strip() const
{
    return assume_str(this->attr("strip")());
}

str str::swapcase() const
{
    return assume_str(this->attr("swapcase")());
}

str str::title() const
{
    return assume_str(this->attr("title")());
}

str str::translate(object_cref table) const
{
    return assume_str(this->attr("translate")(table));
}

str str::translate(object_cref table, object_cref deletechars) const
{
    return assume_str(this->attr("translate")(table,deletechars));
}

str str::upper() const
{
    return assume_str(this->attr("upper")());
}

}}  // namespace boost::python
