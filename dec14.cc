#include <ranges>
#include <regex>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

class day14: public solver {
  std::vector<std::tuple<int, int, int>> params;

public:
  void presolve(std::string input) override {
    static const std::regex re(R"(\w+ can fly (\d+) km/s for (\d+) seconds?, but then must rest for (\d+) seconds?\.)");
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
      params.emplace_back(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]));
    }
  }
  std::string solve_first() override {
    auto races = params | std::views::transform([](const auto& param) -> int {
                   const auto [speed, duration, rest] = param;
                   int cycle = duration + rest;
                   int cycles = 2503 / cycle;
                   int remainder = 2503 % cycle;
                   int distance = cycles * speed * duration + speed * std::min(remainder, duration);
                   return distance;
                 });
    return std::to_string(*std::ranges::max_element(races));
  }
  std::string solve_second() override {
    std::vector<int> scores(params.size());
    for (int i = 1; i <= 2503; ++i) {
      int max_distance = 0;
      for (size_t j = 0; j < params.size(); ++j) {
        const auto [speed, duration, rest] = params[j];
        int cycle = duration + rest;
        int cycles = i / cycle;
        int remainder = i % cycle;
        int distance = cycles * speed * duration + speed * std::min(remainder, duration);
        max_distance = std::max(max_distance, distance);
      }
      for (size_t j = 0; j < params.size(); ++j) {
        const auto [speed, duration, rest] = params[j];
        int cycle = duration + rest;
        int cycles = i / cycle;
        int remainder = i % cycle;
        int distance = cycles * speed * duration + speed * std::min(remainder, duration);
        if (distance == max_distance) {
          ++scores[j];
        }
      }
    }
    return std::to_string(*std::ranges::max_element(scores));
  }
};

static bool day14_registered = register_solver<day14>(14);
