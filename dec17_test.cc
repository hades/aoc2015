#define BOOST_TEST_MODULE dec17_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

constexpr const char input[] = R"(20
15
10
5
5
125
)";

BOOST_AUTO_TEST_CASE(dec17_test_first) {
  auto solver = solvers[16]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == "4");
}

BOOST_AUTO_TEST_CASE(dec17_test_second) {
  auto solver = solvers[16]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == "3");
}
