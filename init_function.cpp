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

namespace python { namespace detail {

  PyObject* init::do_call(PyObject* args_, PyObject* keywords) const
  {
      tuple args(ref(args_, ref::increment_count));
      if (args[0]->ob_type->ob_type != extension_meta_class())
      {
          PyErr_SetString(PyExc_TypeError, "argument 1 to __init__ must be an ExtensionInstance");
          return 0;
      }

      extension_instance *self = static_cast<extension_instance*>(args[0].get());

      tuple ctor_args = args.slice(1, args.size());

      std::auto_ptr<instance_holder_base> result(
          create_holder(self, ctor_args.get(), keywords));

      self->add_implementation(result);
      return none();
  }

    string init::arguments_as_string(tuple arguments) const
    {
        return argument_tuple_as_string(arguments.slice(1, arguments.size()));
    }

}} // namespace python::detail
