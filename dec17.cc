#include <map>
#include <set>
#include <utility>

#include <boost/algorithm/string.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

std::vector<std::vector<int>> possible_combinations(const std::map<int, int>& containers, int liters) {
  if (liters == 0) {
    return {{}};
  }
  if (containers.empty()) {
    return {};
  }
  std::vector<std::vector<int>> result;
  auto new_containers = containers;
  for (auto& [container_size, container_count]: containers) {
    if (container_size > liters)
      continue;
    if (container_count == 0)
      continue;
    new_containers[container_size] = 0;
    for (int i = 1; i <= container_count; i++) {
      if (i * container_size > liters)
        break;
      auto sub_result = possible_combinations(new_containers, liters - i * container_size);
      for (auto& sub: sub_result) {
        for (int j = 0; j < i; j++) {
          sub.push_back(container_size);
        }
        result.push_back(std::move(sub));
        for (int j = 1; j < boost::math::binomial_coefficient<double>(container_count, i); j++) {
          result.push_back(result.back());
        }
      }
    }
  }
  return result;
}

class day17: public solver {
  std::vector<std::vector<int>> combinations;

public:
  void presolve(std::string input) override {
    std::vector<std::string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));
    std::map<int, int> containers;
    for (const auto& line: lines) {
      if (line.empty()) {
        continue;
      }
      containers[std::stoi(line)]++;
    }
    combinations = possible_combinations(containers, 150);
  }
  std::string solve_first() override { return std::to_string(combinations.size()); }
  std::string solve_second() override {
    std::sort(combinations.begin(), combinations.end(),
              [](const auto& a, const auto& b) { return a.size() < b.size(); });
    int number_of_smallest =
        std::distance(combinations.begin(), std::find_if(combinations.begin(), combinations.end(), [&](const auto& c) {
                        return c.size() != combinations.front().size();
                      }));
    return std::to_string(number_of_smallest);
  }
};

static bool day17_registered = register_solver<day17>(17);
