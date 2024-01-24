#include <ranges>
#include <regex>
#include <set>

#include <boost/algorithm/string.hpp>
#include <boost/json/parse.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

int64_t json_sum(const boost::json::value& value, bool ignore_red = false) {
  if (value.is_int64()) {
    return value.as_int64();
  } else if (value.is_object()) {
    int64_t sum = 0;
    for (auto& [key, value]: value.as_object()) {
      sum += json_sum(value, ignore_red);
      if (ignore_red && value == "red") {
        return 0;
      }
    }
    return sum;
  } else if (value.is_array()) {
    int64_t sum = 0;
    for (auto& value: value.as_array()) {
      sum += json_sum(value, ignore_red);
    }
    return sum;
  } else {
    return 0;
  }
}

class day12: public solver {
  boost::json::value input;

public:
  void presolve(std::string input) override { this->input = boost::json::parse(input); }
  std::string solve_first() override { return std::to_string(json_sum(input)); }
  std::string solve_second() override { return std::to_string(json_sum(input, true)); }
};

static bool day12_registered = register_solver<day12>(12);
