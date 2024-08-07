// Boost.Units - A C++ library for zero-overhead dimensional analysis and
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/core/ignore_unused.hpp>
#include <boost/units/systems/si/base.hpp>
#include <boost/units/quantity.hpp>

void foo()
{
    BOOST_CONSTEXPR_OR_CONST boost::units::quantity<boost::units::si::dimensionless> d = boost::units::quantity< boost::units::si::dimensionless >();
    boost::ignore_unused(d);
}
