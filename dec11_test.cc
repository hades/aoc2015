#define BOOST_TEST_MODULE dec11_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

constexpr const char* inputs[] = {
    "abcdefgh",
    "ghijklmn",
};

constexpr const char* expected_results[] = {
    "abcdffaa",
    "ghjaabcc",
};

constexpr const char* expected_results_second[] = {
    "abcdffbb",
    "ghjbbcdd",
};

BOOST_DATA_TEST_CASE(dec11_test_first, data::make(inputs) ^ data::make(expected_results), input, expected_result) {
  auto solver = solvers[10]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == expected_result);
}

BOOST_DATA_TEST_CASE(dec11_test_second, data::make(inputs) ^ data::make(expected_results_second), input,
                     expected_result) {
  auto solver = solvers[10]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == expected_result);
}
