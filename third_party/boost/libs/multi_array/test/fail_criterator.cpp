// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

//
// fail_criterator.cpp
//   const_reverse_iterator/reverse_iterator conversion  test
//

#include <boost/multi_array.hpp>

#include <boost/core/lightweight_test.hpp>


int main() {
    typedef boost::multi_array<int,3> array;

    typedef array::reverse_iterator riterator1;
    typedef array::const_reverse_iterator criterator1;

    // ILLEGAL conversion from const_reverse_iterator to reverse_iterator
    riterator1 in = criterator1();

    return boost::report_errors();
}
