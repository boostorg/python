#include <boost/python/str.hpp>
#include <boost/python/extract.hpp>

namespace boost { namespace python {

BOOST_PYTHON_DECL detail::new_reference str::call(object const& arg)
{
    return (detail::new_reference)PyObject_CallFunction(
        (PyObject*)&PyString_Type, "(O)", 
        arg.ptr());
} 

BOOST_PYTHON_DECL str::str(const char* s)
    : object(detail::new_reference(PyString_FromString(s)))
{}

BOOST_PYTHON_DECL str::str(object_cref other)
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
BOOST_PYTHON_DECL str str::capitalize() const
{
    return assume_str(this->attr("capitalize")());
}

BOOST_PYTHON_DECL str str::center(object_cref width) const
{
    return assume_str(
        this->attr("center")(width)
        );
}

BOOST_PYTHON_DECL long str::count(object_cref sub) const
{
    return extract<long>(this->attr("count")(sub));
}

BOOST_PYTHON_DECL long str::count(object_cref sub, object_cref start) const
{
    return extract<long>(this->attr("count")(sub,start));
}

BOOST_PYTHON_DECL long str::count(object_cref sub, object_cref start, object_cref end) const
{
    return extract<long>(this->attr("count")(sub,start,end));
}

BOOST_PYTHON_DECL object str::decode() const
{
    return this->attr("decode")();
}

BOOST_PYTHON_DECL object str::decode(object_cref encoding) const
{
    return this->attr("decode")(encoding);
}

BOOST_PYTHON_DECL object str::decode(object_cref encoding, object_cref errors) const
{
    return this->attr("decode")(encoding,errors);
}

BOOST_PYTHON_DECL object str::encode() const
{
    return this->attr("encode")();
}

BOOST_PYTHON_DECL object str::encode(object_cref encoding) const
{
    return this->attr("encode")(encoding);
}

BOOST_PYTHON_DECL object str::encode(object_cref encoding, object_cref errors) const
{
    return this->attr("encode")(encoding,errors);
}

BOOST_PYTHON_DECL bool str::endswith(object_cref suffix) const
{
    bool result = PyInt_AsLong(this->attr("endswith")(suffix).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL str str::expandtabs() const
{
    return assume_str(this->attr("expandtabs")());
}

BOOST_PYTHON_DECL str str::expandtabs(object_cref tabsize) const
{
    return assume_str(this->attr("expandtabs")(tabsize));
}

BOOST_PYTHON_DECL long str::find(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("find")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::find(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("find")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::find(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("find")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::index(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("index")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::index(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("index")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::index(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("index")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::isalnum() const
{
    bool result = PyInt_AsLong(this->attr("isalnum")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::isalpha() const
{
    bool result = PyInt_AsLong(this->attr("isalpha")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::isdigit() const
{
    bool result = PyInt_AsLong(this->attr("isdigit")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::islower() const
{
    bool result = PyInt_AsLong(this->attr("islower")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::isspace() const
{
    bool result = PyInt_AsLong(this->attr("isspace")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::istitle() const
{
    bool result = PyInt_AsLong(this->attr("istitle")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::isupper() const
{
    bool result = PyInt_AsLong(this->attr("isupper")().ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL str str::join(object_cref sequence) const
{
    return assume_str(this->attr("join")(sequence));
}

BOOST_PYTHON_DECL str str::ljust(object_cref width) const
{
    return assume_str(this->attr("ljust")(width));
}

BOOST_PYTHON_DECL str str::lower() const
{
    return assume_str(this->attr("lower")());
}

BOOST_PYTHON_DECL str str::lstrip() const
{
    return assume_str(this->attr("lstrip")());
}

BOOST_PYTHON_DECL str str::replace(object_cref old, object_cref new_) const 
{
    return assume_str(this->attr("replace")(old,new_));
}

BOOST_PYTHON_DECL str str::replace(object_cref old, object_cref new_, object_cref maxsplit) const {
    return assume_str(this->attr("replace")(old,new_,maxsplit));
}

BOOST_PYTHON_DECL long str::rfind(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("rfind")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::rfind(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("rfind")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::rfind(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("rfind")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::rindex(object_cref sub) const
{
    long result = PyInt_AsLong(this->attr("rindex")(sub).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::rindex(object_cref sub, object_cref start) const
{
    long result = PyInt_AsLong(this->attr("rindex")(sub,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL long str::rindex(object_cref sub, object_cref start, object_cref end) const
{
    long result = PyInt_AsLong(this->attr("rindex")(sub,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL str str::rjust(object_cref width) const
{
    return assume_str(this->attr("rjust")(width));
}

BOOST_PYTHON_DECL str str::rstrip() const
{
    return assume_str(this->attr("rstrip")());
}

BOOST_PYTHON_DECL list str::split() const
{
    return list(this->attr("split")());
}

BOOST_PYTHON_DECL list str::split(object_cref sep) const
{
    return list(this->attr("split")(sep));
}

BOOST_PYTHON_DECL list str::split(object_cref sep, object_cref maxsplit) const
{
    return list(this->attr("split")(sep,maxsplit));
}

BOOST_PYTHON_DECL list str::splitlines() const
{
    return list(this->attr("splitlines")());
}

BOOST_PYTHON_DECL list str::splitlines(object_cref keepends) const
{
    return list(this->attr("splitlines")(keepends));
}

BOOST_PYTHON_DECL bool str::startswith(object_cref prefix) const
{
    bool result = PyInt_AsLong(this->attr("startswith")(prefix).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::startswith(object_cref prefix, object_cref start) const
{
    bool result = PyInt_AsLong(this->attr("startswith")(prefix,start).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL bool str::startswith(object_cref prefix, object_cref start, object_cref end) const
{
    bool result = PyInt_AsLong(this->attr("startswith")(prefix,start,end).ptr());
    if (PyErr_Occurred())
        throw_error_already_set();
    return result;
}

BOOST_PYTHON_DECL str str::strip() const
{
    return assume_str(this->attr("strip")());
}

BOOST_PYTHON_DECL str str::swapcase() const
{
    return assume_str(this->attr("swapcase")());
}

BOOST_PYTHON_DECL str str::title() const
{
    return assume_str(this->attr("title")());
}

BOOST_PYTHON_DECL str str::translate(object_cref table) const
{
    return assume_str(this->attr("translate")(table));
}

BOOST_PYTHON_DECL str str::translate(object_cref table, object_cref deletechars) const
{
    return assume_str(this->attr("translate")(table,deletechars));
}

BOOST_PYTHON_DECL str str::upper() const
{
    return assume_str(this->attr("upper")());
}

}}  // namespace boost::python
