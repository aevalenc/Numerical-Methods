cc_test(
    name = "direct_solver_tests",
    srcs = ["direct_solver_tests.cpp"],
    deps = [
        "//matrix_solvers/direct_solvers:backwards_substitution",
        "//matrix_solvers/direct_solvers:doolittle",
        "//matrix_solvers/direct_solvers:forward_substitution",
        "//matrix_solvers/direct_solvers:lu_solve",
        "@com_google_googletest//:gtest_main",
    ],
)
