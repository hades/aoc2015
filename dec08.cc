#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

class day08: public solver {
  std::vector<std::string> input;

public:
  void presolve(std::string input) override { boost::split(this->input, input, boost::is_any_of("\n")); }
  std::string solve_first() override {
    int overhead = 0;
    for (const auto& line: input) {
      if (line.empty())
        continue;
      overhead += 2;
      for (size_t i = 1; i < line.size() - 1; ++i) {
        if (line[i] == '\\') {
          if (line[i + 1] == '\\' || line[i + 1] == '"') {
            ++i;
            ++overhead;
          } else if (line[i + 1] == 'x') {
            i += 3;
            overhead += 3;
          } else {
            throw cpptrace::runtime_error(std::format("invalid input: {}", line));
          }
        }
      }
    }
    return std::to_string(overhead);
  }
  std::string solve_second() override {
    int overhead = 0;
    for (const auto& line: input) {
      if (line.empty())
        continue;
      overhead += 2;
      for (const char ch: line) {
        if (ch == '\\' || ch == '"')
          ++overhead;
      }
    }
    return std::to_string(overhead);
  }
};

static bool day08_registered = register_solver<day08>(8);
