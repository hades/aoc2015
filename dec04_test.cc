#define BOOST_TEST_MODULE dec04_test

#include <iostream>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

const char* inputs_first[] = {
    "abcdef",
    "pqrstuv",
};

int expected_results_first[] = {
    609043,
    1048970,
};

int expected_results_second[] = {
    6742839,
    5714438,
};

BOOST_DATA_TEST_CASE(dec04_test_first, data::make(inputs_first) ^ data::make(expected_results_first), input,
                     expected_result) {
  auto solver = solvers[3]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_first() == std::to_string(expected_result)));
}

BOOST_DATA_TEST_CASE(dec04_test_second, data::make(inputs_first) ^ data::make(expected_results_second), input,
                     expected_result) {
  auto solver = solvers[3]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_second() == std::to_string(expected_result)));
}
