// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef CLASS_METADATA_DWA2004719_HPP
# define CLASS_METADATA_DWA2004719_HPP
# include <boost/python/converter/shared_ptr_from_python.hpp>

# include <boost/python/object/inheritance.hpp>
# include <boost/python/object/class_wrapper.hpp>
# include <boost/python/object/make_instance.hpp>
# include <boost/python/object/value_holder.hpp>
# include <boost/python/object/pointer_holder.hpp>
# include <boost/python/object/make_ptr_instance.hpp>

# include <boost/python/detail/force_instantiate.hpp>
# include <boost/python/detail/not_specified.hpp>

# include <boost/python/has_back_reference.hpp>
# include <boost/python/bases.hpp>

# include <boost/type_traits/add_pointer.hpp>
# include <boost/type_traits/is_convertible.hpp>
# include <boost/type_traits/is_polymorphic.hpp>

# include <boost/mpl/if.hpp>
# include <boost/mpl/apply_if.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/mpl/or.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/for_each.hpp>
# include <boost/mpl/placeholders.hpp>
# include <boost/mpl/single_view.hpp>
# include <boost/type_traits/is_convertible.hpp>

# include <boost/noncopyable.hpp>
# include <boost/detail/workaround.hpp>

namespace boost { namespace python { namespace objects { 

BOOST_PYTHON_DECL
void copy_class_object(type_info const& src, type_info const& dst);

//
// Support for registering base/derived relationships
//
template <class Derived>
struct register_base_of
{
    template <class Base>
    inline void operator()(Base*) const
    {
        // Register the Base class
        register_dynamic_id<Base>();

        // Register the up-cast
        register_conversion<Derived,Base>(false);

        // Register the down-cast, if appropriate.
        this->register_downcast((Base*)0, is_polymorphic<Base>());
    }
    
 private:
    static inline void register_downcast(void*, mpl::false_) {}
    
    template <class Base>
    static inline void register_downcast(Base*, mpl::true_)
    {
        register_conversion<Base, Derived>(true);
    }

};

//
// Preamble of register_class.  Also used for callback classes, which
// need some registration of their own.
//
template <class T, class Bases>
void register_shared_ptr_from_python_and_casts(T*, Bases)
{
    // Constructor performs registration
    python::detail::force_instantiate(converter::shared_ptr_from_python<T>());

    //
    // register all up/downcasts here.  We're using the alternate
    // interface to mpl::for_each to avoid an MSVC 6 bug.
    //
    register_dynamic_id<T>();
    mpl::for_each(register_base_of<T>(), (Bases*)0, (add_pointer<mpl::_>*)0);
}

//
// Helper for choosing the unnamed held_type argument
//
template <class T, class Prev>
struct select_held_type
  : mpl::if_<
        mpl::or_<
            python::detail::specifies_bases<T>
          , is_same<T,noncopyable>
        >
      , Prev
      , T
    >
{
};

template <
    class T // class being wrapped
  , class X1 // = detail::not_specified
  , class X2 // = detail::not_specified
  , class X3 // = detail::not_specified
>
struct class_metadata
{
    //
    // Calculate the unnamed template arguments
    //
    
    // held_type_arg -- not_specified, [a class derived from] T or a
    // smart pointer to [a class derived from] T.  Preserving
    // not_specified allows us to give class_<T,T> a back-reference.
    typedef typename select_held_type<
        X1
      , typename select_held_type<
            X2
          , typename select_held_type<
                X3
              , python::detail::not_specified
            >::type
        >::type
    >::type held_type_arg;

    // bases
    typedef typename python::detail::select_bases<
        X1
      , typename python::detail::select_bases<
            X2
          , typename python::detail::select_bases<
                X3
              , python::bases<>
            >::type
        >::type
    >::type bases;

    typedef mpl::or_<
        is_same<X1,noncopyable>
      , is_same<X2,noncopyable>
      , is_same<X3,noncopyable>
    > is_noncopyable;
    
    //
    // Holder computation.
    //
    
    // Compute the actual type that will be held in the Holder.
    typedef typename mpl::if_<
        is_same<held_type_arg,python::detail::not_specified>, T, held_type_arg
    >::type held_type;

    // Determine if the object will be held by value
    typedef is_convertible<held_type*,T*> use_value_holder;
    
    // Compute the "wrapped type", that is, if held_type is a smart
    // pointer, we're talking about the pointee.
    typedef typename mpl::apply_if<
        use_value_holder
      , mpl::identity<held_type>
      , pointee<held_type>
    >::type wrapper;

    // Determine whether wrapper needs to be separately registered
    typedef is_base_and_derived<T,wrapper> use_callback_class;

    // Determine whether to use a holder with a back-reference
    typedef mpl::or_<
        use_callback_class
      , has_back_reference<T>
      , is_same<held_type_arg,T>
    > use_back_reference;

    // Select the holder.
    typedef typename mpl::apply_if<
        use_back_reference
      , mpl::if_<
            use_value_holder
          , value_holder_back_reference<T, wrapper>
          , pointer_holder_back_reference<held_type,T>
        >
      , mpl::if_<
            use_value_holder
          , value_holder<T>
          , pointer_holder<held_type,T>
        >
    >::type holder;
    
    inline static void register_() // Register the runtime metadata.
    {
        objects::register_shared_ptr_from_python_and_casts((T*)0, bases());

        class_metadata::maybe_register_callback_class(use_callback_class());

        class_metadata::maybe_register_class_to_python(is_noncopyable());
        
        class_metadata::maybe_register_pointer_to_python(
            (use_value_holder*)0, (use_back_reference*)0);
    }

 private:
    //
    // Support for converting smart pointers to python
    //
    inline static void maybe_register_pointer_to_python(void*,void*) {}
    
    inline static void maybe_register_pointer_to_python(mpl::false_*, mpl::false_*)
    {
        python::detail::force_instantiate(
            objects::class_value_wrapper<
                held_type
              , make_ptr_instance<T, pointer_holder<held_type, T> >
            >()
        );
    }
    //
    // Support for registering to-python converters
    //
    inline static void maybe_register_class_to_python(mpl::true_) {}
    inline static void maybe_register_class_to_python(mpl::false_)
    {
        python::detail::force_instantiate(class_cref_wrapper<T, make_instance<T, holder> >());
    }

    //
    // Support for registering callback classes
    //
    inline static void maybe_register_callback_class(mpl::false_) {}

    inline static void maybe_register_callback_class(mpl::true_)
    {
        objects::register_shared_ptr_from_python_and_casts(
            (wrapper*)0, mpl::single_view<T>());

        // explicit qualification of type_id makes msvc6 happy
        objects::copy_class_object(python::type_id<T>(), python::type_id<wrapper>());
    }
};

}}} // namespace boost::python::object

#endif // CLASS_METADATA_DWA2004719_HPP
