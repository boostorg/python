//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include "init_function.h"
#include "objects.h"
#include "extclass.h"
#include <utility>

namespace py { namespace detail {

  PyObject* Init::do_call(PyObject* args_, PyObject* keywords) const
  {
      Tuple args(Ptr(args_, Ptr::borrowed));
      if (args[0]->ob_type->ob_type != extension_meta_class())
      {
          PyErr_SetString(PyExc_TypeError, "argument 1 to __init__ must be an ExtensionInstance");
          return 0;
      }

      ExtensionInstance *self = static_cast<ExtensionInstance*>(args[0].get());

      Tuple ctor_args = args.slice(1, args.size());

      std::auto_ptr<InstanceHolderBase> result(
          create_holder(self, ctor_args.get(), keywords));

      self->add_implementation(result);
      return none();
  }

}} // namespace py::detail
