#define BOOST_TEST_MODULE dec01_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

const char* inputs_first[] = {
    "(())", "()()", "(((", "(()(()(", "))(((((", "())", "))(", ")))", ")())())",
};

int expected_results_first[] = {
    0, 0, 3, 3, 3, -1, -1, -3, -3,
};

BOOST_DATA_TEST_CASE(dec01_test_first, data::make(inputs_first) ^ data::make(expected_results_first), input,
                     expected_result) {
  auto solver = solvers[0]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_first() == std::to_string(expected_result)));
}

const char* inputs_second[] = {
    ")",
    "()())",
};

int expected_results_second[] = {
    1,
    5,
};

BOOST_DATA_TEST_CASE(dec01_test_second, data::make(inputs_second) ^ data::make(expected_results_second), input,
                     expected_result) {
  auto solver = solvers[0]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_second() == std::to_string(expected_result)));
}
