// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_DWA200216_HPP
# define CLASS_DWA200216_HPP

# include <boost/python/class_fwd.hpp>
# include <boost/python/object/class.hpp>
# include <boost/python/bases.hpp>

# include <boost/python/object.hpp>

# include <boost/python/type_id.hpp>
# include <boost/python/object/class_converters.hpp>
# include <boost/type_traits/ice.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/mpl/size.hpp>
# include <boost/mpl/for_each.hpp>
# include <boost/mpl/bool_c.hpp>
# include <boost/python/object/select_holder.hpp>
# include <boost/python/object/class_wrapper.hpp>
# include <boost/python/object/make_instance.hpp>
# include <boost/python/data_members.hpp>
# include <boost/utility.hpp>
# include <boost/python/object/pickle_support.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/object/add_to_namespace.hpp>
# include <boost/python/signature.hpp>
# include <boost/python/init.hpp>
# include <boost/python/args_fwd.hpp>

# include <boost/python/detail/overloads_fwd.hpp>
# include <boost/python/detail/operator_id.hpp>
# include <boost/python/detail/member_function_cast.hpp>
# include <boost/python/detail/def_helper.hpp>
# include <boost/python/detail/force_instantiate.hpp>

namespace boost { namespace python {

enum no_init_t { no_init };

namespace detail
{
  // This function object is used with mpl::for_each to write the id
  // of the type a pointer to which is passed as its 2nd compile-time
  // argument. into the iterator pointed to by its runtime argument
  struct write_type_id
  {
      write_type_id(type_info**p) : p(p) {}

      // Here's the runtime behavior
      template <class T>
      void operator()(T*) const
      {
          *(*p)++ = type_id<T>();
      }

      type_info** p;
  };

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
  template <class T, class SelectHolder>
  static inline void register_copy_constructor(mpl::bool_c<true> const&, SelectHolder const& , T* = 0)
  {
      typedef typename SelectHolder::type holder;
      force_instantiate(objects::class_wrapper<T,holder, objects::make_instance<T,holder> >());
      SelectHolder::register_();
  }

  // Tag dispatched to have no effect.
  template <class T, class SelectHolder>
  static inline void register_copy_constructor(mpl::bool_c<false> const&, SelectHolder const&, T* = 0)
  {
      SelectHolder::register_();
  }

  // A helpful compile-time assertion which gives a reasonable error
  // message if T can't be default-constructed.
  template <class T>
  class assert_default_constructible
  {
      template <class U>
      static int specify_init_arguments_or_no_init_for_class_(U const&);
   public:
      assert_default_constructible()
      {
          force_instantiate(
              sizeof(
                  specify_init_arguments_or_no_init_for_class_(T())
                  ));
                      
      }
  };
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
 public: // types
    typedef objects::class_base base;
    typedef T wrapped_type;
    
    typedef class_<T,X1,X2,X3> self;
    BOOST_STATIC_CONSTANT(bool, is_copyable = (!detail::has_noncopyable<X1,X2,X3>::value));

    typedef typename detail::select_held_type<
        X1, typename detail::select_held_type<
        X2, typename detail::select_held_type<
        X3
    >::type>::type>::type held_type;

    typedef objects::select_holder<T,held_type> holder_selector;

 private:

    typedef typename detail::select_bases<X1
            , typename detail::select_bases<X2
              , typename boost::python::detail::select_bases<X3>::type
              >::type
            >::type bases;


    // A helper class which will contain an array of id objects to be
    // passed to the base class constructor
    struct id_vector
    {
        id_vector()
        {
            // Stick the derived class id into the first element of the array
            ids[0] = type_id<T>();

            // Write the rest of the elements into succeeding positions.
            type_info* p = ids + 1;
            mpl::for_each(detail::write_type_id(&p), (bases*)0, (add_pointer<mpl::_>*)0);
        }

        BOOST_STATIC_CONSTANT(
            std::size_t, size = mpl::size<bases>::value + 1);
        type_info ids[size];
    };
    friend struct id_vector;

 public:
    // Automatically derive the class name - only works on some
    // compilers because type_info::name is sometimes mangled (gcc)
//    class_();           // With default-constructor init function
//    class_(no_init_t);  // With no init function

    // Construct with the class name, with or without docstring, and default init() function
    class_(char const* name, char const* doc = 0);

    // Construct with class name, no docstring, and no init() function
    class_(char const* name, no_init_t);

    // Construct with class name, docstring, and no init() function
    class_(char const* name, char const* doc, no_init_t);

    template <class DerivedT>
    inline class_(char const* name, init_base<DerivedT> const& i)
        : base(name, id_vector::size, id_vector().ids)
    {
        this->register_();
        define_init(*this, i.derived());
        this->set_instance_size(holder_selector::additional_size());
    }

    template <class DerivedT>
    inline class_(char const* name, char const* doc, init_base<DerivedT> const& i)
        : base(name, id_vector::size, id_vector().ids, doc)
    {
        this->register_();
        define_init(*this, i.derived());
        this->set_instance_size(holder_selector::additional_size());
    }

    // Wrap a member function or a non-member function which can take
    // a T, T cv&, or T cv* as its first parameter, or a callable
    // python object.
    template <class F>
    self& def(char const* name, F f)
    {
        this->def_impl(name, f, detail::keywords<>(), default_call_policies(), 0, &f);
        return *this;
    }

    template <class DerivedT>
    self& def(init_base<DerivedT> const& i)
    {
        define_init(*this, i.derived());
        return *this;
    }

