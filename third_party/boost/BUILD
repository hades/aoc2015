package(default_visibility = ["//visibility:public"])

cc_library(
    name = "boost",
    srcs = glob(
        [
            "libs/container/src/**/*.cpp",
            "libs/container/src/**/*.inc",
            "libs/json/src/**/*.cpp",
            "libs/url/src/**/*.cpp",
            "libs/url/src/**/*.hpp",
            "boost/**/*.ipp",
        ],
        exclude = [
        ],
    ),
    hdrs = glob(
        [
            "boost/**/*.h",
            "boost/**/*.hpp",
        ],
        exclude = [
            "boost/test/**/*.hpp",
        ],
    ),
    copts = [
        "-fvisibility-inlines-hidden",
        "-fvisibility=hidden",
    ],
    defines = [
        "BOOST_ALL_NO_LIB=1",
        "BOOST_COBALT_USE_STD_PMR=1",
        "NDEBUG",
    ],
    includes = [
        ".",
    ],
    linkstatic = True,
)

cc_library(
    name = "boost_test",
    srcs = glob(
        [
            "libs/test/src/**/*.cpp",
            "libs/test/src/**/*.hpp",
            "boost/**/*.hpp",
            "boost/**/*.ipp",
        ],
        exclude = [
            "libs/test/src/cpp_main.cpp",
        ],
    ),
    hdrs = glob([
        "boost/test/**/*.hpp",
        "boost/test/**/*.ipp",
    ]),
    copts = [
        "-fvisibility-inlines-hidden",
        "-fvisibility=hidden",
    ],
    defines = [
        "BOOST_ALL_NO_LIB=1",
        "BOOST_COBALT_USE_STD_PMR=1",
        "NDEBUG",
    ],
    includes = [
        ".",
    ],
    linkstatic = True,
)
