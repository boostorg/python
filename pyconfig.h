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
#  define PY_NO_INLINE_FRIENDS_IN_NAMESPACE 1 // A more accurate name
#  define PY_INLINE_FRIEND
# else
#  define PY_INLINE_FRIEND ::py
# endif

# if defined(BOOST_MSVC)
#  define PY_COMPILER_IS_MSVC 1
#  if _MSC_VER <= 1200
#   define PY_MSVC6_OR_EARLIER 1
#  endif

# pragma warning (disable : 4786)

# endif

// Work around the broken library implementation/strict ansi checking on some
// EDG-based compilers (e.g. alpha), which incorrectly warn that the result of
// offsetof() is not an integer constant expression.
# if defined(__DECCXX_VER) && __DECCXX_VER <= 60290024
#  define PY_OFFSETOF(s_name, s_member) \
        ((size_t)__INTADDR__(&(((s_name *)0)->s_member)))
# else
#  define PY_OFFSETOF(s_name, s_member) \
        offsetof(s_name, s_member)
# endif

// The STLport puts all of the standard 'C' library names in std (as far as the
// user is concerned), but without it you need a fix if you're using MSVC.
# if defined(PY_MSVC6_OR_EARLIER) && !defined(__STLPORT)
#  define PY_CSTD_
# else
#  define PY_CSTD_ std
# endif

#endif // CONFIG_DWA052200_H_
