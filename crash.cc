#include <signal.h>
#include <sys/wait.h>

#include <iostream>

#include <cpptrace/cpptrace.hpp>

#include "crash.h"

void crash_handler_lifeboat_process() {
  int sig;
  fread(&sig, sizeof(int), 1, stdin);
  std::cerr << "[LIFEBOAT] caught signal: " << sigdescr_np(sig) << std::endl;
  cpptrace::object_trace trace;
  for (;;) {
    cpptrace::safe_object_frame frame;
    std::size_t f_size = fread(&frame, sizeof(frame), 1, stdin);
    if (f_size == 0)
      break;
    if (f_size != 1) {
      std::cerr << "[LIFEBOAT] failed to read frame" << std::endl;
      std::cerr << "error: " << strerror(errno) << std::endl;
      break;
    }
    trace.frames.push_back(frame.resolve());
  }
  trace.resolve().print(std::cerr);
}

void crash_handler(int sig) {
  constexpr std::size_t MAX_STACK_TRACE_SIZE = 100;
  cpptrace::frame_ptr buffer[MAX_STACK_TRACE_SIZE];
  std::size_t st_size = cpptrace::safe_generate_raw_trace(buffer, MAX_STACK_TRACE_SIZE);
  int pipefd[2];
  pipe(pipefd);
  const pid_t my_pid = fork();
  if (my_pid == -1) {
    write(STDERR_FILENO, "failed to fork\n", 15);
    _exit(1);
  }
  if (my_pid == 0) {
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    execl("/proc/self/exe", "/proc/self/exe", "--crash_handler_lifeboat_process", nullptr);
    _exit(1);
  }
  write(pipefd[1], &sig, sizeof(int));
  for (std::size_t i = 0; i < st_size; ++i) {
    cpptrace::safe_object_frame frame;
    cpptrace::get_safe_object_frame(buffer[i], &frame);
    write(pipefd[1], &frame, sizeof(frame));
  }
  close(pipefd[0]);
  close(pipefd[1]);
  waitpid(my_pid, nullptr, 0);
  _exit(1);
}

void warmup_cpptrace() {
  constexpr std::size_t MAX_STACK_TRACE_SIZE = 100;
  cpptrace::frame_ptr buffer[MAX_STACK_TRACE_SIZE];
  cpptrace::safe_generate_raw_trace(buffer, MAX_STACK_TRACE_SIZE);
  cpptrace::safe_object_frame frame;
  cpptrace::get_safe_object_frame(buffer[0], &frame);
}

void init_crash_handler() {
  warmup_cpptrace();
  struct sigaction action {};
  action.sa_handler = &crash_handler;
  action.sa_flags = SA_RESETHAND;
  sigemptyset(&action.sa_mask);
  sigaddset(&action.sa_mask, SIGABRT);
  sigaddset(&action.sa_mask, SIGFPE);
  sigaddset(&action.sa_mask, SIGILL);
  sigaddset(&action.sa_mask, SIGSEGV);

  sigaction(SIGABRT, &action, nullptr);
  sigaction(SIGFPE, &action, nullptr);
  sigaction(SIGILL, &action, nullptr);
  sigaction(SIGSEGV, &action, nullptr);
}
