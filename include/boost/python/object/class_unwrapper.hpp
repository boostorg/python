// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_UNWRAPPER_DWA20011221_HPP
# define CLASS_UNWRAPPER_DWA20011221_HPP

# include <boost/python/object/class.hpp>
# include <boost/python/converter/unwrapper.hpp>

namespace boost { namespace python { namespace objects { 

template <class T>
struct class_unwrapper
{
 private:
    template <class Target>
    struct reference_unwrapper : converter::unwrapper<Target>
    {
        void* can_convert(PyObject* p) const
        {
            return find_instance<T>(p);
        }
        
        Target convert(PyObject* p, void* data, ) const
        {
            return *find_instance<T>(p)->target();
        }
    };
    
    reference_unwrapper<T&> m_reference;
# ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    reference_unwrapper<T const&> m_const_reference;
# endif 
};

}}} // namespace boost::python::objects

#endif // CLASS_UNWRAPPER_DWA20011221_HPP
