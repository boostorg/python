// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_WRAPPER_DWA20011221_HPP
# define CLASS_WRAPPER_DWA20011221_HPP

# include <boost/python/to_python_converter.hpp>
# include <boost/ref.hpp>

namespace boost { namespace python { namespace objects { 

// Used to convert objects of type Src to wrapped C++ classes by
// building a new instance object and installing a Holder constructed
// from the Src object.
template <class Src, class Holder, class MakeInstance>
struct class_wrapper
    : to_python_converter<Src,class_wrapper<Src,Holder,MakeInstance> >
{
    static PyObject* convert(Src const& x)
    {
        return MakeInstance::execute(cref(x));
    }
};

}}} // namespace boost::python::objects

#endif // CLASS_WRAPPER_DWA20011221_HPP
