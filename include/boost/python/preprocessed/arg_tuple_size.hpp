// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARG_TUPLE_SIZE_DWA2002410_HPP
# define ARG_TUPLE_SIZE_DWA2002410_HPP

# if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<class R>struct arg_tuple_size<R(*)()>{
BOOST_STATIC_CONSTANT(std::size_t,value=0);
};
template<class R,class A0>struct arg_tuple_size<R(*)(A0)>{
BOOST_STATIC_CONSTANT(std::size_t,value=1);
};
template<class R,class A0,class A1>struct arg_tuple_size<R(*)(A0,A1)>{
BOOST_STATIC_CONSTANT(std::size_t,value=2);
};
template<class R,class A0,class A1,class A2>struct arg_tuple_size<R(*)(A0,A1,A2)>{
BOOST_STATIC_CONSTANT(std::size_t,value=3);
};
template<class R,class A0,class A1,class A2,class A3>struct arg_tuple_size<R(*)(A0,A1,A2,A3)>{
BOOST_STATIC_CONSTANT(std::size_t,value=4);
};
template<class R,class A0,class A1,class A2,class A3,class A4>struct arg_tuple_size<R(*)(A0,A1,A2,A3,A4)>{
BOOST_STATIC_CONSTANT(std::size_t,value=5);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>struct arg_tuple_size<R(*)(A0,A1,A2,A3,A4,A5)>{
BOOST_STATIC_CONSTANT(std::size_t,value=6);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>struct arg_tuple_size<R(*)(A0,A1,A2,A3,A4,A5,A6)>{
BOOST_STATIC_CONSTANT(std::size_t,value=7);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>struct arg_tuple_size<R(*)(A0,A1,A2,A3,A4,A5,A6,A7)>{
BOOST_STATIC_CONSTANT(std::size_t,value=8);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>struct arg_tuple_size<R(*)(A0,A1,A2,A3,A4,A5,A6,A7,A8)>{
BOOST_STATIC_CONSTANT(std::size_t,value=9);
};

 
 template<class R,class A0>struct arg_tuple_size<R(A0::*)()>{
BOOST_STATIC_CONSTANT(std::size_t,value=1);
};
template<class R,class A0,class A1>struct arg_tuple_size<R(A0::*)(A1)>{
BOOST_STATIC_CONSTANT(std::size_t,value=2);
};
template<class R,class A0,class A1,class A2>struct arg_tuple_size<R(A0::*)(A1,A2)>{
BOOST_STATIC_CONSTANT(std::size_t,value=3);
};
template<class R,class A0,class A1,class A2,class A3>struct arg_tuple_size<R(A0::*)(A1,A2,A3)>{
BOOST_STATIC_CONSTANT(std::size_t,value=4);
};
template<class R,class A0,class A1,class A2,class A3,class A4>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4)>{
BOOST_STATIC_CONSTANT(std::size_t,value=5);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5)>{
BOOST_STATIC_CONSTANT(std::size_t,value=6);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6)>{
BOOST_STATIC_CONSTANT(std::size_t,value=7);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7)>{
BOOST_STATIC_CONSTANT(std::size_t,value=8);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8)>{
BOOST_STATIC_CONSTANT(std::size_t,value=9);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>{
BOOST_STATIC_CONSTANT(std::size_t,value=10);
};
// Metrowerks thinks this creates ambiguities
#  if !defined(__MWERKS__) || __MWERKS__ > 0x2407
template<class R,class A0>struct arg_tuple_size<R(A0::*)()const>{
BOOST_STATIC_CONSTANT(std::size_t,value=1);
};
template<class R,class A0,class A1>struct arg_tuple_size<R(A0::*)(A1)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=2);
};
template<class R,class A0,class A1,class A2>struct arg_tuple_size<R(A0::*)(A1,A2)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=3);
};
template<class R,class A0,class A1,class A2,class A3>struct arg_tuple_size<R(A0::*)(A1,A2,A3)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=4);
};
template<class R,class A0,class A1,class A2,class A3,class A4>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=5);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=6);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=7);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=8);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=9);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>{
BOOST_STATIC_CONSTANT(std::size_t,value=10);
};
template<class R,class A0>struct arg_tuple_size<R(A0::*)()volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=1);
};
template<class R,class A0,class A1>struct arg_tuple_size<R(A0::*)(A1)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=2);
};
template<class R,class A0,class A1,class A2>struct arg_tuple_size<R(A0::*)(A1,A2)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=3);
};
template<class R,class A0,class A1,class A2,class A3>struct arg_tuple_size<R(A0::*)(A1,A2,A3)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=4);
};
template<class R,class A0,class A1,class A2,class A3,class A4>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=5);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=6);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=7);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=8);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=9);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=10);
};
template<class R,class A0>struct arg_tuple_size<R(A0::*)()const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=1);
};
template<class R,class A0,class A1>struct arg_tuple_size<R(A0::*)(A1)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=2);
};
template<class R,class A0,class A1,class A2>struct arg_tuple_size<R(A0::*)(A1,A2)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=3);
};
template<class R,class A0,class A1,class A2,class A3>struct arg_tuple_size<R(A0::*)(A1,A2,A3)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=4);
};
template<class R,class A0,class A1,class A2,class A3,class A4>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=5);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=6);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=7);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=8);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=9);
};
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>struct arg_tuple_size<R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const volatile>{
BOOST_STATIC_CONSTANT(std::size_t,value=10);
};
#  endif

