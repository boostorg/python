// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA200216_HPP
# define CLASS_DWA200216_HPP

# include <boost/python/class_fwd.hpp>
# include <boost/python/reference.hpp>
# include <boost/python/object/class.hpp>
# include <boost/python/object/value_holder_fwd.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/detail/wrap_function.hpp>
# include <boost/python/detail/member_function_cast.hpp>
# include <boost/mpl/type_list.hpp>
# include <boost/python/object/class_converters.hpp>
# include <boost/mpl/size.hpp>
# include <boost/mpl/for_each.hpp>
# include <boost/python/detail/type_list.hpp>

namespace // put some convenience classes into the unnamed namespace for the user
{
  // A type list for specifying bases
  template < BOOST_MPL_LIST_DEFAULT_PARAMETERS(typename B, ::boost::mpl::null_argument) >
  struct bases : ::boost::mpl::type_list< BOOST_MPL_LIST_PARAMETERS(B) >::type
  {};

  // A type list for specifying arguments
  template < BOOST_MPL_LIST_DEFAULT_PARAMETERS(typename A, ::boost::mpl::null_argument) >
  struct args : ::boost::mpl::type_list< BOOST_MPL_LIST_PARAMETERS(A) >::type
  {};
}

namespace boost { namespace python { 

namespace detail
{
  // This is an mpl BinaryMetaFunction object with a runtime behavior,
  // which is to write the id of the type which is passed as its 2nd
  // compile-time argument into the iterator pointed to by its runtime
  // argument
  struct write_type_id
  {
      // The first argument is Ignored because mpl::for_each is still
      // currently an accumulate (reduce) implementation.
      template <class Ignored, class T> struct apply
      {
          // also an artifact of accumulate-based for_each
          typedef void type;

          // Here's the runtime behavior
          static void execute(converter::undecorated_type_id_t** p)
          {
              *(*p)++ = converter::undecorated_type_id<T>();
          }
      };
  };
}

//
// class_<T,Bases,HolderGenerator>
//
//      This is the primary mechanism through which users will expose
//      C++ classes to Python. The three template arguments are:
//
//        T - The class being exposed to Python
//
//        Bases - An MPL sequence of base classes
//
//        HolderGenerator -
//           An optional type generator for the "holder" which
//           maintains the C++ object inside the Python instance. The
//           default just holds the object "by-value", but other
//           holders can be substituted which will hold the C++ object
//           by smart pointer, for example.
//
template <
    class T // class being wrapped
    , class Bases
    , class HolderGenerator
    >
class class_ : private objects::class_base
{
    typedef class_<T,Bases,HolderGenerator> self;
 public:

    // Automatically derive the class name - only works on some
    // compilers because type_info::name is sometimes mangled (gcc)
    class_();
    
    // Construct with the class name.  [ Would have used a default
    // argument but gcc-2.95.2 choked on typeid(T).name() as a default
    // parameter value]
    class_(char const* name);


    // Wrap a member function or a non-member function which can take
    // a T, T cv&, or T cv* as its first parameter, or a callable
    // python object.
    template <class F>
    self& def(char const* name, F f)
    {
        // Use function::add_to_namespace to achieve overloading if
        // appropriate.
        objects::function::add_to_namespace(
            this->object(), name,
            ref(detail::wrap_function(
                    // This bit of nastiness casts F to a member function of T if possible. 
                    detail::member_function_cast<T,F>::stage1(f).stage2((T*)0).stage3(f)
                    )));
        return *this;
    }

    template <class Fn, class CallPolicy>
    self& def(char const* name, Fn fn, CallPolicy policy)
    {
        this->def(name
                  , boost::python::make_function(
                      // This bit of nastiness casts F to a member function of T if possible. 
                      detail::member_function_cast<T,Fn>::stage1(fn).stage2((T*)0).stage3(fn)
                      , policy)
            );
        
        return *this;
    }
    
    // Define the constructor with the given Args, which should be an
    // MPL sequence of types.
    template <class Args>
    self& def_init(Args const&)
    {
        def("__init__", make_constructor<T,Args,HolderGenerator>());
        return *this;
    }

    // Define the default constructor.
    self& def_init()
    {
        this->def_init(mpl::type_list<>::type());
        return *this;
    }

    // return the underlying object
    ref object() const;

 private: // types
    typedef objects::class_id class_id;
    
    // A helper class which will contain an array of id objects to be
    // passed to the base class constructor
    struct id_vector
    {
        typedef objects::class_id class_id;
        id_vector()
        {
            // Stick the derived class id into the first element of the array
            ids[0] = converter::undecorated_type_id<T>();
    
            // Write the rest of the elements into succeeding positions.
            class_id* p = ids + 1;
            mpl::for_each<Bases, void, detail::write_type_id>::execute(&p);
        }
        
        BOOST_STATIC_CONSTANT(
            std::size_t, size = mpl::size<Bases>::value + 1);
        class_id ids[size];
    };

 private: // helper functions
    void initialize_converters();
};


//
// implementations
//
template <class T, class Bases, class HolderGenerator>
inline class_<T, Bases, HolderGenerator>::class_()
    : class_base(typeid(T).name(), id_vector::size, id_vector().ids)
{
    // Bring the class converters into existence. This static object
    // will survive until the shared library this module lives in is
    // unloaded (that doesn't happen until Python terminates).
    static objects::class_converters<T,Bases> converters(object());
}

template <class T, class Bases, class HolderGenerator>
inline class_<T, Bases, HolderGenerator>::class_(char const* name)
    : class_base(name, id_vector::size, id_vector().ids)
{
    // Bring the class converters into existence. This static object
    // will survive until the shared library this module lives in is
    // unloaded (that doesn't happen until Python terminates).
    static objects::class_converters<T,Bases> converters(object());
}

template <class T, class Bases, class HolderGenerator>
inline ref class_<T, Bases, HolderGenerator>::object() const
{
    typedef objects::class_base base;
    
    return this->base::object();
}

}} // namespace boost::python

#endif // CLASS_DWA200216_HPP
