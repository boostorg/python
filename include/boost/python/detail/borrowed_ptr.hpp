#ifndef BORROWED_PTR_DWA20020601_HPP
# define BORROWED_PTR_DWA20020601_HPP
// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

# include <boost/config.hpp>
#include <boost/type.hpp>

namespace boost { namespace python { namespace detail {

template<class T> class borrowed
{ 
    typedef T type;
};

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template<typename T>
struct is_borrowed_ptr
{
    BOOST_STATIC_CONSTANT(bool, value = false); 
};

template<typename T>
struct is_borrowed_ptr<borrowed<T>*>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

# else // no partial specialization

typedef char (&yes_borrowed_ptr_t)[1];
typedef char (&no_borrowed_ptr_t)[2];
      
no_borrowed_ptr_t is_borrowed_ptr_test(...);

template<typename T>
yes_borrowed_ptr_t is_borrowed_ptr_test(boost::type< borrowed<T>* >);

template<typename T>
class is_borrowed_ptr
{
 public:
    BOOST_STATIC_CONSTANT(
        bool, value = (
            sizeof(detail::is_borrowed_ptr_test(boost::type<T>()))
            == sizeof(detail::yes_borrowed_ptr_t)));
};

# endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}} // namespace boost::python::detail

#endif // #ifndef BORROWED_PTR_DWA20020601_HPP
