// Copyright David Abrahams 2003. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/mpl/bool_c.hpp>
#ifndef BOOST_NO_AUTO_PTR
# include <memory>
#endif 

#ifndef COPY_CTOR_MUTATES_RHS_DWA2003219_HPP
# define COPY_CTOR_MUTATES_RHS_DWA2003219_HPP

namespace boost { namespace python { namespace detail { 

# if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_AUTO_PTR)

template <class T>
struct is_auto_ptr
{
    typedef char yes;
    typedef char (&no)[2];

    static
    T& f();

    template <class U>
    static yes test(std::auto_ptr<U>&, int);

    template <class U>
    static no test(U&, ...);
    
    BOOST_STATIC_CONSTANT(
        bool, value = sizeof(test(f(), 0)) == sizeof(yes));

    typedef mpl::bool_c<value> type;
                              
};

# else

template <class T>
struct is_auto_ptr : mpl::false_c
{
};

#  if !defined(BOOST_NO_AUTO_PTR)
template <class T>
struct is_auto_ptr<std::auto_ptr<T> > : mpl::true_c
{
};

#  endif
# endif

template <class T>
struct copy_ctor_mutates_rhs
    : is_auto_ptr<T>
{
};

}}} // namespace boost::python::detail

#endif // COPY_CTOR_MUTATES_RHS_DWA2003219_HPP
