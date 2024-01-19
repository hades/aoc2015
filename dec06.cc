#include <iostream>
#include <ranges>
#include <regex>
#include <string>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

class day06: public solver {
  enum class op { on, off, toggle };

  std::vector<std::tuple<op, int, int, int, int>> input;

public:
  void presolve(std::string input) override {
    this->input.resize(0);
    std::vector<std::string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));
    for (const auto& line: lines) {
      std::smatch m;
      bool matched =
          std::regex_match(line, m, std::regex(R"((turn on|turn off|toggle) (\d+),(\d+) through (\d+),(\d+))"));
      if (!matched)
        continue;
      op o;
      if (m.str(1) == "turn on")
        o = op::on;
      else if (m.str(1) == "turn off")
        o = op::off;
      else
        o = op::toggle;
      std::cerr << m.str(1) << " " << m.str(2) << " " << m.str(3) << " " << m.str(4) << " " << m.str(5) << std::endl;
      this->input.emplace_back(o, std::stoi(m.str(2)), std::stoi(m.str(3)), std::stoi(m.str(4)), std::stoi(m.str(5)));
    }
  }
  std::string solve_first() override {
    std::vector<std::vector<bool>> lights(1000, std::vector<bool>(1000, false));
    for (const auto& [o, x1, y1, x2, y2]: input) {
      for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
          switch (o) {
          case op::on:
            lights[x][y] = true;
            break;
          case op::off:
            lights[x][y] = false;
            break;
          case op::toggle:
            lights[x][y] = !lights[x][y];
            break;
          }
        }
      }
    }
    int result = 0;
    for (const auto& row: lights) {
      for (bool light: row) {
        if (light)
          ++result;
      }
    }
    return std::to_string(result);
  }
  std::string solve_second() override {
    std::vector<std::vector<int>> lights(1000, std::vector<int>(1000, 0));
    for (const auto& [o, x1, y1, x2, y2]: input) {
      for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
          switch (o) {
          case op::on:
            lights[x][y]++;
            break;
          case op::off:
            lights[x][y] = std::max(0, lights[x][y] - 1);
            break;
          case op::toggle:
            lights[x][y] = lights[x][y] += 2;
            break;
          }
        }
      }
    }
    int result = 0;
    for (const auto& row: lights) {
      for (int light: row) {
        result += light;
      }
    }
    return std::to_string(result);
  }
};

static bool day06_registered = register_solver<day06>(6);
