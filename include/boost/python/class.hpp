// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA200216_HPP
# define CLASS_DWA200216_HPP

# include <boost/python/class_fwd.hpp>
# include <boost/python/bases.hpp>
# include <boost/python/args.hpp>
# include <boost/python/handle.hpp>
# include <boost/python/object/class.hpp>
# include <boost/python/type_id.hpp>
# include <boost/python/detail/wrap_function.hpp>
# include <boost/python/detail/member_function_cast.hpp>
# include <boost/python/object/class_converters.hpp>
# include <boost/type_traits/ice.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/mpl/size.hpp>
# include <boost/mpl/for_each.hpp>
# include <boost/mpl/bool_t.hpp>
# include <boost/python/object/select_holder.hpp>
# include <boost/python/object/class_wrapper.hpp>
# include <boost/python/data_members.hpp>
# include <boost/utility.hpp>
# include <boost/python/detail/operator_id.hpp>
# include <boost/python/object/pickle_support.hpp>

namespace boost { namespace python { 

namespace detail
{
  struct write_type_id;
  
  template <class T, class Prev = detail::not_specified>
  struct select_held_type;
  
  template <class T1, class T2, class T3>
  struct has_noncopyable;

  template <detail::operator_id, class L, class R>
  struct operator_;

  // Register a to_python converter for a class T, depending on the
  // type of the first (tag) argument. The 2nd argument is a pointer
  // to the type of holder that must be created. The 3rd argument is a
  // reference to the Python type object to be created.
  template <class T, class Holder>
  static inline void register_copy_constructor(mpl::bool_t<true> const&, Holder*, object const& obj, T* = 0)
  {
      objects::class_wrapper<T,Holder> x(obj);
  }

  // Tag dispatched to have no effect.
  template <class T, class Holder>
  static inline void register_copy_constructor(mpl::bool_t<false> const&, Holder*, object const&, T* = 0)
  {
  }
}

//
// class_<T,Bases,HolderGenerator>
//
//      This is the primary mechanism through which users will expose
//      C++ classes to Python. The three template arguments are:
//
template <
    class T // class being wrapped
    , class X1 // = detail::not_specified
    , class X2 // = detail::not_specified
    , class X3 // = detail::not_specified
    >
class class_ : public objects::class_base
{
    typedef objects::class_base base;

    typedef class_<T,X1,X2,X3> self;
    BOOST_STATIC_CONSTANT(bool, is_copyable = (!detail::has_noncopyable<X1,X2,X3>::value));
    
    typedef typename detail::select_held_type<
        X1, typename detail::select_held_type<
        X2, typename detail::select_held_type<
        X3
    >::type>::type>::type held_type;
    
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
            *this, name
            , object(
                detail::new_reference(
                    detail::wrap_function(
                    // This bit of nastiness casts F to a member function of T if possible. 
                    detail::member_function_cast<T,F>::stage1(f).stage2((T*)0).stage3(f)
                        ))));
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

    template <detail::operator_id id, class L, class R>
    self& def(detail::operator_<id,L,R> const& op)
    {
        typedef detail::operator_<id,L,R> op_t;
        // Use function::add_to_namespace to achieve overloading if
        // appropriate.
        objects::function::add_to_namespace(
            *this, op.name()
            , object(
                detail::new_reference(
                    detail::wrap_function(&op_t::template apply<T>::execute))));
        return *this;
    }
    
    // Define the constructor with the given Args, which should be an
    // MPL sequence of types.
    template <class Args>
    self& def_init(Args const&)
    {
        def("__init__",
            make_constructor<Args>(
                // Using runtime type selection works around a CWPro7 bug.
                objects::select_holder<T,held_type>((held_type*)0).get()
                )
            );
        return *this;
    }

    template <class Args, class CallPolicy>
    self& def_init(Args const&, CallPolicy policy)
    {
        def("__init__",
            make_constructor<Args>(
                policy
                // Using runtime type selection works around a CWPro7 bug.
                , objects::select_holder<T,held_type>((held_type*)0).get()
                )
            );
        return *this;
    }

