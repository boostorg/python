// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef EXPORT_DWA20011220_HPP
# define EXPORT_DWA20011220_HPP

# include <boost/python/detail/config.hpp>
# ifdef _WIN32
#  ifdef BOOST_PYTHON_SOURCE
#   define BOOST_PYTHON_EXPORT __declspec(dllexport)
#  else 
#   define BOOST_PYTHON_EXPORT __declspec(dllimport)
#  endif
# else
#  define BOOST_PYTHON_EXPORT
# endif 

#endif // EXPORT_DWA20011220_HPP
