#include <boost/python/tuple.hpp>

namespace boost { namespace python {

BOOST_PYTHON_DECL detail::new_reference tuple::call(object const& arg)
{
    return (detail::new_reference)PyObject_CallFunction(
        (PyObject*)&PyTuple_Type, "(O)", 
        arg.ptr());
}
    
BOOST_PYTHON_DECL tuple::tuple()
    : object(detail::new_reference(PyTuple_New(0)))
{}
    
BOOST_PYTHON_DECL tuple::tuple(object_cref sequence)
    : object(tuple::call(sequence))
{}

}}  // namespace boost::python
