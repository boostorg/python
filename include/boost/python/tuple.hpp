#ifndef TUPLE_20020706_HPP
#define TUPLE_20020706_HPP

#include <boost/python/object.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python {

class tuple : public object
{
 public:
    // tuple() -> an empty tuple
    BOOST_PYTHON_DECL tuple();
    
    // tuple(sequence) -> tuple initialized from sequence's items
    BOOST_PYTHON_DECL tuple(object_cref sequence);

    template <class T>
    explicit tuple(T const& sequence)
        : object(tuple::call(object(sequence)))
    {
    }

 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(tuple)
    
 private:
    static BOOST_PYTHON_DECL detail::new_reference call(object const&);
};


//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<tuple>
      : pytype_object_manager_traits<&PyTuple_Type,tuple>
  {
  };
}

}}  // namespace boost::python

#endif

