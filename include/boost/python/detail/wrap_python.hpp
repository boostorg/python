#ifdef _DEBUG
# ifndef DEBUG_PYTHON
#  undef _DEBUG // Don't let Python force the debug library just because we're debugging.
#  define DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# endif
#endif

//
// Some things we need in order to get Python.h to work with compilers other
// than MSVC on Win32
//
#if defined(_WIN32)
# ifdef __GNUC__

typedef int pid_t;
#  define WORD_BIT 32
#  define hypot _hypot
#  include <stdio.h>
#  define HAVE_CLOCK
#  define HAVE_STRFTIME
#  define HAVE_STRERROR
#  define NT_THREADS
#  define WITH_THREAD
#  ifndef NETSCAPE_PI
#   define USE_SOCKET
#  endif

#  ifdef USE_DL_IMPORT
#   define DL_IMPORT(RTYPE) __declspec(dllimport) RTYPE
#  endif

#  ifdef USE_DL_EXPORT
#   define DL_IMPORT(RTYPE) __declspec(dllexport) RTYPE
#   define DL_EXPORT(RTYPE) __declspec(dllexport) RTYPE
#  endif

#  define HAVE_LONG_LONG 1
#  define LONG_LONG long long

# elif defined(__MWERKS__)

#  ifndef _MSC_VER
#   define PY_MSC_VER_DEFINED_FROM_WRAP_PYTHON_H 1
#   define _MSC_VER 900
#  endif

# endif

#endif // _WIN32

#include <Python.h>

#ifdef PY_MSC_VER_DEFINED_FROM_WRAP_PYTHON_H
# undef _MSC_VER
#endif

#ifdef DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# undef DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# define _DEBUG
#endif

