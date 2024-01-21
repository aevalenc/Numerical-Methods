"""
BUILD file for direct solvers of the matrix solver namespace
"""

cc_library(
    name = "backwards_substitution",
    srcs = ["backwards_substitution.cpp"],
    hdrs = ["backwards_substitution.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "doolittle",
    srcs = ["doolittle.cpp"],
    hdrs = ["doolittle.h"],
    visibility = ["//visibility:public"],
    deps = ["//matrix_solvers:utilities"],
)

cc_library(
    name = "forward_substitution",
    srcs = ["forward_substitution.cpp"],
    hdrs = ["forward_substitution.h"],
    visibility = ["//visibility:public"],
)
