//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef CONFIG_DWA052200_H_
# define CONFIG_DWA052200_H_

# include <boost/config.hpp>
# include <cstddef>

# ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
   // A gcc bug forces some symbols into the global namespace
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE
#  define BOOST_PYTHON_CONVERSION
#  define BOOST_PYTHON_IMPORT_CONVERSION(x) using ::x
# else
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE namespace boost { namespace python {
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE }} // namespace boost::python
#  define BOOST_PYTHON_CONVERSION python
#  define BOOST_PYTHON_IMPORT_CONVERSION(x) void never_defined() // so we can follow the macro with a ';'
# endif

# if defined(BOOST_MSVC)
#  if _MSC_VER <= 1200
#   define BOOST_MSVC6_OR_EARLIER 1
#  endif

# pragma warning (disable : 4786)

# endif

// Work around the broken library implementation/strict ansi checking on some
// EDG-based compilers (e.g. alpha), which incorrectly warn that the result of
// offsetof() is not an integer constant expression.
# if defined(__DECCXX_VER) && __DECCXX_VER <= 60290024
#  define BOOST_OFFSETOF(s_name, s_member) \
        ((size_t)__INTADDR__(&(((s_name *)0)->s_member)))
# else
#  define BOOST_OFFSETOF(s_name, s_member) \
        offsetof(s_name, s_member)
# endif

// The STLport puts all of the standard 'C' library names in std (as far as the
// user is concerned), but without it you need a fix if you're using MSVC.
# if defined(BOOST_MSVC6_OR_EARLIER) && !defined(__STLPORT)
#  define BOOST_CSTD_
# else
#  define BOOST_CSTD_ std
# endif

#endif // CONFIG_DWA052200_H_
