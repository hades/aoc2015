#define BOOST_TEST_MODULE dec13_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

constexpr const char input[] = R"(Alice would gain 54 happiness units by sitting next to Bob.
Alice would lose 79 happiness units by sitting next to Carol.
Alice would lose 2 happiness units by sitting next to David.
Bob would gain 83 happiness units by sitting next to Alice.
Bob would lose 7 happiness units by sitting next to Carol.
Bob would lose 63 happiness units by sitting next to David.
Carol would lose 62 happiness units by sitting next to Alice.
Carol would gain 60 happiness units by sitting next to Bob.
Carol would gain 55 happiness units by sitting next to David.
David would gain 46 happiness units by sitting next to Alice.
David would lose 7 happiness units by sitting next to Bob.
David would gain 41 happiness units by sitting next to Carol.
)";

BOOST_AUTO_TEST_CASE(dec13_test_first) {
  auto solver = solvers[12]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == "330");
}

BOOST_AUTO_TEST_CASE(dec13_test_second) {
  auto solver = solvers[12]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == "286");
}
