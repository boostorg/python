#ifndef BOOST_PYTHON_OBJECT_PYTHON_TYPE_H
#define BOOST_PYTHON_OBJECT_PYTHON_TYPE_H

#include <boost/python/converter/registered.hpp>

namespace boost {namespace python {namespace converter{ 
namespace detail{
    inline void * identity (PyObject *p){return p;}
    namespace strip_type_info{
        BOOST_PYTHON_DECL void insert(boost::python::type_info, boost::python::type_info);
        BOOST_PYTHON_DECL type_info query(boost::python::type_info);
    }
        
}// namespace converter::detail


template <class T> struct python_class : PyObject
{
    typedef python_class<T> this_type;
    typedef T type;
    static void register_()
    {
        static bool first_time = true;

        if ( !first_time ) return;
        first_time = false;
        converter::registry::insert(&detail::identity, boost::python::type_id<this_type>());
        converter::detail::strip_type_info::insert(boost::python::type_id<type>(), boost::python::type_id<type*>());
        converter::detail::strip_type_info::insert(boost::python::type_id<type>(), boost::python::type_id<type const *>());
        converter::detail::strip_type_info::insert(boost::python::type_id<type>(), boost::python::type_id<this_type*>());
    }
private:
    python_class();
};

        
}}} //namespace boost :: python :: converter

#endif //BOOST_PYTHON_OBJECT_PYTHON_TYPE_H
