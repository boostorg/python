//  Copyright David Abrahams 2001. Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
#ifndef EXPORT_DWA20011120_HPP
# define EXPORT_DWA20011120_HPP
#  include <boost/config.hpp>
#  include <boost/preprocessor/if.hpp>
#  include <boost/preprocessor/cat.hpp>

# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#  ifndef BOOST_PYTHON_EXPORT
#   define BOOST_PYTHON_EXPORT __declspec(dllimport)
#  endif
# else
#  define BOOST_PYTHON_EXPORT
# endif 

#endif // EXPORT_DWA20011120_HPP
