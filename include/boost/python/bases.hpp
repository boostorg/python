// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BASES_DWA2002321_HPP
# define BASES_DWA2002321_HPP
# include <boost/type_traits/object_traits.hpp>
# include <boost/mpl/type_list.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/mpl/identity/identity.hpp>

namespace boost { namespace python { 
  // A type list for specifying bases
  template < BOOST_MPL_LIST_DEFAULT_PARAMETERS(typename B, ::boost::mpl::null_argument) >
  struct bases : ::boost::mpl::type_list< BOOST_MPL_LIST_PARAMETERS(B) >::type
  {};

  namespace detail
  {
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class T> struct specifies_bases
    {
        BOOST_STATIC_CONSTANT(bool, value = false);
    };
    template < BOOST_MPL_LIST_PARAMETERS(class B) >
    struct specifies_bases< bases< BOOST_MPL_LIST_PARAMETERS(B) > >
    {
        BOOST_STATIC_CONSTANT(bool, value = true);
    };
# else
    template < BOOST_MPL_LIST_PARAMETERS(class B) >
    static char is_bases_helper(bases< BOOST_MPL_LIST_PARAMETERS(B) > const&);
    
    static char (& is_bases_helper(...) )[256];

    template <class T> struct specifies_bases
    {
     private:
        static typename add_reference<T>::type make();
        BOOST_STATIC_CONSTANT(bool, non_ref = !is_reference<T>::value);
     public:
        BOOST_STATIC_CONSTANT(bool, value = non_ref & (sizeof(is_bases_helper(make())) == 1));
    };
# endif
    template <class T, class Prev = bases<> >
    struct select_bases
        : mpl::select_type<
                specifies_bases<T>::value
                , T
                , Prev
          >
    {
    };
  }
}} // namespace boost::python

#endif // BASES_DWA2002321_HPP
