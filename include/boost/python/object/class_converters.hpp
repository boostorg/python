// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CLASS_CONVERTERS_DWA2002119_HPP
# define CLASS_CONVERTERS_DWA2002119_HPP

# include <boost/python/object/class_wrapper.hpp>
# include <boost/mpl/fold.hpp>
# include <boost/python/reference.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/object/find_instance.hpp>
# include <boost/python/object/inheritance.hpp>

namespace boost { namespace python { namespace objects { 

//////////////////////////////////////////////////////////////////////
//
// register_base_of<T> -
//      A BinaryMetaFunction object which registers a single base
//      class of T, and the corresponding cast(s)
//


// register_downcast/do_nothing -
//      Helpers for register_base_of<> which take care of registering
//      down-casts
template <class Base, class Derived>
struct register_downcast
{
    static void execute()
    {
        register_conversion<Base, Derived>(true);
    }
};

struct do_nothing
{
    static void execute() { }
};

// Here's where the real work gets done:
template <class Derived>
struct register_base_of
{
    // We're not using any state so we supply Ingored argument
    template <class Ignored, class Base>
    struct apply
    {
        typedef void type; // 'type' needs to be defined for the same reasons

        // Here's the runtime part:
        static void execute()
        {
            // Register the Base class
            register_dynamic_id<Base>();
            // Register the up-cast
            register_conversion<Derived,Base>(false);

            // Register the down-cast, if appropriate.
            mpl::select_if_c<
                is_polymorphic<Base>::value
                , register_downcast<Base,Derived>
                , do_nothing
                >::type::execute();
        }
    };
};


// Brings into existence all converters associated with a class Bases
// is expected to be an mpl sequence of base types.
template <class Derived, class Bases>
inline void register_class_from_python(Derived* = 0, Bases* = 0)
{
    // cause the static registration to be instantiated. Can't just
    // cast it to void on all compilers; some will skip its
    // initialization.
    void const* ignored = &instance_finder<Derived>::registration;
    (void)ignored;
    
    // register all up/downcasts here
    register_dynamic_id<Derived>();

    // register each base in the sequence
    mpl::fold<Bases, void, register_base_of<Derived> >::execute();
}

}}} // namespace boost::python::object

#endif // CLASS_CONVERTERS_DWA2002119_HPP
