#include <ranges>
#include <string>
#include <thread>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <cpptrace/cpptrace.hpp>
#include <cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <md5.h>

#include "solvers.h"

constexpr int PARALLELISM = 12;

class day04: public solver {
  std::string input;
  std::vector<std::optional<int>> results;

  void solver_thread(int thread_id, int start, int step, bool six_zeroes) {
    for (int i = 0;; ++i) {
      int value = start + step * i;
      if (i % 1000 == 0) {
        for (const auto& result: results) {
          if (result && *result < value) {
            return;
          }
        }
      }
      std::string str_value = input + std::to_string(value);
      CryptoPP::Weak::MD5 md5;
      md5.Update((const CryptoPP::byte*)str_value.data(), str_value.size());
      std::vector<CryptoPP::byte> digest;
      digest.resize(md5.DigestSize());
      md5.Final(&digest[0]);
      if (digest[0] == 0 && digest[1] == 0 && (six_zeroes ? digest[2] == 0 : digest[2] < 0x10)) {
        results[thread_id] = value;
        return;
      }
    }
  }
  std::string solve(bool six_zeroes) {
    std::vector<std::thread> threads;
    results.resize(0);
    results.resize(PARALLELISM);
    for (int i = 0; i < PARALLELISM; ++i) {
      threads.emplace_back([this, i, six_zeroes]() { solver_thread(i, i, PARALLELISM, six_zeroes); });
    }
    for (auto& thread: threads) {
      thread.join();
    }
    int min = std::ranges::min(std::views::filter(results, [](const auto& result) { return result.has_value(); }) |
                               std::views::transform([](const auto& result) { return *result; }));
    return std::to_string(min);
  }

public:
  void presolve(std::string input) override {
    this->input = input;
    boost::trim_right(this->input);
  }
  std::string solve_first() override { return solve(false); }
  std::string solve_second() override { return solve(true); }
};

static bool day04_registered = register_solver<day04>(4);
