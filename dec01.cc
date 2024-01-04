#include <string>

#include "solvers.h"

class day01: public solver {
  int basement_reached_on_step;
  int last_floor;
public:
  void presolve(std::string input) override {
    bool been_to_basement = false;
    int floor = 0;
    int counter = 0;
    for (const char ch: input) {
      counter++;
      if (ch == '(')
        floor++;
      else if (ch == ')')
        floor--;
      else
        continue;
      if (floor == -1 && !been_to_basement) {
        basement_reached_on_step = counter;
        been_to_basement = true;
      }
    }
    last_floor = floor;
  }
  std::string solve_first() override { return std::to_string(last_floor); }
  std::string solve_second() override { return std::to_string(basement_reached_on_step); }
};

static bool day01_registered = register_solver<day01>(1);
