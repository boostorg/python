// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_INDIRECT_DWA200221_HPP
# define TO_PYTHON_INDIRECT_DWA200221_HPP

# include <boost/type_traits/object_traits.hpp>
# include <boost/python/object/pointer_holder.hpp>
# include <boost/python/object/class_object.hpp>
# include <boost/python/detail/unwind_type.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/shared_ptr.hpp>
# include <memory>

namespace boost { namespace python {

template <class T, class MakeHolder>
struct to_python_indirect
{
    static bool convertible();
    PyObject* operator()(T ptr) const;
 private:
    static PyTypeObject* type();
};

//
// implementations
//
namespace detail
{
  struct make_owning_holder
  {
      typedef instance_holder* result_type;
      template <class T>
      static result_type execute(T* p)
      {
          // can't use auto_ptr with Intel 5 for some reason
# if defined(__ICL) && __ICL < 600 
          typedef boost::shared_ptr<T> smart_pointer;
# else 
          typedef std::auto_ptr<T> smart_pointer;
# endif 
          
          return new objects::pointer_holder<smart_pointer, T>(
              smart_pointer(p));
      }
  };

  struct make_reference_holder
  {
      typedef instance_holder* result_type;
      template <class T>
      static result_type execute(T* p)
      {
          return new objects::pointer_holder<T*, T>(p);
      }
  };

  struct get_pointer_class
  {
      typedef PyTypeObject* result_type;
      template <class T>
      static result_type execute(T* p)
      {
          BOOST_STATIC_ASSERT(is_class<T>::value);
          return python::objects::class_object<T>::reference;
      }
  };

  // null_pointer_to_none -- return none() for null pointers and 0 for all other types/values
  // 
  // Uses simulated partial ordering
  template <class T>
  inline PyObject* null_pointer_to_none(T&, int)
  {
      return 0;
  }

  // overload for pointers
  template <class T>
  inline PyObject* null_pointer_to_none(T* x, long)
  {
      return x == 0 ? python::detail::none() : 0;
  }
}

template <class T, class MakeHolder>
inline bool to_python_indirect<T,MakeHolder>::convertible()
{
    BOOST_STATIC_ASSERT(is_pointer<T>::value || is_reference<T>::value);
    return type() != 0;
}

template <class T, class MakeHolder>
inline PyObject* to_python_indirect<T,MakeHolder>::operator()(T x) const
{
    PyObject* const null_result = detail::null_pointer_to_none(x, 1L);
    if (null_result != 0)
        return null_result;
    
    PyObject* raw_result = type()->tp_alloc(type(), 0);

    if (raw_result == 0)
        return 0;

    // Everything's OK; Bypass NULL checks but guard against
    // exceptions.
    ref result(raw_result, ref::allow_null());

    // Build a value_holder to contain the object using the copy
    // constructor
    instance_holder* p =
        detail::unwind_type<MakeHolder>(x);

    // Install it in the instance
    p->install(raw_result);

    // Return the new result
    return result.release();
}

template <class T, class MakeHolder>
inline PyTypeObject* to_python_indirect<T,MakeHolder>::type()
{
    return detail::unwind_type<detail::get_pointer_class,T>();
}

}} // namespace boost::python

#endif // TO_PYTHON_INDIRECT_DWA200221_HPP
