#ifndef TUPLE_20020706_HPP
#define TUPLE_20020706_HPP

#include <boost/python/object.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python {

class BOOST_PYTHON_DECL tuple : public object
{
 public:
    // tuple() -> an empty tuple
    tuple();

    // tuple(sequence) -> tuple initialized from sequence's items
    tuple(object_cref sequence);

    template <class T>
    explicit tuple(T const& sequence)
        : object(tuple::call(object(sequence)))
    {
    }

 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(tuple)

 private:
    static detail::new_reference call(object const&);
};

//
// Converter Specializations    // $$$ JDG $$$ moved here to prevent
//                              // G++ bug complaining specialization
                                // provided after instantiation
namespace converter
{
  template <>
  struct object_manager_traits<tuple>
      : pytype_object_manager_traits<&PyTuple_Type,tuple>
  {
  };
}

// for completeness
inline tuple make_tuple() { return tuple(); }

# define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PYTHON_MAX_ARITY, <boost/python/detail/make_tuple.hpp>))
# include BOOST_PP_ITERATE()

}}  // namespace boost::python

#endif

