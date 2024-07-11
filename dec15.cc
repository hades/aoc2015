#include <algorithm>
#include <map>
#include <ranges>
#include <regex>

#include <boost/algorithm/string.hpp>
#include <boost/range/numeric.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

int solve(const std::vector<std::tuple<int, int, int, int, int>>& ingredient_qualities,
          std::vector<int> current_ingredients, std::optional<int> calories_requirement = std::nullopt) {
  int current_sum = boost::accumulate(current_ingredients, 0);
  if (current_ingredients.size() == ingredient_qualities.size() - 1) {
    current_ingredients.push_back(100 - current_sum);
    int capacity = 0;
    int durability = 0;
    int flavor = 0;
    int texture = 0;
    int calories = 0;
    for (size_t i = 0; i < ingredient_qualities.size(); ++i) {
      const auto& qualities = ingredient_qualities[i];
      auto [capacity_, durability_, flavor_, texture_, calories_] = qualities;
      capacity += capacity_ * current_ingredients[i];
      durability += durability_ * current_ingredients[i];
      flavor += flavor_ * current_ingredients[i];
      texture += texture_ * current_ingredients[i];
      calories += calories_ * current_ingredients[i];
    }
    if (calories_requirement.has_value() && calories != calories_requirement.value()) {
      return std::numeric_limits<int>::min();
    }
    return std::max(capacity, 0) * std::max(durability, 0) * std::max(flavor, 0) * std::max(texture, 0);
  }
  int max = 100 - current_sum - (ingredient_qualities.size() - current_ingredients.size() - 1);
  int best_result = std::numeric_limits<int>::min();
  for (int i = 1; i <= max; ++i) {
    current_ingredients.push_back(i);
    best_result = std::max(best_result, solve(ingredient_qualities, current_ingredients, calories_requirement));
    current_ingredients.pop_back();
  }
  return best_result;
}

std::string solve(const std::map<std::string, std::tuple<int, int, int, int, int>>& ingredient_qualities,
                  std::optional<int> calories_requirement = std::nullopt) {
  auto vec =
      ingredient_qualities | std::views::values | std::ranges::to<std::vector<std::tuple<int, int, int, int, int>>>();
  return std::to_string(solve(vec, {}, calories_requirement));
}

class day15: public solver {
  std::map<std::string, std::tuple<int, int, int, int, int>> ingredients;

public:
  void presolve(std::string input) override {
    static const std::regex re(
        R"((\w+): capacity (-?\d+), durability (-?\d+), flavor (-?\d+), texture (-?\d+), calories (-?\d+))");
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
      ingredients[match[1]] = {std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4]), std::stoi(match[5]),
                               std::stoi(match[6])};
    }
  }
  std::string solve_first() override { return solve(ingredients, std::nullopt); }
  std::string solve_second() override { return solve(ingredients, 500); }
};

static bool day15_registered = register_solver<day15>(15);
