//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

//  Revision History:
//  04 Mar 01  Some fixes so it will compile with Intel C++ (Dave Abrahams)

#ifndef CONFIG_DWA052200_H_
# define CONFIG_DWA052200_H_

# include <boost/config.hpp>
# include <cstddef>

# if defined(BOOST_MSVC)
#  if _MSC_VER <= 1200
#   define BOOST_MSVC6_OR_EARLIER 1
#  endif

# pragma warning (disable : 4786)

# endif

# if defined(BOOST_PYTHON_USE_FRIEND_KOENIG_LOOKUP)
// for compilers that support Koenig lookup
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE namespace boost { namespace python {
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE }} // namespace boost::python
# else
// for compilers that do not support Koenig lookup for friend functions
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE
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
// user is concerned), but without it you need a fix if you're using MSVC or
// Intel C++
# if defined(BOOST_MSVC_STD_ITERATOR)
#  define BOOST_CSTD_
# else
#  define BOOST_CSTD_ std
# endif

#ifdef _WIN32
# define BOOST_PYTHON_MODULE_INIT(name) extern "C" __declspec(dllexport) void init##name()
#else
# define BOOST_PYTHON_MODULE_INIT(name) extern "C" void init##name()
#endif

#endif // CONFIG_DWA052200_H_