    // Define the default constructor.
    self& def_init()
    {
        this->def_init(mpl::type_list<>::type());
        return *this;
    }

    //
    // Data member access
    //
    template <class D>
    self& def_readonly(char const* name, D T::*pm)
    {
        handle<> fget(make_getter(pm));
        this->add_property(name, fget);
        return *this;
    }

    template <class D>
    self& def_readwrite(char const* name, D T::*pm)
    {
        handle<> fget(make_getter(pm));
        handle<> fset(make_setter(pm));
        return this->add_property(name, fget, fset);
    }

    // Property creation
    self& add_property(char const* name, handle<> const& fget);
    self& add_property(char const* name, handle<> const& fget, handle<> const& fset);

    self& setattr(char const* name, handle<> const&);

    // Pickle support
    template <typename PickleSuiteType>
    self& def_pickle(PickleSuiteType const& x)
    {
      error_messages::must_be_derived_from_pickle_suite(x);
      detail::pickle_suite_finalize<PickleSuiteType>::register_(
        *this,
        &PickleSuiteType::getinitargs,
        &PickleSuiteType::getstate,
        &PickleSuiteType::setstate,
        PickleSuiteType::getstate_manages_dict());
      return *this;
    }

 private: // types
    typedef objects::class_id class_id;
    
    typedef typename detail::select_bases<X1
            , typename detail::select_bases<X2
              , typename boost::python::detail::select_bases<X3>::type
              >::type
            >::type bases;
    
    // A helper class which will contain an array of id objects to be
    // passed to the base class constructor
    struct id_vector
    {
        typedef objects::class_id class_id;
        id_vector()
        {
            // Stick the derived class id into the first element of the array
            ids[0] = type_id<T>();
    
            // Write the rest of the elements into succeeding positions.
            class_id* p = ids + 1;
            mpl::for_each<bases, void, detail::write_type_id>::execute(&p);
        }
        
        BOOST_STATIC_CONSTANT(
            std::size_t, size = mpl::size<bases>::value + 1);
        class_id ids[size];
    };
    friend struct id_vector;
};


//
// implementations
//
template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>::class_()
    : base(typeid(T).name(), id_vector::size, id_vector().ids)
{
    // register converters
    objects::register_class_from_python<T,bases>();
    
    detail::register_copy_constructor<T>(
        mpl::bool_t<is_copyable>()
        , objects::select_holder<T,held_type>((held_type*)0).get()
        , *this);
}

template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>::class_(char const* name)
    : base(name, id_vector::size, id_vector().ids)
{
    // register converters
    objects::register_class_from_python<T,bases>();
    
    detail::register_copy_constructor<T>(
        mpl::bool_t<is_copyable>()
        , objects::select_holder<T,held_type>((held_type*)0).get()
        , *this);
}


template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>& class_<T,X1,X2,X3>::add_property(char const* name, handle<> const& fget)
{
    base::add_property(name, fget);
    return *this;
}

template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>& class_<T,X1,X2,X3>::add_property(char const* name, handle<> const& fget, handle<> const& fset)
{
    base::add_property(name, fget, fset);
    return *this;
}

template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>& class_<T,X1,X2,X3>::setattr(char const* name, handle<> const& x)
{
    base::setattr(name, x);
    return *this;
}

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
          static void execute(type_info** p)
          {
              *(*p)++ = type_id<T>();
          }
      };
  };


  template <class T1, class T2, class T3>
  struct has_noncopyable
      : type_traits::ice_or<
        is_same<T1,noncopyable>::value
      , is_same<T2,noncopyable>::value
      , is_same<T3,noncopyable>::value>
  {};


    template <class T, class Prev>
    struct select_held_type
        : mpl::select_type<
            type_traits::ice_or<
                 specifies_bases<T>::value
               , is_same<T,noncopyable>::value
            >::value
            , Prev
            , T
          >
    {
    };
}

}} // namespace boost::python

#endif // CLASS_DWA200216_HPP
