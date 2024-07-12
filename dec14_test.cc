#define BOOST_TEST_MODULE dec14_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

constexpr const char input[] = R"(Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.
)";

BOOST_AUTO_TEST_CASE(dec14_test_first) {
  auto solver = solvers[13]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == "2660");
}

BOOST_AUTO_TEST_CASE(dec14_test_second) {
  auto solver = solvers[13]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == "1564");
}
