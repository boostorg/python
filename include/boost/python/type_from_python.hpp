// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TYPE_FROM_PYTHON_DWA2002130_HPP
# define TYPE_FROM_PYTHON_DWA2002130_HPP

namespace boost { namespace python {

template <PyTypeObject const* python_type>
struct type_from_python
{
    static void* convertible(PyObject* op)
    {
        return PyObject_TypeCheck(
            op, const_cast<PyTypeObject*>(python_type)) ? op : 0;
    }
};

}} // namespace boost::python

#endif // TYPE_FROM_PYTHON_DWA2002130_HPP
