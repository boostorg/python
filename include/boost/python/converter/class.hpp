// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA20011215_HPP
# define CLASS_DWA20011215_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/converter/unwrapper.hpp>

namespace boost { namespace python { namespace converter { 

struct class_unwrapper_base
{
    class_unwrapper_base(type_id_t sought_type);
    void*
};

template <class T>
struct class_unwrapper
{
    struct ref_unwrapper : unwrapper<T&>
    {
        bool convertible(PyObject* p) const
        {
            return p->ob_type == &SimpleType;
        }
    
        simple const& convert(PyObject* p, void*&) const
        {
            return static_cast<SimpleObject*>(p)->x;
        }
        
    };
    
# ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    struct const_ref_unwrapper : unwrapper<T const&>
    {
        bool convertible(PyObject* p) const
        {
            return p->ob_type == &SimpleType;
        }
    
        simple const& convert(PyObject* p, void*&) const
        {
            return static_cast<SimpleObject*>(p)->x;
        }
        
    };
# endif 
};

}}} // namespace boost::python::converter

#endif // CLASS_DWA20011215_HPP
