#include <ranges>
#include <regex>
#include <set>

#include <boost/algorithm/string.hpp>
#include <cpptrace/cpptrace.hpp>

#include "solvers.h"

struct travelling_salesman {
  static int init() { return std::numeric_limits<int>::max(); }
  static int reduce(int a, int b) { return std::min(a, b); }
};

struct travelling_salesman_max {
  static int init() { return std::numeric_limits<int>::min(); }
  static int reduce(int a, int b) { return std::max(a, b); }
};

template <class P>
int travelling_salesman_recursive_generic(const std::vector<std::vector<int>>& distances, std::set<size_t> unvisited,
                                          std::optional<size_t> current = std::nullopt) {
  if (unvisited.empty())
    return 0;
  int min_distance = P::init();
  for (const auto& next: unvisited) {
    std::set<size_t> next_unvisited = unvisited;
    next_unvisited.erase(next);
    int next_hop = current ? distances[*current][next] : 0;
    min_distance =
        P::reduce(min_distance, next_hop + travelling_salesman_recursive_generic<P>(distances, next_unvisited, next));
  }
  return min_distance;
}

class day09: public solver {
  std::vector<std::vector<int>> distances;

public:
  void presolve(std::string input) override {
    std::vector<std::string> lines;
    std::vector<std::tuple<std::string, std::string, int>> distances;
    std::set<std::string> cities;
    boost::split(lines, input, boost::is_any_of("\n"));
    for (const auto& line: lines) {
      if (line.empty())
        continue;
      std::smatch m;
      if (!std::regex_match(line, m, std::regex(R"((\w+) to (\w+) = (\d+))")))
        throw cpptrace::runtime_error(std::format("invalid input: {}", line));
      distances.emplace_back(m[1], m[2], std::stoi(m[3]));
      cities.insert(m[1]);
      cities.insert(m[2]);
    }
    std::vector<std::string> cities_vec(cities.begin(), cities.end());
    this->distances.resize(cities.size(), std::vector<int>(cities.size(), 0));
    for (const auto& [from, to, distance]: distances) {
      size_t from_id = std::distance(cities_vec.begin(), std::find(cities_vec.begin(), cities_vec.end(), from));
      size_t to_id = std::distance(cities_vec.begin(), std::find(cities_vec.begin(), cities_vec.end(), to));
      this->distances[from_id][to_id] = distance;
      this->distances[to_id][from_id] = distance;
    }
  }
  std::string solve_first() override {
    std::set<size_t> unvisited = std::views::iota(size_t{0}, distances.size()) | std::ranges::to<std::set>();
    return std::to_string(travelling_salesman_recursive_generic<travelling_salesman>(distances, unvisited));
  }
  std::string solve_second() override {
    std::set<size_t> unvisited = std::views::iota(size_t{0}, distances.size()) | std::ranges::to<std::set>();
    return std::to_string(travelling_salesman_recursive_generic<travelling_salesman_max>(distances, unvisited));
  }
};

static bool day09_registered = register_solver<day09>(9);
