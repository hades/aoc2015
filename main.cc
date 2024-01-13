#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <vector>

#include <cpptrace/cpptrace.hpp>
#include <cxxopts.hpp>
#include <rang.hpp>
#include <spdlog/spdlog.h>
#include <zug/transducer/range.hpp>
#include <zug/into_vector.hpp>

#include "crash.h"
#include "requests.h"
#include "solvers.h"

std::vector<int> get_days_to_run(int day) {
  if (day < 0 || day > 25) {
    throw cpptrace::invalid_argument("--day must be between 1 and 25");
  }
  if (day == 0) {
    return zug::into_vector(zug::range(1, 26));
  }
  return {day};
}

std::string get_input(int day, const std::string& cookie) {
  using std::filesystem::path;
  using std::filesystem::is_regular_file;

  path input_file{std::format("day{:02d}.in", day)};
  if (is_regular_file(input_file)) {
    spdlog::debug("reading input from {}", input_file.string());
    std::stringstream str;
    str << (std::ifstream{input_file}).rdbuf();
    return str.str();
  }
  if (cookie.empty()) {
    throw cpptrace::invalid_argument("--cookie needs to be specified");
  }
  std::string url = "https://adventofcode.com/2015/day/" + std::to_string(day) + "/input";
  spdlog::info("fetching input from {}", url);
  auto resp = get(url, {.headers = {{"cookie", std::string("session=") + cookie}}});
  if (resp.status_code != 200) {
    spdlog::debug("response from the server: {}", resp.text);
    throw cpptrace::runtime_error(std::format("failed to fetch input: HTTP status code {}", resp.status_code));
  }
  return resp.text;
}

int main(int argc, char** argv) {
  cxxopts::Options options("aoc15", "Solver for Advent of Code 2015");
  options.add_options()
      ("d,day", "Day to run (all days by default)", cxxopts::value<int>()->default_value("0"))
      ("D,debug", "Enable debug output", cxxopts::value<bool>()->default_value("false"))
      ("s,submit", "Submit the solution to the AoC website", cxxopts::value<bool>()->default_value("false"))
      ("c,cookie", "Session cookie for the AoC website", cxxopts::value<std::string>()->default_value(""))
      ("2,second_only", "Only run the second part of the puzzle", cxxopts::value<bool>()->default_value("false"))
      ("e,evaluate", "Evaluate the solution", cxxopts::value<bool>()->default_value("false"))
      ("r,repeats_for_timing", "Number of times to run the solution for timing", cxxopts::value<int>()->default_value("3"));
  options.add_options("hidden")
      ("crash_handler_lifeboat_process", "Do not use: only used for signal handling");

  try {
    auto opts = options.parse(argc, argv);
    if (opts["debug"].as<bool>()) {
      spdlog::set_level(spdlog::level::debug);
    }
    if (opts["crash_handler_lifeboat_process"].as<bool>()) {
      crash_handler_lifeboat_process();
      return 0;
    }
    init_crash_handler();
    int day = opts["day"].as<int>();
    std::vector<int> days = get_days_to_run(day);
    for (int day: days) {
      spdlog::info("solving day {}", day);
      std::string input = get_input(day, opts["cookie"].as<std::string>());
      auto solver = solvers[day - 1]();
      spdlog::info("presolving day {}", day);
      solver->presolve(std::move(input));
      if (!opts["second_only"].as<bool>()) {
        spdlog::info("solving first part of day {}", day);
        std::string first = solver->solve_first();
        spdlog::info("first part of day {}: {}", day, first);
      }
      spdlog::info("solving second part of day {}", day);
      std::string second = solver->solve_second();
      spdlog::info("second part of day {}: {}", day, second);
    }
  } catch (const cxxopts::OptionException& e) {
    std::cout << options.help() << std::endl;
    std::cout << rang::style::bold << rang::fg::red << "Syntax error: " << e.what() << std::endl;
    std::cout << rang::fg::reset << rang::style::reset;
    return 1;
  } catch (const cpptrace::exception& e) {
    std::cout << rang::style::bold << rang::fg::red << "Error: " << e.message() << std::endl;
    std::cout << rang::fg::reset << rang::style::reset;
    e.trace().print(std::cout, cpptrace::isatty(cpptrace::stdout_fileno));
    return 1;
  } catch(const std::exception& e) {
    std::cout << rang::style::bold << rang::fg::red << "Error: " << e.what() << std::endl;
    std::cout << rang::fg::reset << rang::style::reset;
    return 1;
  }
}
