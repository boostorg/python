#include <boost/python/tuple.hpp>

namespace boost { namespace python {

detail::new_reference tuple::call(object const& arg_)
{
    return (detail::new_reference)PyObject_CallFunction(
        (PyObject*)&PyTuple_Type, "(O)", 
        arg_.ptr());
}
    
tuple::tuple()
    : object(detail::new_reference(PyTuple_New(0)))
{}
    
tuple::tuple(object_cref sequence)
    : object(tuple::call(sequence))
{}

}}  // namespace boost::python
