// Example by Ralf W. Grosse-Kunstleve
/*

   This example shows how to convert a class from and to native
   Python objects, such as tuples.

   We do not want to expose the helper class MillerIndex as an
   Extension Class. However, in order to simplify the wrapper code,
   we want to define from_python() and to_python() functions for
   class MillerIndex.

   Consider the alternatives:

     - Expose MillerIndex as an Extension Class.
         We need a constructor MillerIndex(python::tuple).
         Python function calls become more complex:
           foo(MillerIndex((1,2,3)) instead of foo((1,2,3))
         We need a method such as MillerIndex().as_tuple().

     - Define a wrapper function for each function that we
       want to expose, e.g.:
          void add(const IndexingSet& ixset, const python::tuple PyMIx)

   The first alternative introduces a new type that the user has to
   deal with. Other modules using Miller indices might organize them in
   different ways, for example to increase runtime efficiency for
   important procedures. This means, the user has to know how to
   convert between the different kinds of Miller index representations.
   This can quickly become a nuisance. Relying on native Python data
   structures minimizes the number of special types the user has to
   learn and convert. Of course, this argument is only valid for
   small and relatively simply classes.

   If there are many member functions with MillerIndex arguments, the
   second alternative is impractical, and concentrating the conversion
   mechanism in one central place is essential for code
   maintainability.  An added benefit is that more convenient (smarter)
   conversion functions can be provided without cluttering the rest of
   the wrapper code.

 */

#include <string>
#include <vector>
#include <boost/python/class_builder.hpp>
namespace python = boost::python;

namespace { // Avoid cluttering the global namespace.

  // The helper class.
  //
  class MillerIndex {
    public:
      int v[3];
  };

  // The main class. Imagine that there are MANY member functions
  // like add() and get().
  //
  class IndexingSet {
    private:
      std::vector<MillerIndex> VMIx;
    public:
      void add(const MillerIndex& MIx) { VMIx.push_back(MIx); }
      MillerIndex get(std::size_t i) const { return VMIx[i]; }
  };
}

BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE

  // Convert a Python tuple to a MillerIndex object.
  //
  MillerIndex from_python(PyObject* p, python::type<const MillerIndex&>)
  {
    python::tuple tup
      = python::tuple(python::ref(p, python::ref::increment_count));
    if (tup.size() != 3) {
      PyErr_SetString(PyExc_ValueError,
        "expecting exactly 3 values in tuple.");
      throw python::error_already_set();
    }
    MillerIndex result;
    for (int i = 0; i < 3; i++)
      result.v[i] = from_python(tup[i].get(), python::type<int>());
    return result;
  }

  // Similar conversion for MillerIndex objects passed by value.
  // Not actually used, but included to show the principle.
  //
  MillerIndex from_python(PyObject* p, python::type<MillerIndex>)
  {
    return from_python(p, python::type<const MillerIndex&>());
  }

  // Convert a MillerIndex object to a Python tuple.
  //
  PyObject* to_python(const MillerIndex& hkl)
  {
    python::tuple result(3);
    for (int i = 0; i < 3; i++)
      result.set_item(i, python::ref(to_python(hkl.v[i])));
    return result.reference().release();
  }

BOOST_PYTHON_END_CONVERSION_NAMESPACE

BOOST_PYTHON_MODULE_INIT(do_it_yourself_convts)
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("do_it_yourself_convts");

    // Create the Python type object for our extension class.
    python::class_builder<IndexingSet> ixset_class(this_module, "IndexingSet");

    // Add the __init__ function.
    ixset_class.def(python::constructor<>());
    // Add the member functions.
    ixset_class.def(&IndexingSet::add, "add");
    ixset_class.def(&IndexingSet::get, "get");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
