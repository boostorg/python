// -*- mode:c++ -*-
//
// Header file value_traits.hpp
//
// Traits information about container element types for use in
// determining which Python methods to support for a container.
//
// Copyright (c) 2003 Raoul M. Gough
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this material for any purpose is hereby
// granted without fee, provided the above notices are retained on all
// copies.  Permission to modify the material and to distribute modified
// versions is granted, provided the above notices are retained, and a
// notice that the material was modified is included with the above
// copyright notice.
//
// History
// =======
// 2003/ 9/12	rmg	File creation
//
// $Id$
//

#ifndef value_traits_rmg_20030912_included
#define value_traits_rmg_20030912_included

namespace indexing {
  template<typename T>
  struct value_traits {
    static bool const equality_comparable = true;
    // Meaning from C++98 standard section 20.1.1

    // static bool const has_less = true;
    // etc...

    // Default, do-nothing, version of visitor_helper
    template<typename PythonClass, typename Policy>
    static void visitor_helper (PythonClass &, Policy const &) { }
  };
}

#endif // value_traits_rmg_20030912_included
