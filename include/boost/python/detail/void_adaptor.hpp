//  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#ifndef VOID_ADAPTOR_DWA20011112_HPP
# define VOID_ADAPTOR_DWA20011112_HPP

namespace boost { namespace python { namespace detail {

  extern BOOST_PYTHON_DECL PyObject arbitrary_object;

  template <class T>
  struct void_adaptor
  {
      typedef PyObject* result_type;
      
      void_adaptor(T const& f)
          : m_f(f)
      {}
          
      PyObject* operator()() const
      {
          m_f();
          return &arbitrary_object;
      }
   private:
      T m_f;
  };

  template <class T>
  void_adaptor<T> make_void_adaptor(T const& f)
  {
      return void_adaptor<T>(f);
  }
}}} // namespace boost::python::detail

#endif // VOID_ADAPTOR_DWA20011112_HPP

