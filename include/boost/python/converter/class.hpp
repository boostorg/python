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

template <class T>
struct class_unwrapper
    : private unwrapper<T&>
    , private unwrapper<T const&>
    , private unwrapper<T*>
    , private unwrapper<T const*>
{
 private:
    void* can_convert(PyObject*) const;
    T& convert(PyObject*, void*, boost::type<T&>) const;
    T const& convert(PyObject*, void*, boost::type<T const&>) const;
    T* convert(PyObject*, void*, boost::type<T*>) const;
    T const* convert(PyObject*, void*, boost::type<T const*>) const;
};

//
// implementations
//
template <class T>
void* class_unwrapper<T>::can_convert(PyObject* p) const
{
    return objects::find_holder<T>(p);
}

template <class T>
T& class_unwrapper<T>::convert(PyObject*, void* holder_, boost::type<T&>) const
{
    return *static_cast<objects::holder<T>*>(holder_)->target();
}

template <class T>
T const& class_unwrapper<T>::convert(PyObject*, void* holder_, boost::type<T const&>) const
{
    return *static_cast<objects::holder<T>*>(holder_)->target();
}

template <class T>
T* class_unwrapper<T>::convert(PyObject*, void* holder_, boost::type<T*>) const
{
    return static_cast<objects::holder<T>*>(holder_)->target();
}

template <class T>
T const* class_unwrapper<T>::convert(PyObject*, void* holder_, boost::type<T const*>) const
{
    return static_cast<objects::holder<T>*>(holder_)->target();
}

}}} // namespace boost::python::converter

#endif // CLASS_DWA20011215_HPP
