package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libdwarf-lite",
    srcs = glob([
        "src/lib/libdwarf/*.c",
        "src/lib/libdwarf/*.h",
    ]),
    hdrs = glob([
        "src/lib/libdwarf/*.h",
    ]),
    defines = [
        "LIBDWARF_STATIC",
    ],
    includes = [
        "src/lib/libdwarf",
    ],
    linkstatic = True,
    deps = [
        "@zlib",
        "@zstd",
    ],
)
