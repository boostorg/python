#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>

namespace boost { namespace python {
    
namespace
{
  // When returning list objects from methods, it may turn out that the
  // derived class is returning something else, perhaps something not
  // even derived from list. Since it is generally harmless for a
  // Boost.Python wrapper object to hold an object of a different
  // type, and because calling list() with an object may in fact
  // perform a conversion, the least-bad alternative is to assume that
  // we have a Python list object and stuff it into the list result.
  list assume_list(object const& o)
  {
      return list(detail::borrowed_reference(o.ptr()));
  }

  // No PyDict_CheckExact; roll our own.
  inline bool check_exact(dict const* p)
  {
      return  p->ptr()->ob_type == &PyDict_Type;
  }
}

BOOST_PYTHON_DECL detail::new_reference dict::call(object const& arg)
{
    return (detail::new_reference)PyObject_CallFunction(
        (PyObject*)&PyDict_Type, "(O)", 
        arg.ptr());
}

BOOST_PYTHON_DECL dict::dict()
    : object(detail::new_reference(PyDict_New()))
{}
    
BOOST_PYTHON_DECL dict::dict(object_cref data)
    : object(dict::call(data))
{}
    
BOOST_PYTHON_DECL void dict::clear()
{
    if (check_exact(this))
        PyDict_Clear(this->ptr());
    else
        this->attr("clear")();
}

BOOST_PYTHON_DECL dict dict::copy()
{
    if (check_exact(this))
    {
        return dict(detail::new_reference(
                        PyDict_Copy(this->ptr())));
    }
    else
    {
        return dict(detail::borrowed_reference(
                        this->attr("copy")().ptr()
                        ));
    }
}

BOOST_PYTHON_DECL object dict::get(object_cref k) const
{
    if (check_exact(this))
    {
        return object(detail::borrowed_reference(
                          PyDict_GetItem(this->ptr(),k.ptr())));
    }
    else
    {
        return this->attr("get")(k);
    }
}

BOOST_PYTHON_DECL object dict::get(object_cref k, object_cref d) const
{
    return this->attr("get")(k,d);
}

BOOST_PYTHON_DECL bool dict::has_key(object_cref k) const
{
    return extract<bool>(this->attr("has_key")(k)); 
}

BOOST_PYTHON_DECL list dict::items() const
{
    if (check_exact(this))
    {
        return list(detail::new_reference(
                        PyDict_Items(this->ptr())));
    }
    else
    {
        return assume_list(this->attr("items")());
    }
}

BOOST_PYTHON_DECL object dict::iteritems() const
{
    return this->attr("iteritems")();
}

BOOST_PYTHON_DECL object dict::iterkeys() const
{
    return this->attr("iterkeys")();
}

BOOST_PYTHON_DECL object dict::itervalues() const
{
    return this->attr("itervalues")();
}

BOOST_PYTHON_DECL list dict::keys() const
{
    if (check_exact(this))
    {
        return list(detail::new_reference(
                        PyDict_Keys(this->ptr())));
    }
    else
    {
        return assume_list(this->attr("keys")());
    }
}

BOOST_PYTHON_DECL tuple dict::popitem()
{
    return tuple(detail::borrowed_reference(
                     this->attr("popitem")().ptr()
                     ));
}

BOOST_PYTHON_DECL object dict::setdefault(object_cref k)
{
    return this->attr("setdefault")(k);
}

BOOST_PYTHON_DECL object dict::setdefault(object_cref k, object_cref d)
{
    return this->attr("setdefault")(k,d);
}

BOOST_PYTHON_DECL void dict::update(object_cref other)
{
    if (check_exact(this))
    {
        if (PyDict_Update(this->ptr(),other.ptr()) == -1)
            throw_error_already_set();
    }
    else
    {
        this->attr("update")(other);
    }
}

BOOST_PYTHON_DECL list dict::values() const
{
    if (check_exact(this))
    {
        return list(detail::new_reference(
                        PyDict_Values(this->ptr())));
    }
    else
    {
        return assume_list(this->attr("values")());
    }
}

}}  // namespace boost::python
