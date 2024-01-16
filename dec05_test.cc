#define BOOST_TEST_MODULE dec05_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "solvers.h"

namespace data = boost::unit_test::data;

BOOST_AUTO_TEST_CASE(dec05_test_first) {
  auto solver = solvers[4]();
  solver->presolve(R"(aei
xazegov
aeiouaeiouaeiou
xx
abcdde
aabbccdd
ugknbfddgicrmopn
aaa
jchzalrnumimnmhp
haegwjzuvuyypxyu
dvszwmarrgswjxmb)");
  BOOST_TEST((solver->solve_first() == "2"));
}

BOOST_AUTO_TEST_CASE(dec05_test_second) {
  auto solver = solvers[4]();
  solver->presolve(R"(
qjhvhtzxzqqjkmpb
xxyxx
uurcxstgmygtbstg
ieodomkazucvgmuy)");
  BOOST_TEST((solver->solve_second() == "2"));
}
