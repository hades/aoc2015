#define BOOST_TEST_MODULE dec01_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

const char* inputs_first[] = {
    ">",
    "^>v<",
    "^v^v^v^v^v",
};

int expected_results_first[] = {
    2,
    4,
    2,
};

const char* inputs_second[] = {
    "^v",
    "^>v<",
    "^v^v^v^v^v",
};

int expected_results_second[] = {
    3,
    3,
    11,
};

BOOST_DATA_TEST_CASE(dec03_test_first, data::make(inputs_first) ^ data::make(expected_results_first), input,
                     expected_result) {
  auto solver = solvers[2]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_first() == std::to_string(expected_result)));
}

BOOST_DATA_TEST_CASE(dec03_test_second, data::make(inputs_second) ^ data::make(expected_results_second), input,
                     expected_result) {
  auto solver = solvers[2]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_second() == std::to_string(expected_result)));
}
