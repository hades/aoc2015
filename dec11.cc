#include <ranges>
#include <regex>
#include <set>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

void increment(std::string& s) {
  for (std::string::iterator it = s.end() - 1;; --it) {
    if (it == s.begin() || *it != 'z') {
      ++*it;
      return;
    }
    *it = 'a';
  }
}

bool check(const std::string& s) {
  int straight_length = 0;
  std::set<char> pair_chars;
  for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
    if (*it == 'i' || *it == 'o' || *it == 'l') {
      return false;
    }
    if (it != s.begin() && *it == *(it - 1)) {
      pair_chars.insert(*it);
    }
    if (straight_length < 2) {
      if (it != s.begin() && *it == *(it - 1) + 1) {
        ++straight_length;
      } else {
        straight_length = 0;
      }
    }
  }
  if (straight_length == 2 && pair_chars.size() >= 2) {
    return true;
  }
  return false;
}

class day11: public solver {
  std::string input;

public:
  void presolve(std::string input) override {
    this->input = input;
    boost::trim_right(this->input);
  }
  std::string solve_first() override {
    std::string result = input;
    do {
      increment(result);
    } while (!check(result));
    return result;
  }
  std::string solve_second() override {
    std::string result = input;
    do {
      increment(result);
    } while (!check(result));
    do {
      increment(result);
    } while (!check(result));
    return result;
  }
};

static bool day11_registered = register_solver<day11>(11);
