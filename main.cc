#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

#include <cpptrace/cpptrace.hpp>
#include <cxxopts.hpp>
#include <rang.hpp>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>
#include <zug/into_vector.hpp>
#include <zug/transducer/range.hpp>

#include "crash.h"
#include "requests.h"
#include "solvers.h"

constexpr const char SUBMISSIONS_FILE[] = "submissions.yaml";

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
  using std::filesystem::is_regular_file;
  using std::filesystem::path;

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

enum class submit_result {
  accepted,
  rejected_too_high,
  rejected_too_low,
  rejected,
};

YAML::Node read_prior_submissions(int day, int part) {
  using std::filesystem::is_regular_file;
  using std::filesystem::path;

  path submissions_file{SUBMISSIONS_FILE};
  if (!is_regular_file(submissions_file)) {
    return {};
  }
  spdlog::debug("reading prior submissions from {}", submissions_file.string());
  auto file = YAML::LoadFile(submissions_file.string());
  return file["submissions"][std::format("dec{:02d}_p{}", day, part)];
}

void write_prior_submission(int day, int part, const std::string& answer, submit_result result) {
  using std::filesystem::is_regular_file;
  using std::filesystem::path;

  path submissions_file{SUBMISSIONS_FILE};
  YAML::Node file;
  if (is_regular_file(submissions_file)) {
    file = YAML::LoadFile(submissions_file.string());
  }
  YAML::Node node = file["submissions"][std::format("dec{:02d}_p{}", day, part)];
  if (result == submit_result::accepted) {
    node["accepted"] = answer;
  } else if (result == submit_result::rejected_too_high) {
    if (!node["upper_bound"] || std::stoi(answer) < node["upper_bound"].as<int>()) {
      node["upper_bound"] = answer;
    }
  } else if (result == submit_result::rejected_too_low) {
    if (!node["lower_bound"] || std::stoi(answer) > node["lower_bound"].as<int>()) {
      node["lower_bound"] = answer;
    }
  } else {
    node["rejected"].push_back(answer);
  }
  std::ofstream output(SUBMISSIONS_FILE);
  YAML::Emitter emitter(output);
  emitter.SetIndent(2);
  emitter << YAML::Comment("This file is automatically generated by aoc15");
  emitter << YAML::Newline;
  emitter << YAML::Comment("It contains the results of the previous submissions");
  emitter << YAML::Newline;
  emitter << file;
  emitter << YAML::Newline;
}

submit_result submit_send(int day, int part, const std::string& answer, const std::string& cookie) {
  std::string url = std::format("https://adventofcode.com/2015/day/{}/answer", day);
  std::multimap<std::string, std::string> data = {
      {"level", std::to_string(part)},
      {"answer", answer},
  };
  auto resp = post(url, {.headers = {{"cookie", std::string("session=") + cookie}}}, data);
  if (resp.status_code != 200) {
    spdlog::debug("response from the server: {}", resp.text);
    throw cpptrace::runtime_error(std::format("failed to submit answer: HTTP status code {}", resp.status_code));
  }
  if (resp.text.find("You gave an answer too recently") != std::string::npos) {
    std::smatch match;
    if (!std::regex_search(resp.text, match, std::regex(R"(You have (?:(\d+)m )?(\d+)s left to wait)"))) {
      throw cpptrace::runtime_error("failed to parse remaining time to wait");
    }
    int seconds = std::stoi(match[2]) + 60 * (match[1].length() ? std::stoi(match[1]) : 0);
    spdlog::info("waiting {} seconds before submitting again", seconds);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    return submit_send(day, part, answer, cookie);
  }
  if (resp.text.find("That's the right answer") != std::string::npos) {
    return submit_result::accepted;
  } else if (resp.text.find("your answer is too high") != std::string::npos) {
    return submit_result::rejected_too_high;
  } else if (resp.text.find("your answer is too low") != std::string::npos) {
    return submit_result::rejected_too_low;
  } else {
    return submit_result::rejected;
  }
}

submit_result submit(int day, int part, const std::string& answer, const std::string& cookie) {
  auto prior_submissions = read_prior_submissions(day, part);
  if (prior_submissions["accepted"]) {
    spdlog::debug("not submitting answer, an accepted answer has already been submitted");
    return prior_submissions["accepted"].as<std::string>() == answer ? submit_result::accepted
                                                                     : submit_result::rejected;
  }
  if (prior_submissions["rejected"]) {
    spdlog::debug("not submitting answer, this answer has already been rejected");
    auto rejected_answers = prior_submissions["rejected"].as<std::vector<std::string>>();
    if (std::ranges::find(rejected_answers, answer) != rejected_answers.end()) {
      return submit_result::rejected;
    }
  }
  if (prior_submissions["upper_bound"] && std::stoi(answer) >= prior_submissions["upper_bound"].as<int>()) {
    spdlog::debug("not submitting answer, this answer is too high");
    return submit_result::rejected_too_high;
  }
  if (prior_submissions["lower_bound"] && std::stoi(answer) <= prior_submissions["lower_bound"].as<int>()) {
    spdlog::debug("not submitting answer, this answer is too low");
    return submit_result::rejected_too_low;
  }
  submit_result result = submit_send(day, part, answer, cookie);
  write_prior_submission(day, part, answer, result);
  return result;
}

void log_result(submit_result result) {
  switch (result) {
  case submit_result::accepted:
    spdlog::info("answer accepted");
    break;
  case submit_result::rejected_too_high:
    spdlog::info("answer rejected: too high");
    break;
  case submit_result::rejected_too_low:
    spdlog::info("answer rejected: too low");
    break;
  case submit_result::rejected:
    spdlog::info("answer rejected");
    break;
  }
}

int main(int argc, char** argv) {
  cxxopts::Options options("aoc15", "Solver for Advent of Code 2015");
  options.add_options()("d,day", "Day to run (all days by default)", cxxopts::value<int>()->default_value("0"))(
      "D,debug", "Enable debug output", cxxopts::value<bool>()->default_value("false"))(
      "s,submit", "Submit the solution to the AoC website", cxxopts::value<bool>()->default_value("false"))(
      "c,cookie", "Session cookie for the AoC website", cxxopts::value<std::string>()->default_value(""))(
      "2,second_only", "Only run the second part of the puzzle", cxxopts::value<bool>()->default_value("false"))(
      "e,evaluate", "Evaluate the solution", cxxopts::value<bool>()->default_value("false"))(
      "r,repeats_for_timing", "Number of times to run the solution for timing",
      cxxopts::value<int>()->default_value("3"));
  options.add_options("hidden")("crash_handler_lifeboat_process", "Do not use: only used for signal handling");

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
        if (opts["submit"].as<bool>()) {
          spdlog::info("submitting first part of day {}", day);
          log_result(submit(day, 1, first, opts["cookie"].as<std::string>()));
        }
      }
      spdlog::info("solving second part of day {}", day);
      std::string second = solver->solve_second();
      spdlog::info("second part of day {}: {}", day, second);
      if (opts["submit"].as<bool>()) {
        spdlog::info("submitting second part of day {}", day);
        log_result(submit(day, 2, second, opts["cookie"].as<std::string>()));
      }
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
  } catch (const std::exception& e) {
    std::cout << rang::style::bold << rang::fg::red << "Error: " << e.what() << std::endl;
    std::cout << rang::fg::reset << rang::style::reset;
    return 1;
  }
}
