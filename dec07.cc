#include <map>
#include <regex>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

using term = std::variant<std::string, uint16_t>;

struct not_ {
  term a;
};

struct and_ {
  term a;
  term b;
};

struct or_ {
  term a;
  term b;
};

struct lshift {
  term a;
  term b;
};

struct rshift {
  term a;
  term b;
};

using expr = std::variant<term, not_, and_, or_, lshift, rshift>;

term make_term(const std::string& a) {
  if (std::isdigit(a[0]))
    return uint16_t(std::stoi(a));
  else
    return a;
}

class evaluator {
  std::unordered_map<std::string, uint16_t> computed_values;
  std::unordered_map<std::string, expr> expressions;

public:
  evaluator() = default;
  evaluator(std::vector<std::string>&& input) {
    for (const auto& line: input) {
      if (line.empty())
        continue;
      if (std::smatch m; std::regex_match(line, m, std::regex(R"((\w+) -> (\w+))"))) {
        expressions[m.str(2)] = make_term(m.str(1));
      } else if (std::smatch m; std::regex_match(line, m, std::regex(R"(NOT (\w+) -> (\w+))"))) {
        expressions[m.str(2)] = not_{make_term(m.str(1))};
      } else if (std::smatch m; std::regex_match(line, m, std::regex(R"((\w+) AND (\w+) -> (\w+))"))) {
        expressions[m.str(3)] = and_{make_term(m.str(1)), make_term(m.str(2))};
      } else if (std::smatch m; std::regex_match(line, m, std::regex(R"((\w+) OR (\w+) -> (\w+))"))) {
        expressions[m.str(3)] = or_{make_term(m.str(1)), make_term(m.str(2))};
      } else if (std::smatch m; std::regex_match(line, m, std::regex(R"((\w+) LSHIFT (\w+) -> (\w+))"))) {
        expressions[m.str(3)] = lshift{make_term(m.str(1)), make_term(m.str(2))};
      } else if (std::smatch m; std::regex_match(line, m, std::regex(R"((\w+) RSHIFT (\w+) -> (\w+))"))) {
        expressions[m.str(3)] = rshift{make_term(m.str(1)), make_term(m.str(2))};
      } else {
        throw cpptrace::runtime_error(std::format("invalid input: {}", line));
      }
    }
  }

  void add_expression(std::string&& name, expr&& e) {
    expressions[name] = e;
    computed_values.clear();
  }

  uint16_t evaluate(uint16_t a) { return a; }

  uint16_t evaluate(const not_& a) { return ~evaluate(a.a); }

  uint16_t evaluate(const and_& a) { return evaluate(a.a) & evaluate(a.b); }

  uint16_t evaluate(const or_& a) { return evaluate(a.a) | evaluate(a.b); }

  uint16_t evaluate(const lshift& a) { return evaluate(a.a) << evaluate(a.b); }

  uint16_t evaluate(const rshift& a) { return evaluate(a.a) >> evaluate(a.b); }

  uint16_t evaluate(const std::string& a) {
    if (auto it = computed_values.find(a); it != computed_values.end())
      return it->second;
    uint16_t result = evaluate(expressions[a]);
    computed_values[a] = result;
    return result;
  }

  uint16_t evaluate(const term& a) {
    return std::visit([this](auto&& arg) { return evaluate(arg); }, a);
  }

  uint16_t evaluate(const expr& a) {
    return std::visit([this](auto&& arg) { return evaluate(arg); }, a);
  }
};

class day07: public solver {
  evaluator e;

public:
  void presolve(std::string input) override {
    std::vector<std::string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));
    e = evaluator(std::move(lines));
  }
  std::string solve_first() override { return std::to_string(e.evaluate(std::string("a"))); }
  std::string solve_second() override {
    uint16_t new_b = e.evaluate(std::string("a"));
    e.add_expression("b", uint16_t(new_b));
    return std::to_string(e.evaluate(std::string("a")));
  }
};

static bool day07_registered = register_solver<day07>(7);
