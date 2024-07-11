#define BOOST_TEST_MODULE dec15_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

constexpr const char input[] = R"(Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3
)";

BOOST_AUTO_TEST_CASE(dec15_test_first) {
  auto solver = solvers[14]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == "62842880");
}

BOOST_AUTO_TEST_CASE(dec15_test_second) {
  auto solver = solvers[14]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == "57600000");
}
