// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BASES_DWA2002321_HPP
# define BASES_DWA2002321_HPP
# include <boost/type_traits/object_traits.hpp>
# include <boost/python/detail/type_list.hpp>
# include <boost/mpl/if.hpp>
# include <boost/preprocessor/enum_params_with_a_default.hpp>
# include <boost/preprocessor/enum_params.hpp>

namespace boost { namespace python { 

  // A type list for specifying bases
  template < BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PYTHON_MAX_BASES, typename B, mpl::void_) >
  struct bases : detail::type_list< BOOST_PP_ENUM_PARAMS(BOOST_PYTHON_MAX_BASES, B) >::type
  {};

  namespace detail
  {
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class T> struct specifies_bases
    {
        BOOST_STATIC_CONSTANT(bool, value = false);
    };
    template < BOOST_PP_ENUM_PARAMS(BOOST_PYTHON_MAX_BASES, class B) >
    struct specifies_bases< bases< BOOST_PP_ENUM_PARAMS(BOOST_PYTHON_MAX_BASES, B) > >
    {
        BOOST_STATIC_CONSTANT(bool, value = true);
    };
# else
    template < BOOST_PP_ENUM_PARAMS(BOOST_PYTHON_MAX_BASES, class B) >
    static char is_bases_helper(bases< BOOST_PP_ENUM_PARAMS(BOOST_PYTHON_MAX_BASES, B) > const&);
    
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
        : mpl::if_c<
                specifies_bases<T>::value
                , T
                , Prev
          >
    {
    };
  }
}} // namespace boost::python

#endif // BASES_DWA2002321_HPP
