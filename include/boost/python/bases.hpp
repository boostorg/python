// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BASES_DWA2002321_HPP
# define BASES_DWA2002321_HPP
# include <boost/type_traits/object_traits.hpp>
# include <boost/mpl/list.hpp>
# include <boost/mpl/select_if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/preprocessor/enum_params_with_a_default.hpp>
# include <boost/preprocessor/enum_params.hpp>

namespace boost { namespace python { 
  // A type list for specifying bases
  template < BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_LIMIT_LIST_SIZE, typename B, ::boost::mpl::aux::none) >
  struct bases : ::boost::mpl::list< BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_LIST_SIZE,B) >
  {};

  namespace detail
  {
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class T> struct specifies_bases
    {
        BOOST_STATIC_CONSTANT(bool, value = false);
    };
    template < BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_LIST_SIZE,class B) >
    struct specifies_bases< bases< BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_LIST_SIZE,B) > >
    {
        BOOST_STATIC_CONSTANT(bool, value = true);
    };
# else
    template < BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_LIST_SIZE,class B) >
    static char is_bases_helper(bases< BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_LIST_SIZE,B) > const&);
    
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
        : mpl::select_if_c<
                specifies_bases<T>::value
                , T
                , Prev
          >
    {
    };
  }
}} // namespace boost::python

#endif // BASES_DWA2002321_HPP
