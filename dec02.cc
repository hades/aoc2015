#include <ranges>
#include <string>

#include <boost/lexical_cast.hpp>

#include "solvers.h"

class day02: public solver {
  std::vector<std::vector<int>> dims;

public:
  void presolve(std::string input) override {
    for (const auto line: std::views::split(input, '\n')) {
      dims.push_back(std::views::split(line, 'x') |
                     std::views::transform([](auto v) { return boost::lexical_cast<int>(std::string_view(v)); }) |
                     std::ranges::to<std::vector>());
    }
  }
  std::string solve_first() override {
    int total = 0;
    for (const auto& dim: dims) {
      if (dim.size() != 3) {
        continue;
      }
      int l = dim[0];
      int w = dim[1];
      int h = dim[2];
      int a = l * w;
      int b = w * h;
      int c = h * l;
      int min = std::min({a, b, c});
      total += 2 * a + 2 * b + 2 * c + min;
    }
    return std::to_string(total);
  }
  std::string solve_second() override {
    int total = 0;
    for (const auto& dim: dims) {
      if (dim.size() != 3) {
        continue;
      }
      int l = dim[0];
      int w = dim[1];
      int h = dim[2];
      int max = std::max({l, w, h});
      total += 2 * (l + w + h - max) + l * w * h;
    }
    return std::to_string(total);
  }
};

static bool day02_registered = register_solver<day02>(2);
