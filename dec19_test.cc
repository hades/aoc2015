#define BOOST_TEST_MODULE dec19_test

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <spdlog/spdlog.h>

#include "solvers.h"

constexpr const char input[] = R"(e => H
e => O
H => HO
H => OH
O => HH

HOHOHO
)";

BOOST_AUTO_TEST_CASE(dec19_test_first) {
  spdlog::set_level(spdlog::level::debug);
  auto solver = solvers[18]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_first() == "7");
}

BOOST_AUTO_TEST_CASE(dec19_test_second) {
  spdlog::set_level(spdlog::level::debug);
  auto solver = solvers[18]();
  solver->presolve(input);
  BOOST_TEST(solver->solve_second() == "6");
}
