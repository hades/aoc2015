#include <ranges>
#include <regex>
#include <set>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

std::string process(const std::string& input, size_t times) {
  std::string result = input;
  for (size_t i = 0; i < times; ++i) {
    std::string next;
    std::string::iterator it = result.begin();
    while (it != result.end()) {
      if (!std::isdigit(*it)) {
        break;
      }
      std::string::iterator it_start = it;
      while (it != result.end() && *it_start == *it) {
        ++it;
      }
      next += std::to_string(std::distance(it_start, it));
      next += *it_start;
    }
    result = next;
  }
  return std::to_string(result.size());
}

class day10: public solver {
  std::string input;

public:
  void presolve(std::string input) override { this->input = input; }
  std::string solve_first() override { return process(input, 40); }
  std::string solve_second() override { return process(input, 50); }
};

static bool day10_registered = register_solver<day10>(10);
