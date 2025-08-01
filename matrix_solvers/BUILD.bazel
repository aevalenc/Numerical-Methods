cc_library(
    name = "utilities",
    srcs = ["utilities.cpp"],
    hdrs = ["utilities.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "utilities_tests",
    srcs = ["utilities_tests.cpp"],
    deps = [
        ":utilities",
        "@com_google_googletest//:gtest_main",
    ],
)
