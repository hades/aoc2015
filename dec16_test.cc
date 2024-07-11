#define BOOST_TEST_MODULE dec16_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

constexpr const char input[] = R"(Sue 260: goldfish: 0, vizslas: 0, samoyeds: 2
Sue 371: trees: 2, cars: 3, vizslas: 8
Sue 372: trees: 10, children: 9, cats: 1
Sue 373: pomeranians: 3, perfumes: 1, vizslas: 0
)";

BOOST_AUTO_TEST_CASE(dec16_test_first) {
  auto solver = solvers[15]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == "373");
}

BOOST_AUTO_TEST_CASE(dec16_test_second) {
  auto solver = solvers[15]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == "260");
}
