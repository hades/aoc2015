#include <boost/algorithm/string.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "solvers.h"

void step(boost::numeric::ublas::matrix<bool>& grid) {
  auto new_grid = grid;
  for (size_t i = 0; i < grid.size1(); i++) {
    for (size_t j = 0; j < grid.size2(); j++) {
      int neighbors = 0;
      for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
          if (x == 0 && y == 0)
            continue;
          if (i + x < 0 || i + x >= grid.size1())
            continue;
          if (j + y < 0 || j + y >= grid.size2())
            continue;
          if (grid(i + x, j + y)) {
            neighbors++;
          }
        }
      }
      if (grid(i, j)) {
        new_grid(i, j) = neighbors == 2 || neighbors == 3;
      } else {
        new_grid(i, j) = neighbors == 3;
      }
    }
  }
  grid = new_grid;
}

int count(const boost::numeric::ublas::matrix<bool>& grid) {
  int result = 0;
  for (size_t i = 0; i < grid.size1(); i++) {
    for (size_t j = 0; j < grid.size2(); j++) {
      if (grid(i, j)) {
        result++;
      }
    }
  }
  return result;
}

class day18: public solver {
  boost::numeric::ublas::matrix<bool> grid;

public:
  void presolve(std::string input) override {
    boost::trim_right(input);
    std::vector<std::string> lines;
    boost::split(lines, input, boost::is_any_of("\n"));
    grid = boost::numeric::ublas::matrix<bool>(lines.size(), lines.front().size());
    for (size_t i = 0; i < lines.size(); i++) {
      for (size_t j = 0; j < lines.front().size(); j++) {
        grid(i, j) = lines[i][j] == '#';
      }
    }
  }
  std::string solve_first() override {
    auto grid = this->grid;
    for (size_t i = 0; i < 100; ++i) {
      step(grid);
    }
    return std::to_string(count(grid));
  }
  std::string solve_second() override {
    auto grid = this->grid;
    for (size_t i = 0; i < 100; ++i) {
      grid(0, 0) = true;
      grid(0, grid.size2() - 1) = true;
      grid(grid.size1() - 1, 0) = true;
      grid(grid.size1() - 1, grid.size2() - 1) = true;
      step(grid);
    }
    grid(0, 0) = true;
    grid(0, grid.size2() - 1) = true;
    grid(grid.size1() - 1, 0) = true;
    grid(grid.size1() - 1, grid.size2() - 1) = true;
    return std::to_string(count(grid));
  }
};

static bool day18_registered = register_solver<day18>(18);
