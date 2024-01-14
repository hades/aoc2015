#include <map>
#include <string>

#include "solvers.h"

class day03: public solver {
  std::string input;

public:
  void presolve(std::string input) override { this->input = input; }
  std::string solve_first() override {
    std::map<std::pair<int, int>, int> house_visits;
    int x = 0;
    int y = 0;
    house_visits[{x, y}]++;
    for (const char c: input) {
      switch (c) {
      case '^':
        y++;
        break;
      case 'v':
        y--;
        break;
      case '>':
        x++;
        break;
      case '<':
        x--;
        break;
      }
      house_visits[{x, y}]++;
    }
    return std::to_string(house_visits.size());
  }
  std::string solve_second() override {
    std::map<std::pair<int, int>, int> house_visits;
    int sx = 0;
    int sy = 0;
    int rx = 0;
    int ry = 0;
    bool santa = true;
    house_visits[{0, 0}]++;
    for (const char c: input) {
      int& x = santa ? sx : rx;
      int& y = santa ? sy : ry;
      switch (c) {
      case '^':
        y++;
        break;
      case 'v':
        y--;
        break;
      case '>':
        x++;
        break;
      case '<':
        x--;
        break;
      }
      house_visits[{x, y}]++;
      santa = !santa;
    }
    return std::to_string(house_visits.size());
  }
};

static bool day03_registered = register_solver<day03>(3);
