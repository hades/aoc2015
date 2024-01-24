#define BOOST_TEST_MODULE dec12_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

constexpr const char* inputs[] = {
    R"([1,2,3])",      R"({"a":2,"b":4})", R"([[[3]]])", R"({"a":{"b":4},"c":-1})",
    R"({"a":[-1,1]})", R"([-1,{"a":1}])",  R"([])",      R"({})",
};

constexpr const char* expected_results[] = {
    "6", "6", "3", "3", "0", "0", "0", "0",
};

constexpr const char* inputs_second[] = {
    R"([1,2,3])",
    R"([1,{"c":"red","b":2},3])",
    R"({"d":"red","e":[1,2,3,4],"f":5})",
    R"([1,"red",5])",
};

constexpr const char* expected_results_second[] = {
    "6",
    "4",
    "0",
    "6",
};

BOOST_DATA_TEST_CASE(dec12_test_first, data::make(inputs) ^ data::make(expected_results), input, expected_result) {
  auto solver = solvers[11]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == expected_result);
}

BOOST_DATA_TEST_CASE(dec12_test_second, data::make(inputs_second) ^ data::make(expected_results_second), input,
                     expected_result) {
  auto solver = solvers[11]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == expected_result);
}
