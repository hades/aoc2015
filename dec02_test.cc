#define BOOST_TEST_MODULE dec02_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

const char* inputs_first[] = {
    "2x3x4",
    "1x1x10",
};

int expected_results_first[] = {
    58,
    43,
};

int expected_results_second[] = {
    34,
    14,
};

BOOST_DATA_TEST_CASE(dec02_test_first, data::make(inputs_first) ^ data::make(expected_results_first), input,
                     expected_result) {
  auto solver = solvers[1]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_first() == std::to_string(expected_result)));
}

BOOST_DATA_TEST_CASE(dec02_test_second, data::make(inputs_first) ^ data::make(expected_results_second), input,
                     expected_result) {
  auto solver = solvers[1]();
  solver->presolve(input);
  BOOST_TEST((solver->solve_second() == std::to_string(expected_result)));
}
