#error obsolete
/*
 *
 * Copyright (c) 1998-2000
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_libary_include.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Automatic library inclusion for Borland/Microsoft compilers.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */


#ifndef BOOST_REGEX_LIBRARY_INCLUDE_HPP
#define BOOST_REGEX_LIBRARY_INCLUDE_HPP
#ifndef BOOST_REGEX_NO_LIB

#if defined(BOOST_MSVC) && !defined(BOOST_REGEX_BUILD_DLL)
#ifdef __SGI_STL_PORT
   #ifdef _DLL
      // All these are multithreaded:
      #if defined(_DEBUG) && defined(__STL_DEBUG)
         #pragma comment(lib, "vc6-stlport-re300ddl.lib")
      #elif defined(_DEBUG)
         #pragma comment(lib, "vc6-stlport-re300dl.lib")
      #elif defined(BOOST_REGEX_STATIC_LINK)
         // static regex lib, dll runtime
         #pragma comment(lib, "vc6-stlport-re300ls.lib")
      #else // DEBUG
         #pragma comment(lib, "vc6-stlport-re300l.lib")
      #endif // _DEBUG
   #else // _DLL
      #ifdef _MT
         #if defined(_DEBUG) && defined(__STL_DEBUG)
            #pragma comment(lib, "vc6-stlport-re300ddm.lib")
         #elif defined(_DEBUG)
            #pragma comment(lib, "vc6-stlport-re300dm.lib")
         #else //_DEBUG
            #pragma comment(lib, "vc6-stlport-re300m.lib")
         #endif //_DEBUG
      #else //_MT
         // STLPort does not support single threaded builds:
         #error STLPort does not support single threaded builds
      #endif //_MT
   #endif //_DLL
#elif _MSC_VER < 1300
   #ifdef _DLL
      // All these are multithreaded:
      #ifdef _DEBUG
         #pragma comment(lib, "vc6-re300dl.lib")
      #elif defined(BOOST_REGEX_STATIC_LINK)
         // static regex lib, dll runtime
         #pragma comment(lib, "vc6-re300ls.lib")
      #else // DEBUG
         #pragma comment(lib, "vc6-re300l.lib")
      #endif // _DEBUG
   #else // _DLL
      #ifdef _MT
         #ifdef _DEBUG
            #pragma comment(lib, "vc6-re300dm.lib")
         #else //_DEBUG
            #pragma comment(lib, "vc6-re300m.lib")
         #endif //_DEBUG
      #else //_MT
         #ifdef _DEBUG
            #pragma comment(lib, "vc6-re300d.lib")
         #else //_DEBUG
            #pragma comment(lib, "vc6-re300.lib")
         #endif //_DEBUG
      #endif //_MT
   #endif //_DLL
#else
   #ifdef _DLL
      // All these are multithreaded:
      #ifdef _DEBUG
         #pragma comment(lib, "vc7-re300dl.lib")
      #elif defined(BOOST_REGEX_STATIC_LINK)
         // static regex lib, dll runtime
         #pragma comment(lib, "vc7-re300ls.lib")
      #else // DEBUG
         #pragma comment(lib, "vc7-re300l.lib")
      #endif // _DEBUG
   #else // _DLL
      #ifdef _MT
         #ifdef _DEBUG
            #pragma comment(lib, "vc7-re300dm.lib")
         #else //_DEBUG
            #pragma comment(lib, "vc7-re300m.lib")
         #endif //_DEBUG
      #else //_MT
         #ifdef _DEBUG
            #pragma comment(lib, "vc7-re300d.lib")
         #else //_DEBUG
            #pragma comment(lib, "vc7-re300.lib")
         #endif //_DEBUG
      #endif //_MT
   #endif //_DLL
#endif // __SGI_STL_PORT
#endif //BOOST_MSVC


#if defined(__BORLANDC__) && !defined(BOOST_REGEX_BUILD_DLL)
   
   #if __BORLANDC__ < 0x550
   
   #ifdef BOOST_REGEX_USE_VCL
   
      #ifdef _RTLDLL
         #pragma comment(lib, "bcb4re300lv.lib")
      #else
         #pragma comment(lib, "bcb4re300v.lib")
      #endif
   
   #else // VCL
   
   #ifdef _RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb4re300lm.lib")
      #else // __MT__
         #pragma comment(lib, "bcb4re300l.lib")
      #endif // __MT__
   #else //_RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb4re300m.lib")
      #else // __MT__
         #pragma comment(lib, "bcb4re300.lib")
      #endif // __MT__
   #endif // _RTLDLL
   
   #endif // VCL
   
   #else // C++ Builder 5:

   #ifdef BOOST_REGEX_USE_VCL
   
      #ifdef _RTLDLL
         #pragma comment(lib, "bcb5re300lv.lib")
      #else
         #pragma comment(lib, "bcb5re300v.lib")
      #endif
   
   #else // VCL
   
   #ifdef _RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb5re300lm.lib")
      #else // __MT__
         #pragma comment(lib, "bcb5re300l.lib")
      #endif // __MT__
   #else //_RTLDLL
      #ifdef __MT__
         #pragma comment(lib, "bcb5re300m.lib")
      #else // __MT__
         #pragma comment(lib, "bcb5re300.lib")
      #endif // __MT__
   #endif // _RTLDLL
   
   #endif // VCL
   
   #endif   
   
#endif //__BORLANDC__

#endif //BOOST_REGEX_NO_LIB

#endif // BOOST_REGEX_LIBRARY_INCLUDE_HPP




