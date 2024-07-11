#define BOOST_TEST_MODULE dec18_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

constexpr const char input[] = R"(.#.#.#
...##.
#....#
..#...
#.#..#
####..
)";

BOOST_AUTO_TEST_CASE(dec18_test_first) {
  auto solver = solvers[17]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == "4");
}

BOOST_AUTO_TEST_CASE(dec18_test_second) {
  auto solver = solvers[17]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == "7");
}
