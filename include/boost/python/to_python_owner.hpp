// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_OWNER_DWA200221_HPP
# define TO_PYTHON_OWNER_DWA200221_HPP

# include <boost/type_traits/object_traits.hpp>
# include <boost/python/object/pointer_holder.hpp>
# include <boost/python/object/class_object.hpp>
# include <boost/python/detail/unwind_type.hpp>
# include <memory>

namespace boost { namespace python {

template <class T>
struct to_python_owner
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
      typedef objects::instance_holder* result_type;
      template <class T>
      static result_type execute(T* p)
      {
          return new objects::pointer_holder<std::auto_ptr<T>, T>(
              std::auto_ptr<T>(p));
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
}

template <class T>
inline bool to_python_owner<T>::convertible()
{
    BOOST_STATIC_ASSERT(is_pointer<T>::value);
    return type() != 0;
}

template <class T>
inline PyObject* to_python_owner<T>::operator()(T x) const
{
    PyObject* raw_result = type()->tp_alloc(type(), 0);

    if (raw_result == 0)
        return 0;

    // Everything's OK; Bypass NULL checks but guard against
    // exceptions.
    ref result(raw_result, ref::allow_null());

    // Build a value_holder to contain the object using the copy
    // constructor
    objects::instance_holder* p =
        detail::unwind_type<detail::make_owning_holder>(x);

    // Install it in the instance
    p->install(raw_result);

    // Return the new result
    return result.release();
}

template <class T>
inline PyTypeObject* to_python_owner<T>::type()
{
    return detail::unwind_type<detail::get_pointer_class>(T(0));
}

}} // namespace boost::python

#endif // TO_PYTHON_OWNER_DWA200221_HPP
