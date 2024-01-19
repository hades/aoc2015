#define BOOST_TEST_MODULE dec07_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

constexpr const char PROGRAM[] = R"(123 -> x
456 -> y
x AND y -> d
x OR y -> e
x LSHIFT 2 -> f
y RSHIFT 2 -> g
NOT x -> h
NOT y -> i)";

constexpr const char PROGRAM_SECOND[] = R"(123 -> x
456 -> b
b -> y
x AND y -> d
x OR y -> e
x LSHIFT 2 -> f
y RSHIFT 2 -> g
NOT x -> h
NOT y -> i
g -> a)";

constexpr const char* vars[] = {
    "d", "e", "f", "g", "h", "i", "x", "y",
};

constexpr const char* expected_results[] = {
    "72", "507", "492", "114", "65412", "65079", "123", "456",
};

BOOST_DATA_TEST_CASE(dec07_test_first, data::make(vars) ^ data::make(expected_results), var, expected_result) {
  auto solver = solvers[6]();
  solver->presolve(std::format("{}\n{} -> a", PROGRAM, var));
  BOOST_TEST(solver->solve_first() == expected_result);
}

BOOST_AUTO_TEST_CASE(dec07_test_second) {
  auto solver = solvers[6]();
  solver->presolve(PROGRAM_SECOND);
  BOOST_TEST(solver->solve_second() == "28");
}
