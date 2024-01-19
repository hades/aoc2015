#define BOOST_TEST_MODULE dec06_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

BOOST_AUTO_TEST_CASE(dec06_test_first) {
  auto solver = solvers[5]();
  solver->presolve(R"(turn on 1,1 through 5,5
toggle 0,0 through 4,4
turn off 2,2 through 3,3
turn off 5,5 through 6,6)");
  BOOST_TEST(solver->solve_first() == "17");
}

BOOST_AUTO_TEST_CASE(dec06_test_second) {
  auto solver = solvers[5]();
  solver->presolve(R"(turn on 1,1 through 5,5
toggle 0,0 through 4,4
turn off 2,2 through 3,3
turn off 5,5 through 6,6)");
  BOOST_TEST(solver->solve_second() == "70");
}
