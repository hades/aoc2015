cc_library(
    name = "solvers",
    hdrs = ["solvers.h"],
    deps = [
        "//third_party/cpptrace",
    ],
)

cc_library(
    name = "z3_util",
    hdrs = ["z3_util.h"],
    deps = [
        "//third_party/z3",
    ],
)

cc_library(
    name = "crash",
    srcs = ["crash.cc"],
    hdrs = ["crash.h"],
    deps = [
        "//third_party/cpptrace",
    ],
)

cc_library(
    name = "requests",
    srcs = ["requests.cc"],
    hdrs = ["requests.h"],
    deps = [
        "//third_party/boost",
        "//third_party/spdlog",
        "//third_party/zug",
    ],
)

cc_library(
    name = "dec01",
    srcs = ["dec01.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec01_test",
    srcs = ["dec01_test.cc"],
    deps = [
        ":dec01",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec02",
    srcs = ["dec02.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec02_test",
    srcs = ["dec02_test.cc"],
    deps = [
        ":dec02",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec03",
    srcs = ["dec03.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec03_test",
    srcs = ["dec03_test.cc"],
    deps = [
        ":dec03",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec04",
    srcs = ["dec04.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cryptopp",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec04_test",
    srcs = ["dec04_test.cc"],
    deps = [
        ":dec04",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec05",
    srcs = ["dec05.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec05_test",
    srcs = ["dec05_test.cc"],
    deps = [
        ":dec05",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec06",
    srcs = ["dec06.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec06_test",
    srcs = ["dec06_test.cc"],
    deps = [
        ":dec06",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec07",
    srcs = ["dec07.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec07_test",
    srcs = ["dec07_test.cc"],
    deps = [
        ":dec07",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec08",
    srcs = ["dec08.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec08_test",
    srcs = ["dec08_test.cc"],
    deps = [
        ":dec08",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec09",
    srcs = ["dec09.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec09_test",
    srcs = ["dec09_test.cc"],
    deps = [
        ":dec09",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec10",
    srcs = ["dec10.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec10_test",
    srcs = ["dec10_test.cc"],
    deps = [
        ":dec10",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec11",
    srcs = ["dec11.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec11_test",
    srcs = ["dec11_test.cc"],
    deps = [
        ":dec11",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec12",
    srcs = ["dec12.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec12_test",
    srcs = ["dec12_test.cc"],
    deps = [
        ":dec12",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec13",
    srcs = ["dec13.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        ":z3_util",
        "//third_party/boost",
        "//third_party/z3",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec13_test",
    srcs = ["dec13_test.cc"],
    deps = [
        ":dec13",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec14",
    srcs = ["dec14.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec14_test",
    srcs = ["dec14_test.cc"],
    deps = [
        ":dec14",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec15",
    srcs = ["dec15.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec15_test",
    srcs = ["dec15_test.cc"],
    deps = [
        ":dec15",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec16",
    srcs = ["dec16.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec16_test",
    srcs = ["dec16_test.cc"],
    deps = [
        ":dec16",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec17",
    srcs = ["dec17.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec17_test",
    srcs = ["dec17_test.cc"],
    deps = [
        ":dec17",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec18",
    srcs = ["dec18.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec18_test",
    srcs = ["dec18_test.cc"],
    deps = [
        ":dec18",
        "//third_party/boost:boost_test",
    ],
)

cc_library(
    name = "dec19",
    srcs = ["dec19.cc"],
    linkstatic = True,
    deps = [
        ":solvers",
        "//third_party/boost",
        "//third_party/cpptrace",
        "//third_party/spdlog",
        "@fmt",
    ],
    alwayslink = True,
)

cc_test(
    name = "dec19_test",
    srcs = ["dec19_test.cc"],
    deps = [
        ":dec19",
        "//third_party/boost:boost_test",
        "//third_party/spdlog",
    ],
)

cc_binary(
    name = "aoc15",
    srcs = ["main.cc"],
    deps = [
        ":crash",
        ":dec01",
        ":dec02",
        ":dec03",
        ":dec04",
        ":dec05",
        ":dec06",
        ":dec07",
        ":dec08",
        ":dec09",
        ":dec10",
        ":dec11",
        ":dec12",
        ":dec13",
        ":dec14",
        ":dec15",
        ":dec16",
        ":dec17",
        ":dec18",
        ":dec19",
        ":requests",
        "//third_party/cxxopts",
        "//third_party/rang",
        "//third_party/spdlog",
        "//third_party/zug",
        "@yaml-cpp",
    ],
)
