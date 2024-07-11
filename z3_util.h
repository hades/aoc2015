#pragma once

#include <ranges>
#include <string>
#include <vector>

#include <z3++.h>

inline std::tuple<z3::sort, z3::func_decl_vector, z3::func_decl_vector>
enumeration_sort(z3::context& ctx, std::string name, std::vector<std::string> values) {
  z3::func_decl_vector consts(ctx), tests(ctx);
  auto cvalues = values | std::views::transform([](const std::string& value) { return value.c_str(); }) |
                 std::ranges::to<std::vector<const char*>>();
  z3::sort sort = ctx.enumeration_sort(name.c_str(), cvalues.size(), cvalues.data(), consts, tests);
  return {sort, consts, tests};
}
