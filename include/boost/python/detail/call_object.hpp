// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALL_OBJECT_DWA20011222_HPP
# define CALL_OBJECT_DWA20011222_HPP
# include <boost/python/errors.hpp>
# include <boost/python/detail/types.hpp>
# include <boost/bind.hpp>

namespace boost { namespace python {

namespace detail
{
  // A function object adaptor which turns a function returning R into
  // an "equivalent" function returning void, but taking an R& in
  // which the adapted function's result is stored.
  template <class R, class F>
  struct return_by_reference
  {
      typedef void return_type;
      
      return_by_reference(R& result, F f)
          : m_result(result)
          , m_f(f)
      {
      }
      
      void operator()() const
      {
          m_result = m_f();
      }
      
      R& m_result;
      F m_f;
  };

  // An object generator for the above adaptors
  template <class R, class F>
  return_by_reference<R,F> bind_return(R& result, F f)
  {
      return return_by_reference<R,F>(result, f);
  }

  // Given a function object f with signature
  //
  //    R f(PyTypeObject*,PyObject*)
  //
  // calls f inside of handle_exception_impl, placing f's result in
  // ret. Returns true iff an exception is thrown by f, leaving ret
  // unmodified.
  template <class R, class F>
  bool call_object(R& ret, PyObject* obj, F f)
  {
      return handle_exception(
          detail::bind_return(
              ret
              , boost::bind<R>(
                  f, static_cast<type_object_base*>(obj->ob_type), obj)));
  }
} // namespace detail

}} // namespace boost::python

#endif // CALL_OBJECT_DWA20011222_HPP
