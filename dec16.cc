#include <algorithm>
#include <map>
#include <ranges>
#include <regex>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

class day16: public solver {
  std::map<int, std::map<std::string, int>> aunts;
  static const std::map<std::string, int> aunt_data;

public:
  void presolve(std::string input) override {
    static const std::regex re(R"(Sue (\d+): (\w+): (\d+), (\w+): (\d+), (\w+): (\d+))");
    std::vector<std::string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));
    for (const auto& line: lines) {
      if (line.empty()) {
        continue;
      }
      std::smatch match;
      if (!std::regex_match(line, match, re)) {
        throw cpptrace::runtime_error("invalid input: " + line);
      }
      aunts[std::stoi(match[1])][match[2]] = std::stoi(match[3]);
      aunts[std::stoi(match[1])][match[4]] = std::stoi(match[5]);
      aunts[std::stoi(match[1])][match[6]] = std::stoi(match[7]);
    }
  }
  std::string solve_first() override {
    for (const auto& [aunt, data]: aunts) {
      bool found = true;
      for (const auto& [key, value]: data) {
        if (auto it = aunt_data.find(key); it != aunt_data.end() && it->second != value) {
          found = false;
          break;
        }
      }
      if (found) {
        return std::to_string(aunt);
      }
    }
    throw cpptrace::runtime_error("not found");
  }
  std::string solve_second() override {
    for (const auto& [aunt, data]: aunts) {
      bool found = true;
      for (const auto& [key, value]: data) {
        if (auto it = aunt_data.find(key); it != aunt_data.end() && it->second != value) {
          if ((key == "cats" || key == "trees") && it->second < value) {
            continue;
          }
          if ((key == "pomeranians" || key == "goldfish") && it->second > value) {
            continue;
          }
          found = false;
          break;
        }
      }
      if (found) {
        return std::to_string(aunt);
      }
    }
    throw cpptrace::runtime_error("not found");
  }
};

static bool day16_registered = register_solver<day16>(16);

const std::map<std::string, int> day16::aunt_data{
    {"children", 3}, {"cats", 7},     {"samoyeds", 2}, {"pomeranians", 3}, {"akitas", 0},
    {"vizslas", 0},  {"goldfish", 5}, {"trees", 3},    {"cars", 2},        {"perfumes", 1},
};
