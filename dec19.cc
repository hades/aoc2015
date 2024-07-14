#include <queue>
#include <regex>
#include <set>
#include <utility>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>
#include <spdlog/spdlog.h>

#include "solvers.h"

struct earley_state {
  size_t rule;
  size_t dot;
  size_t start;
  size_t completions = 0;

  bool operator<(const earley_state& other) const {
    return std::tie(rule, dot, start) < std::tie(other.rule, other.dot, other.start);
  }

  bool operator==(const earley_state& other) const {
    return std::tie(rule, dot, start) == std::tie(other.rule, other.dot, other.start);
  }
};

std::string to_string(const earley_state& state, const std::vector<std::pair<std::string, std::string>>& rules) {
  return fmt::format("{} -> {} .{} s{} c{}", rules[state.rule].first, rules[state.rule].second, state.dot, state.start,
                     state.completions);
}

size_t earley_recognizer(const std::vector<std::pair<std::string, std::string>>& rules, const std::string& molecule) {
  std::vector<std::set<earley_state>> states(molecule.size() + 1);
  std::vector<std::deque<earley_state>> queues(molecule.size() + 1);
  for (size_t i = 0; i < rules.size(); ++i) {
    if (rules[i].first == "e") {
      queues[0].push_back({i, 0, 0});
    }
  }
  size_t min_completions = std::numeric_limits<size_t>::max();
  for (size_t i = 0; i <= molecule.size(); ++i) {
    spdlog::debug("i = {}", i);
    while (!queues[i].empty()) {
      earley_state state = queues[i].front();
      queues[i].pop_front();
      if (states[i].find(state) != states[i].end()) {
        continue;
      }
      states[i].insert(state);
      spdlog::debug("processing state ({})", to_string(state, rules));
      const auto& [from, to] = rules[state.rule];
      if (state.dot == to.size()) {
        if (i == molecule.size() && from == "e" && state.start == 0) {
          min_completions = std::min(min_completions, state.completions);
        }
        for (const auto& completable_state: states[state.start]) {
          std::string suffix = rules[completable_state.rule].second.substr(completable_state.dot);
          if (boost::starts_with(suffix, from)) {
            queues[i].push_back({completable_state.rule, completable_state.dot + from.size(), completable_state.start,
                                 state.completions + completable_state.completions + 1});
            spdlog::debug("          COMP-> ({})", to_string(queues[i].back(), rules));
          }
        }
        continue;
      }
      std::string suffix = to.substr(state.dot);
      for (size_t j = 0; j < rules.size(); ++j) {
        if (boost::starts_with(suffix, rules[j].first)) {
          queues[i].push_back({j, 0, i, 0});
          spdlog::debug("PRED          -> ({})", to_string(queues[i].back(), rules));
        }
      }
      if (suffix.size() > 0 && suffix[0] == molecule[i]) {
        queues[i + 1].push_back({state.rule, state.dot + 1, state.start, state.completions});
        spdlog::debug("     SCAN     -> ({})", to_string(queues[i + 1].back(), rules));
      }
    }
  }
  return min_completions + 1;
}

class day19: public solver {
  std::vector<std::pair<std::string, std::string>> rules;
  std::string molecule;

public:
  void presolve(std::string input) override {
    static const std::regex re(R"((\w+) => (\w+))");

    boost::trim_right(input);
    std::vector<std::string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));

    size_t i = 0;
    while (i < lines.size() && lines[i].size() > 0) {
      std::smatch match;
      if (!std::regex_match(lines[i], match, re)) {
        throw cpptrace::runtime_error("invalid input: " + lines[i]);
      }
      rules.emplace_back(match[1], match[2]);
      if (rules.back().first.size() > rules.back().second.size()) {
        throw cpptrace::runtime_error("invalid input (decreasing size): " + lines[i]);
      }
      ++i;
    }
    ++i;
    if (i >= lines.size()) {
      throw cpptrace::runtime_error("invalid input (missing starting molecule)");
    }
    molecule = lines[i];
  }

  std::string solve_first() override {
    std::set<std::string> results;
    for (const auto& [from, to]: rules) {
      size_t pos = 0;
      while ((pos = molecule.find(from, pos)) != std::string::npos) {
        std::string new_molecule = molecule;
        new_molecule.replace(pos, from.size(), to);
        results.insert(std::move(new_molecule));
        ++pos;
      }
    }
    return std::to_string(results.size());
  }

  std::string solve_second() override { return std::to_string(earley_recognizer(rules, molecule)); }
};

static bool day19_registered = register_solver<day19>(19);
