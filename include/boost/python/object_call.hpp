# // Copyright David Abrahams 2002. Permission to copy, use,
# // modify, sell and distribute this software is granted provided this
# // copyright notice appears in all copies. This software is provided
# // "as is" without express or implied warranty, and with no claim as
# // to its suitability for any purpose.

#if !defined(BOOST_PP_IS_ITERATING)
# error Boost.Python - do not include this file!
#endif

#define N BOOST_PP_ITERATION()

	template <BOOST_PYTHON_UNARY_ENUM(N, class A)>
	typename dependent<object, A0>::type
	operator()(BOOST_PYTHON_BINARY_ENUM(N, A, const& a)) const
	{
		typedef typename dependent<object, A0>::type obj;
		U const& self = *static_cast<U const*>(this);
		return call<obj>(converter::get_managed_object(self), BOOST_PYTHON_UNARY_ENUM(N, a));
	}

#undef N
