#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

class day20: public solver {
  int goal = 0;

public:
  void presolve(std::string input) override {
    boost::trim_right(input);
    goal = boost::lexical_cast<int>(input);
  }

  std::string solve_first() override {
    int max_possible_house = goal / 10 + 2;
    std::vector<int> factors(max_possible_house, 1);
    for (int i = 2; i < max_possible_house; ++i) {
      for (int j = i; j < max_possible_house; j += i) {
        factors[j] += i;
      }
    }
    for (int i = 1; i < max_possible_house; ++i) {
      if (factors[i] >= goal / 10) {
        return std::to_string(i);
      }
    }
    throw cpptrace::runtime_error("no solution found");
  }

  std::string solve_second() override {
    int max_possible_house = goal / 11 + 2;
    std::vector<int> presents(max_possible_house, 0);
    for (int i = 1; i < max_possible_house; ++i) {
      int remaining_presents = 50;
      for (int j = i; j < max_possible_house; j += i) {
        presents[j] += i * 11;
        if (--remaining_presents == 0) {
          break;
        }
      }
    }
    for (int i = 1; i < max_possible_house; ++i) {
      if (presents[i] >= goal) {
        return std::to_string(i);
      }
    }
    throw cpptrace::runtime_error("no solution found");
  }
};

static bool day20_registered = register_solver<day20>(20);
