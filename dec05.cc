#include <ranges>
#include <regex>
#include <string>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

class day05: public solver {
  std::vector<std::string> input;

public:
  void presolve(std::string input) override { boost::split(this->input, input, boost::is_any_of("\n")); }
  std::string solve_first() override {
    int nice = 0;
    for (const auto& string: input) {
      if (string.empty())
        continue;
      if (std::regex_search(string, std::regex(R"(ab|cd|pq|xy)")))
        continue;
      if (std::regex_search(string, std::regex(R"(([a-z])\1)")) &&
          std::regex_search(string, std::regex(R"([aeiou].*[aeiou].*[aeiou])"))) {
        ++nice;
      }
    }
    return std::to_string(nice);
  }
  std::string solve_second() override {
    int nice = 0;
    for (const auto& string: input) {
      if (string.empty())
        continue;
      if (std::regex_search(string, std::regex(R"(([a-z][a-z]).*\1)")) &&
          std::regex_search(string, std::regex(R"(([a-z]).\1)"))) {
        ++nice;
      }
    }
    return std::to_string(nice);
  }
};

static bool day05_registered = register_solver<day05>(5);
