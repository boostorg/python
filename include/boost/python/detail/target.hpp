// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TARGET_DWA2002513_HPP
# define TARGET_DWA2002513_HPP

# include <boost/type.hpp>

namespace boost { namespace python { namespace detail {

//
// target(x) - deduce the type of the first argument when bind(x) is
// invoked.
//

// functions
template <class Target, class R>
boost::type<Target>* target(R (*)(Target)) { return 0; }

template <class Target, class R, class A1>
boost::type<Target>* target(R (*)(Target, A1)) { return 0; }
  
template <class Target, class R, class A1, class A2>
boost::type<Target>* target(R (*)(Target, A1, A2)) { return 0; }
  
template <class Target, class R, class A1, class A2, class A3>
boost::type<Target>* target(R (*)(Target, A1, A2, A3)) { return 0; }

// data member pointers
template <class Target, class R>
boost::type<Target&>* target(R (Target::*)) { return 0; }

// member Functions
template <class Target, class R>
boost::type<Target&>* target(R (Target::*)()) { return 0; }

template <class Target, class R, class A1>
boost::type<Target&>* target(R (Target::*)(A1)) { return 0; }

template <class Target, class R, class A1, class A2>
boost::type<Target&>* target(R (Target::*)(A1,A2)) { return 0; }

template <class Target, class R, class A1, class A2, class A3>
boost::type<Target&>* target(R (Target::*)(A1,A2,A3)) { return 0; }

// const member functions
template <class Target, class R>
boost::type<Target const&>* target(R (Target::*)() const) { return 0; }

template <class Target, class R, class A1>
boost::type<Target const&>* target(R (Target::*)(A1) const) { return 0; }

template <class Target, class R, class A1, class A2>
boost::type<Target const&>* target(R (Target::*)(A1,A2) const) { return 0; }

template <class Target, class R, class A1, class A2, class A3>
boost::type<Target const&>* target(R (Target::*)(A1,A2,A3) const) { return 0; }

// volatile member functions
template <class Target, class R>
boost::type<Target volatile&>* target(R (Target::*)() volatile) { return 0; }

template <class Target, class R, class A1>
boost::type<Target volatile&>* target(R (Target::*)(A1) volatile) { return 0; }

template <class Target, class R, class A1, class A2>
boost::type<Target volatile&>* target(R (Target::*)(A1,A2) volatile) { return 0; }

template <class Target, class R, class A1, class A2, class A3>
boost::type<Target volatile&>* target(R (Target::*)(A1,A2,A3) volatile) { return 0; }

// const volatile member functions
template <class Target, class R>
boost::type<Target const volatile&>* target(R (Target::*)() const volatile) { return 0; }

template <class Target, class R, class A1>
boost::type<Target const volatile&>* target(R (Target::*)(A1) const volatile) { return 0; }

template <class Target, class R, class A1, class A2>
boost::type<Target const volatile&>* target(R (Target::*)(A1,A2) const volatile) { return 0; }

template <class Target, class R, class A1, class A2, class A3>
boost::type<Target const volatile&>* target(R (Target::*)(A1,A2,A3) const volatile) { return 0; }

}}} // namespace boost::python::detail

#endif // TARGET_DWA2002513_HPP
