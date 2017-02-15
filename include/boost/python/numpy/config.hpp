//  (C) Copyright Samuli-Petrus Korhonen 2017.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  The author gratefully acknowleges the support of NMR Solutions, Inc., in
//  producing this work.

//  Revision History:
//  15 Feb 17  Initial version

#ifndef CONFIG_NUMPY20170215_H_
# define CONFIG_NUMPY20170215_H_

# include <boost/config.hpp>
# include <boost/detail/workaround.hpp>

# ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
   // A gcc bug forces some symbols into the global namespace
#  define BOOST_NUMPY_BEGIN_CONVERSION_NAMESPACE
#  define BOOST_NUMPY_END_CONVERSION_NAMESPACE
#  define BOOST_NUMPY_CONVERSION
#  define BOOST_NUMPY_IMPORT_CONVERSION(x) using ::x
# else
#  define BOOST_NUMPY_BEGIN_CONVERSION_NAMESPACE namespace boost { namespace python { namespace numpy {
#  define BOOST_NUMPY_END_CONVERSION_NAMESPACE }} // namespace boost::python
#  define BOOST_NUMPY_CONVERSION boost::python
#  define BOOST_NUMPY_IMPORT_CONVERSION(x) void never_defined() // so we can follow the macro with a ';'
# endif

# if defined(BOOST_MSVC)

#  pragma warning (disable : 4786) // disable truncated debug symbols
#  pragma warning (disable : 4251) // disable exported dll function
#  pragma warning (disable : 4800) //'int' : forcing value to bool 'true' or 'false'
#  pragma warning (disable : 4275) // non dll-interface class

# elif defined(__ICL) && __ICL < 600 // Intel C++ 5

#  pragma warning(disable: 985) // identifier was truncated in debug information

# endif

// The STLport puts all of the standard 'C' library names in std (as far as the
// user is concerned), but without it you need a fix if you're using MSVC or
// Intel C++
# if defined(BOOST_NO_STDC_NAMESPACE)
#  define BOOST_CSTD_
# else
#  define BOOST_CSTD_ std
# endif

/*****************************************************************************
 *
 *  Set up dll import/export options:
 *
 ****************************************************************************/

// backwards compatibility:
#ifdef BOOST_NUMPY_STATIC_LIB
#  define BOOST_NUMPY_STATIC_LINK
# elif !defined(BOOST_NUMPY_DYNAMIC_LIB)
#  define BOOST_NUMPY_DYNAMIC_LIB
#endif

#if defined(BOOST_NUMPY_DYNAMIC_LIB)
#  if defined(BOOST_SYMBOL_EXPORT)
#     if defined(BOOST_NUMPY_SOURCE)
#        define BOOST_NUMPY_DECL           BOOST_SYMBOL_EXPORT
#        define BOOST_NUMPY_DECL_FORWARD   BOOST_SYMBOL_FORWARD_EXPORT
#        define BOOST_NUMPY_DECL_EXCEPTION BOOST_EXCEPTION_EXPORT
#        define BOOST_NUMPY_BUILD_DLL
#     else
#        define BOOST_NUMPY_DECL           BOOST_SYMBOL_IMPORT
#        define BOOST_NUMPY_DECL_FORWARD   BOOST_SYMBOL_FORWARD_IMPORT
#        define BOOST_NUMPY_DECL_EXCEPTION BOOST_EXCEPTION_IMPORT
#     endif
#  endif

#endif

#ifndef BOOST_NUMPY_DECL
#  define BOOST_NUMPY_DECL
#endif

#ifndef BOOST_NUMPY_DECL_FORWARD
#  define BOOST_NUMPY_DECL_FORWARD
#endif

#ifndef BOOST_NUMPY_DECL_EXCEPTION
#  define BOOST_NUMPY_DECL_EXCEPTION
#endif

#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
// Replace broken Tru64/cxx offsetof macro
# define BOOST_NUMPY_OFFSETOF(s_name, s_member) \
        ((size_t)__INTADDR__(&(((s_name *)0)->s_member)))
#else
# define BOOST_NUMPY_OFFSETOF offsetof
#endif

//  enable automatic library variant selection  ------------------------------// 

#if !defined(BOOST_NUMPY_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_NUMPY_NO_LIB)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_python
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#ifdef BOOST_NUMPY_DYNAMIC_LIB
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#ifndef BOOST_NUMPY_NO_PY_SIGNATURES
#define BOOST_NUMPY_SUPPORTS_PY_SIGNATURES // enables smooth transition
#endif

#if !defined(BOOST_ATTRIBUTE_UNUSED) && defined(__GNUC__) && (__GNUC__ >= 4)
#  define BOOST_ATTRIBUTE_UNUSED __attribute__((unused))
#endif

#endif // CONFIG_NUMPY20170215_H_
