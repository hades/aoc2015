#define BOOST_TEST_MODULE dec20_test

#include <boost/test/unit_test.hpp>

#include "solvers.h"

BOOST_AUTO_TEST_CASE(dec20_test_first) {
  auto solver = solvers[19]();
  solver->presolve("149");
  BOOST_TEST(solver->solve_first() == "8");
}

BOOST_AUTO_TEST_CASE(dec20_test_second) {
  auto solver = solvers[19]();
  solver->presolve("149");
  BOOST_TEST(solver->solve_second() == "6");
}
