// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef LONG_DWA2002627_HPP
# define LONG_DWA2002627_HPP

# include <boost/python/object.hpp>
# include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python { 

class long_ : public object
{
 public:
    BOOST_PYTHON_DECL long_(); // new long_
    explicit BOOST_PYTHON_DECL long_(object_cref rhs);

    template <class T>
    explicit long_(T const& rhs)
        : object(long_::call(object(rhs)))
    {
    }

    explicit BOOST_PYTHON_DECL long_(object_cref rhs, object_cref base);

    template <class T, class U>
    explicit long_(T const& rhs, U const& base)
        : object(long_::call(object(rhs), object(base)))
    {
    }
 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(long_)
    
 private:
    static BOOST_PYTHON_DECL detail::new_non_null_reference call(object const&);
    static BOOST_PYTHON_DECL detail::new_non_null_reference call(object const&, object const&);
};

//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<long_>
      : pytype_object_manager_traits<&PyLong_Type,long_>
  {
  };
}

}} // namespace boost::python

#endif // LONG_DWA2002627_HPP
