#define BOOST_TEST_MODULE dec09_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

constexpr const char INPUT[] = R"(London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141
)";

BOOST_AUTO_TEST_CASE(dec09_test_first) {
  auto solver = solvers[8]();
  solver->presolve(INPUT);
  BOOST_TEST(solver->solve_first() == "605");
}

BOOST_AUTO_TEST_CASE(dec09_test_second) {
  auto solver = solvers[8]();
  solver->presolve(INPUT);
  BOOST_TEST(solver->solve_second() == "982");
}