    template <class Arg1T, class Arg2T>
    self& def(char const* name, Arg1T arg1, Arg2T const& arg2)
    {
        //  The arguments may be:
        //      def(name, function)
        //      def(name, function, policy)
        //      def(name, function, doc_string)
        //      def(name, signature, overloads)

        dispatch_def(&arg2, name, arg1, arg2);
        return *this;
    }

    template <class Arg1T, class Arg2T, class Arg3T>
    self& def(char const* name, Arg1T arg1, Arg2T const& arg2, Arg3T const& arg3)
    {
        //  The arguments are definitely:
        //      def(name, function, policy, doc_string)
        //      def(name, function, doc_string, policy)

        dispatch_def(&arg2, name, arg1, arg2, arg3);
        return *this;
    }

    template <class Arg1T, class Arg2T, class Arg3T, class Arg4T>
    self& def(char const* name, Arg1T arg1, Arg2T const& arg2, Arg3T const& arg3, Arg4T const& arg4)
    {
        dispatch_def(&arg2, name, arg1, arg2, arg3, arg4);
        return *this;
    }

    template <detail::operator_id id, class L, class R>
    self& def(detail::operator_<id,L,R> const& op)
    {
        typedef detail::operator_<id,L,R> op_t;
        return this->def(op.name(), &op_t::template apply<T>::execute);
    }

    //
    // Data member access
    //
    template <class D>
    self& def_readonly(char const* name, D T::*pm)
    {
        this->add_property(name, make_getter(pm));
        return *this;
    }

    template <class D>
    self& def_readwrite(char const* name, D T::*pm)
    {
        return this->add_property(name, make_getter(pm), make_setter(pm));
    }

    // Property creation
    template <class Get>
    self& add_property(char const* name, Get const& fget)
    {
        base::add_property(name, object(fget));
        return *this;
    }

    template <class Get, class Set>
    self& add_property(char const* name, Get const& fget, Set const& fset)
    {
        base::add_property(name, object(fget), object(fset));
        return *this;
    }

    template <class U>
    self& setattr(char const* name, U const& x)
    {
        this->base::setattr(name, object(x));
        return *this;
    }

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

 private: // helper functions

    template <class Fn, class Policies, class Keywords>
    inline void def_impl(
        char const* name
        , Fn fn
        , Keywords const& keywords
        , Policies const& policies
        , char const* doc
        , ...)
    {
        objects::add_to_namespace(
            *this, name,
            make_function(
                // This bit of nastiness casts F to a member function of T if possible.
                detail::member_function_cast<T,Fn>::stage1(fn).stage2((T*)0).stage3(fn)
                , policies, keywords)
            , doc);
    }

    template <class F>
    inline void def_impl(
        char const* name
        , F f
        , detail::keywords<> const&
        , default_call_policies const&
        , char const* doc
        , object const*)
    {
        objects::add_to_namespace(*this, name, f, doc);
    }

    inline void register_() const;

    template <class OverloadsT, class SigT>
    void dispatch_def(
        detail::overloads_base const*,
        char const* name,
        SigT sig,
        OverloadsT const& overloads)
    {
        //  convert sig to a type_list (see detail::get_signature in signature.hpp)
        //  before calling detail::define_with_defaults.
        detail::define_with_defaults(
            name, overloads, *this, detail::get_signature(sig));
    }

    template <class Fn, class A1>
    void dispatch_def(
        void const*,
        char const* name,
        Fn fn,
        A1 const& a1)
    {
        detail::def_helper<A1> helper(a1);
      
        this->def_impl(
            name, fn
            , helper.keywords()
            , helper.policies()
            , helper.doc()
            , &fn);

    }

    template <class Fn, class A1, class A2>
    void dispatch_def(
        void const*,
        char const* name,
        Fn fn,
        A1 const& a1,
        A2 const& a2)
    {
        detail::def_helper<A1,A2> helper(a1,a2);
      
        this->def_impl(
            name, fn
            , helper.keywords()
            , helper.policies()
            , helper.doc()
            , &fn);
    }

    template <class Fn, class A1, class A2, class A3>
    void dispatch_def(
        void const*,
        char const* name,
        Fn fn,
        A1 const& a1,
        A2 const& a2,
        A3 const& a3
        )
    {
        detail::def_helper<A1,A2,A3> helper(a1,a2,a3);
      
        this->def_impl(
            name, fn
            , helper.keywords()
            , helper.policies()
            , helper.doc()
            , &fn);
    }
};


//
// implementations
//
        // register converters
template <class T, class X1, class X2, class X3>
inline void class_<T,X1,X2,X3>::register_() const
{
    objects::register_class_from_python<T,bases>();

    detail::register_copy_constructor<T>(
        mpl::bool_c<is_copyable>()
        , holder_selector::execute((held_type*)0)
        );
}

template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>::class_(char const* name, char const* doc)
    : base(name, id_vector::size, id_vector().ids, doc)
{
    this->register_();
    detail::assert_default_constructible<T>();
    this->def(init<>());
    this->set_instance_size(holder_selector::additional_size());
}

template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>::class_(char const* name, no_init_t)
    : base(name, id_vector::size, id_vector().ids)
{
    this->register_();
    this->def_no_init();
}

template <class T, class X1, class X2, class X3>
inline class_<T,X1,X2,X3>::class_(char const* name, char const* doc, no_init_t)
    : base(name, id_vector::size, id_vector().ids, doc)
{
    this->register_();
    this->def_no_init();
}

namespace detail
{
  template <class T1, class T2, class T3>
  struct has_noncopyable
      : type_traits::ice_or<
        is_same<T1,noncopyable>::value
      , is_same<T2,noncopyable>::value
      , is_same<T3,noncopyable>::value>
  {};


    template <class T, class Prev>
    struct select_held_type
        : mpl::if_c<
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
