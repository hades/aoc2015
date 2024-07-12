package(default_visibility = ["//visibility:public"])

cc_library(
    name = "z3",
    srcs = glob(
        [
            "src/**/*.h",
            "src/**/*.hpp",
            "src/**/*.cpp",
        ],
        exclude = [
            "src/shell/**/*",
            "src/test/**/*",
        ],
    ),
    hdrs = [
        "src/api/c++/z3++.h",
        "src/api/z3.h",
        "src/api/z3_algebraic.h",
        "src/api/z3_api.h",
        "src/api/z3_ast_containers.h",
        "src/api/z3_fixedpoint.h",
        "src/api/z3_fpa.h",
        "src/api/z3_macros.h",
        "src/api/z3_optimization.h",
        "src/api/z3_polynomial.h",
        "src/api/z3_rcf.h",
        "src/api/z3_spacer.h",
        "src/api/z3_v1.h",
    ],
    copts = [
        "-Ithird_party/z3/src",
    ],
    defines = [
        "_MP_INTERNAL",
    ],
    includes = [
        "src/api",
        "src/api/c++",
    ],
    linkstatic = True,
)
