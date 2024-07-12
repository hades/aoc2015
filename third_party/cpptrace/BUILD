package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cpptrace",
    srcs = glob([
        "src/**/*.cpp",
        "src/**/*.hpp",
        "include/cpptrace/cpptrace.hpp",
        "include/ctrace/ctrace.h",
    ]),
    hdrs = [
        "include/cpptrace/cpptrace.hpp",
        "include/ctrace/ctrace.h",
    ],
    defines = [
        "CPPTRACE_DEMANGLE_WITH_CXXABI",
        "CPPTRACE_GET_SYMBOLS_WITH_LIBDWARF",
        "CPPTRACE_HAS_CXX_EXCEPTION_TYPE",
        "CPPTRACE_HAS_DLADDR1",
        "CPPTRACE_HAS_DL_FIND_OBJECT",
        "CPPTRACE_STATIC_DEFINE",
        "CPPTRACE_UNWIND_WITH_UNWIND",
        "NOMINMAX",
    ],
    includes = [
        "include",
    ],
    linkstatic = True,
    deps = [
        "//third_party/libdwarf-lite",
    ],
)

cc_test(
    name = "unittest",
    srcs = [
        "test/unit/object_trace.cpp",
        "test/unit/raw_trace.cpp",
        "test/unit/stacktrace.cpp",
    ],
    deps = [
        ":cpptrace",
        "@googletest//:gtest_main",
    ],
)
