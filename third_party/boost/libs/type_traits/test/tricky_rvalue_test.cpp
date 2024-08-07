
//  (C) Copyright John Maddock 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef TEST_STD
#  include <type_traits>
#else
#  include <boost/type_traits/is_convertible.hpp>
#  include <boost/type_traits/is_lvalue_reference.hpp>
#  include <boost/type_traits/is_rvalue_reference.hpp>
#  include <boost/type_traits/is_reference.hpp>
#  include <boost/type_traits/is_function.hpp>
#endif
#include "test.hpp"
#include "check_integral_constant.hpp"
#include <boost/detail/workaround.hpp>

TT_TEST_BEGIN(rvalue_reference_test)

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<int (&&)(int)>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_rvalue_reference<int (&)(int)>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_rvalue_reference<int (&&)(int)>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_rvalue_reference<int(&&)(int, ...)>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_rvalue_reference<void(&&)(void)>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_rvalue_reference<void(&&)(int, double const&)>::value, true);
#if !(defined(CI_SUPPRESS_KNOWN_ISSUES) && (BOOST_WORKAROUND(BOOST_GCC, < 40700)) || BOOST_WORKAROUND(BOOST_MSVC, <= 1700))
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_convertible<int&&, int&>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_convertible<int(), int(&&)()>::value), true);
#endif
#endif

TT_TEST_END
