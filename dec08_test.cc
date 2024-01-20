#define BOOST_TEST_MODULE dec08_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

constexpr const char* inputs[] = {
    R"("")",
    R"("abc")",
    R"("aaa\"aaa")",
    R"("\x27")",
};

constexpr const char* expected_results[] = {
    "2",
    "2",
    "3",
    "5",
};

constexpr const char* expected_results_second[] = {
    "4",
    "4",
    "6",
    "5",
};

BOOST_DATA_TEST_CASE(dec08_test_first, data::make(inputs) ^ data::make(expected_results), input, expected_result) {
  auto solver = solvers[7]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == expected_result);
}

BOOST_DATA_TEST_CASE(dec08_test_second, data::make(inputs) ^ data::make(expected_results_second), input,
                     expected_result) {
  auto solver = solvers[7]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == expected_result);
}
