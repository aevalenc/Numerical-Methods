"""
BUILD file for iterative linear solvers
"""

cc_library(
    name = "jacobi_method",
    srcs = ["jacobi.cpp"],
    hdrs = ["jacobi.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "gauss_seidel_method",
    srcs = ["gauss_seidel.cpp"],
    hdrs = ["gauss_seidel.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "conjugate_gradient_method",
    srcs = ["conjugate_gradient.cpp"],
    hdrs = ["conjugate_gradient.h"],
    defines = select({
        "//:print_debug_info": ["PRINT_DEBUG"],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:public"],
    deps = ["//matrix_solvers:utilities"],
)