# else

template<class R>
char_array<0>arg_tuple_size_helper(R(*)());
template<class R,class A0>
char_array<1>arg_tuple_size_helper(R(*)(A0));
template<class R,class A0,class A1>
char_array<2>arg_tuple_size_helper(R(*)(A0,A1));
template<class R,class A0,class A1,class A2>
char_array<3>arg_tuple_size_helper(R(*)(A0,A1,A2));
template<class R,class A0,class A1,class A2,class A3>
char_array<4>arg_tuple_size_helper(R(*)(A0,A1,A2,A3));
template<class R,class A0,class A1,class A2,class A3,class A4>
char_array<5>arg_tuple_size_helper(R(*)(A0,A1,A2,A3,A4));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>
char_array<6>arg_tuple_size_helper(R(*)(A0,A1,A2,A3,A4,A5));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
char_array<7>arg_tuple_size_helper(R(*)(A0,A1,A2,A3,A4,A5,A6));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
char_array<8>arg_tuple_size_helper(R(*)(A0,A1,A2,A3,A4,A5,A6,A7));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
char_array<9>arg_tuple_size_helper(R(*)(A0,A1,A2,A3,A4,A5,A6,A7,A8));

template<class R,class A0>
char_array<1>arg_tuple_size_helper(R(A0::*)());
template<class R,class A0,class A1>
char_array<2>arg_tuple_size_helper(R(A0::*)(A1));
template<class R,class A0,class A1,class A2>
char_array<3>arg_tuple_size_helper(R(A0::*)(A1,A2));
template<class R,class A0,class A1,class A2,class A3>
char_array<4>arg_tuple_size_helper(R(A0::*)(A1,A2,A3));
template<class R,class A0,class A1,class A2,class A3,class A4>
char_array<5>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>
char_array<6>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
char_array<7>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
char_array<8>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
char_array<9>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8));
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
char_array<10>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9));

template<class R,class A0>
char_array<1>arg_tuple_size_helper(R(A0::*)()const);
template<class R,class A0,class A1>
char_array<2>arg_tuple_size_helper(R(A0::*)(A1)const);
template<class R,class A0,class A1,class A2>
char_array<3>arg_tuple_size_helper(R(A0::*)(A1,A2)const);
template<class R,class A0,class A1,class A2,class A3>
char_array<4>arg_tuple_size_helper(R(A0::*)(A1,A2,A3)const);
template<class R,class A0,class A1,class A2,class A3,class A4>
char_array<5>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4)const);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>
char_array<6>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5)const);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
char_array<7>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6)const);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
char_array<8>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7)const);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
char_array<9>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8)const);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
char_array<10>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const);

template<class R,class A0>
char_array<1>arg_tuple_size_helper(R(A0::*)()volatile);
template<class R,class A0,class A1>
char_array<2>arg_tuple_size_helper(R(A0::*)(A1)volatile);
template<class R,class A0,class A1,class A2>
char_array<3>arg_tuple_size_helper(R(A0::*)(A1,A2)volatile);
template<class R,class A0,class A1,class A2,class A3>
char_array<4>arg_tuple_size_helper(R(A0::*)(A1,A2,A3)volatile);
template<class R,class A0,class A1,class A2,class A3,class A4>
char_array<5>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4)volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>
char_array<6>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5)volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
char_array<7>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6)volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
char_array<8>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7)volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
char_array<9>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8)volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
char_array<10>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)volatile);

template<class R,class A0>
char_array<1>arg_tuple_size_helper(R(A0::*)()const volatile);
template<class R,class A0,class A1>
char_array<2>arg_tuple_size_helper(R(A0::*)(A1)const volatile);
template<class R,class A0,class A1,class A2>
char_array<3>arg_tuple_size_helper(R(A0::*)(A1,A2)const volatile);
template<class R,class A0,class A1,class A2,class A3>
char_array<4>arg_tuple_size_helper(R(A0::*)(A1,A2,A3)const volatile);
template<class R,class A0,class A1,class A2,class A3,class A4>
char_array<5>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4)const volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5>
char_array<6>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5)const volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6>
char_array<7>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6)const volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
char_array<8>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7)const volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
char_array<9>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8)const volatile);
template<class R,class A0,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
char_array<10>arg_tuple_size_helper(R(A0::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const volatile);

# endif 

#endif // ARG_TUPLE_SIZE_DWA2002410_HPP
