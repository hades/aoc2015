#include <memory>
#include <functional>
#include <string>

#include <cpptrace/cpptrace.hpp>

class solver {
public:
  virtual void presolve(std::string input) = 0;
  virtual std::string solve_first() = 0;
  virtual std::string solve_second() = 0;
  virtual ~solver() = default;
};

class unimplemented_solver: public solver {
  int day;
public:
  unimplemented_solver(int day): day(day) {}
  void presolve(std::string) override {}
  std::string solve_first() override { throw cpptrace::runtime_error(std::format("solver for day {} not implemented", day)); }
  std::string solve_second() override { throw cpptrace::runtime_error(std::format("solver for day {} not implemented", day)); }
};

inline std::array<std::function<std::unique_ptr<solver>()>, 25> solvers{
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(1); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(2); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(3); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(4); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(5); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(6); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(7); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(8); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(9); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(10); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(11); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(12); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(13); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(14); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(15); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(16); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(17); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(18); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(19); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(20); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(21); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(22); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(23); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(24); },
  []() -> std::unique_ptr<solver> { return std::make_unique<unimplemented_solver>(25); },
};

template<class solver_type>
bool register_solver(int day) {
  solvers[day - 1] = []() -> std::unique_ptr<solver> { return std::make_unique<solver_type>(); };
  return true;
}