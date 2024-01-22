#define BOOST_TEST_MODULE dec10_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

BOOST_AUTO_TEST_CASE(dec10_test_first) {
  auto solver = solvers[9]();
  solver->presolve("1");
  BOOST_TEST(solver->solve_first() == "82350");
}

BOOST_AUTO_TEST_CASE(dec10_test_second) {
  auto solver = solvers[9]();
  solver->presolve("1");
  BOOST_TEST(solver->solve_second() == "1166642");
}
