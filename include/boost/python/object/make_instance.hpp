// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MAKE_INSTANCE_DWA200296_HPP
# define MAKE_INSTANCE_DWA200296_HPP

# include <boost/python/object/instance.hpp>
# include <boost/python/converter/registered.hpp>

namespace boost { namespace python { namespace objects { 

template <class T, class Holder>
struct make_instance
{
    typedef objects::instance<Holder> instance_t;
        
    template <class Arg>
    static PyObject* execute(Arg& x)
    {
        BOOST_STATIC_ASSERT(is_class<T>::value);
        PyTypeObject* type = converter::registered<T>::converters.class_object;

        PyObject* raw_result = type->tp_alloc(
            type, objects::additional_instance_size<Holder>::value);
          
        if (raw_result != 0)
        {
            instance_t* result = (instance_t*)raw_result;
            try
            {
                // construct the new C++ object and install the pointer
                // in the Python object.
                construct(result, x)->install(raw_result);
            }
            catch(...)
            {
                Py_DECREF(raw_result); // reclaim the Python object
                throw;
            }
              
            // Note the position of the internally-stored Holder,
            // for the sake of destruction
            result->ob_size = offsetof(instance_t, storage);
        }
        return raw_result;
    }
    
 private:
    // Kind of a hack to support code re-use. The first form is used
    // to construct holders around pointers or smart pointers. The
    // second form is used to construct holders around by-value
    // returns. We have to pass a pointer to the owning Python object
    // to the second form in order to make it forward the 2nd argument
    // on to the constructor of its embedded T object.
    template <class Arg>
    static Holder* construct(instance_t* result, Arg& x)
    {
        return new ((void*)&result->storage) Holder(x);
    }

    static Holder* construct(instance_t* result, reference_wrapper<T const> x)
    {
        return new ((void*)&result->storage) Holder((PyObject*)result, x);
    }
};
  

}}} // namespace boost::python::object

#endif // MAKE_INSTANCE_DWA200296_HPP
