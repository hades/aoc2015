#include <algorithm>
#include <map>
#include <ranges>
#include <regex>

#include <boost/algorithm/string.hpp>
#include <boost/range/numeric.hpp>
#include <cpptrace/cpptrace.hpp>
#include <z3++.h>

#include "solvers.h"
#include "z3_util.h"

#include <iostream>

std::string solve(std::map<std::string, std::tuple<int, int, int, int, int>> ingredient_qualities, std::optional<int>) {
  z3::set_param("trace", "true");
  z3::set_param("verbose", "10");
  z3::context ctx;
  auto ingredient_names = std::views::keys(ingredient_qualities) | std::ranges::to<std::vector<std::string>>();
  const auto& [quality_sort, qualities, qualities_test] =
      enumeration_sort(ctx, "quality", {"capacity", "durability", "flavor", "texture", "calories"});
  const auto& [ingredient_sort, ingredients, ingredients_test] = enumeration_sort(ctx, "ingredient", ingredient_names);
  z3::func_decl quality = ctx.function("q", ingredient_sort, quality_sort, ctx.int_sort());
  z3::func_decl quantity = ctx.function("v", ingredient_sort, ctx.int_sort());
  z3::optimize opt(ctx);
  z3::expr total_quantity = ctx.int_val(0);
  z3::expr total_capacity = ctx.int_val(0);
  z3::expr total_durability = ctx.int_val(0);
  z3::expr total_flavor = ctx.int_val(0);
  z3::expr total_texture = ctx.int_val(0);
  for (size_t i = 0; i < ingredient_names.size(); ++i) {
    opt.add(quantity(ingredients[i]()) >= 0);
    total_quantity = total_quantity + quantity(ingredients[i]());
    total_capacity = total_capacity + quality(ingredients[i](), qualities[0]()) * quantity(ingredients[i]());
    total_durability = total_durability + quality(ingredients[i](), qualities[1]()) * quantity(ingredients[i]());
    total_flavor = total_flavor + quality(ingredients[i](), qualities[2]()) * quantity(ingredients[i]());
    total_texture = total_texture + quality(ingredients[i](), qualities[3]()) * quantity(ingredients[i]());
    opt.add(quality(ingredients[i](), qualities[0]()) == std::get<0>(ingredient_qualities[ingredient_names[i]]));
    opt.add(quality(ingredients[i](), qualities[1]()) == std::get<1>(ingredient_qualities[ingredient_names[i]]));
    opt.add(quality(ingredients[i](), qualities[2]()) == std::get<2>(ingredient_qualities[ingredient_names[i]]));
    opt.add(quality(ingredients[i](), qualities[3]()) == std::get<3>(ingredient_qualities[ingredient_names[i]]));
    opt.add(quality(ingredients[i](), qualities[4]()) == std::get<4>(ingredient_qualities[ingredient_names[i]]));
  }
  opt.add(total_quantity == 100);
  // opt.add(total_capacity > 0);
  // opt.add(total_durability > 0);
  // opt.add(total_flavor > 0);
  // opt.add(total_texture > 0);
  // z3::expr total_quality = total_capacity * total_durability * total_flavor * total_texture;
  z3::expr total_quality = z3::max(ctx.int_val(0), total_capacity) * z3::max(ctx.int_val(0), total_durability) *
                           z3::max(ctx.int_val(0), total_flavor) * z3::max(ctx.int_val(0), total_texture);
  z3::optimize::handle obj = opt.maximize(total_quality);
  std::cerr << opt << std::endl;
  if (opt.check() != z3::sat) {
    throw cpptrace::runtime_error("no solution found");
  }
  return opt.upper(obj).get_decimal_string(0);
}

/*
int solve(const std::vector<std::tuple<int, int, int, int, int>>& ingredient_qualities, std::vector<int>
current_ingredients, std::optional<int> calories_requirement = std::nullopt) { int current_sum =
boost::accumulate(current_ingredients, 0); if (current_ingredients.size() == ingredient_qualities.size() - 1) {
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
std::optional<int> calories_requirement = std::nullopt) { auto vec = ingredient_qualities | std::views::values |
std::ranges::to<std::vector<std::tuple<int, int, int, int, int>>>(); return std::to_string(solve(vec, {},
calories_requirement));
}
*/

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
