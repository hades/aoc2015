#include <map>
#include <ranges>
#include <regex>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>
#include <z3++.h>

#include "solvers.h"
#include "z3_util.h"

std::string solve(std::map<std::string, std::map<std::string, int>> happiness_modifiers) {
  z3::context ctx;
  auto people_names = std::views::keys(happiness_modifiers) | std::ranges::to<std::vector<std::string>>();
  const auto& [person, persons, persons_test] = enumeration_sort(ctx, "person", people_names);
  const auto& [side, sides, sides_test] = enumeration_sort(ctx, "side", {"left", "right"});
  z3::func_decl adjacent = ctx.function("adjacent", person, side, person);
  z3::func_decl happiness_modifier = ctx.function("happiness_modifier", person, person, ctx.int_sort());
  z3::optimize opt(ctx);
  for (const auto& p: persons) {
    opt.add(adjacent(adjacent(p(), sides[0]()), sides[1]()) == p());
    opt.add(adjacent(p(), sides[0]()) != adjacent(p(), sides[1]()));
    opt.add(adjacent(p(), sides[0]()) != p());
    opt.add(adjacent(p(), sides[1]()) != p());
  }
  z3::expr no_small_loops = adjacent(persons[0](), sides[0]());
  for (size_t i = 2; i < persons.size(); ++i) {
    no_small_loops = adjacent(no_small_loops, sides[0]());
    opt.add(no_small_loops != persons[0]());
  }
  for (size_t i = 0; i < people_names.size(); ++i) {
    for (size_t j = 0; j < people_names.size(); ++j) {
      if (i == j)
        continue;
      opt.add(happiness_modifier(persons[i](), persons[j]()) == happiness_modifiers[people_names[i]][people_names[j]]);
    }
  }
  z3::expr_vector happiness_terms(ctx);
  for (const auto& p: persons) {
    for (const auto& s: sides) {
      happiness_terms.push_back(happiness_modifier(p(), adjacent(p(), s())));
    }
  }
  z3::optimize::handle obj = opt.maximize(z3::sum(happiness_terms));
  if (opt.check() != z3::sat) {
    throw cpptrace::runtime_error("no solution found");
  }
  return opt.upper(obj).get_decimal_string(0);
}

class day13: public solver {
  std::map<std::string, std::map<std::string, int>> happiness_modifiers;

public:
  void presolve(std::string input) override {
    static const std::regex re(R"((\w+) would (gain|lose) (\d+) happiness units by sitting next to (\w+).)");
    std::vector<std::string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));
    for (const auto& line: lines) {
      if (line.empty()) {
        continue;
      }
      std::smatch match;
      if (std::regex_match(line, match, re)) {
        int modifier = std::stoi(match[3]);
        if (match[2] == "lose") {
          modifier = -modifier;
        }
        happiness_modifiers[match[1]][match[4]] = modifier;
      }
    }
  }
  std::string solve_first() override { return solve(happiness_modifiers); }
  std::string solve_second() override {
    auto new_modifiers = happiness_modifiers;
    new_modifiers["me"] = {};
    for (auto& [name, mods]: new_modifiers) {
      mods["me"] = 0;
      new_modifiers["me"][name] = 0;
    }
    return solve(new_modifiers);
  }
};

static bool day13_registered = register_solver<day13>(13);
