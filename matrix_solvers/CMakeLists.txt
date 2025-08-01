# Matrix Solver CMakeLists.txt

add_library(
    direct_solvers
    STATIC
    direct_solvers/backwards_substitution.cpp
    direct_solvers/doolittle.cpp
    direct_solvers/forward_substitution.cpp
    direct_solvers/lu_solve.cpp
)

target_include_directories(direct_solvers PUBLIC
    ${CMAKE_SOURCE_DIR}
)

add_executable(
    direct_solvers_tests
    direct_solvers/test/direct_solvers_tests.cpp
)

target_include_directories(direct_solvers_tests PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    direct_solvers_tests
    PUBLIC
    direct_solvers
    GTest::gtest_main
)

# set_tests_properties(direct_solvers_tests PROPERTIES LABELS "direct_solvers")


include(GoogleTest)
gtest_discover_tests(
    direct_solvers_tests
    DISCOVERY_MODE PRE_TEST
    DISCOVERY_TEST_PREFIX "DirectSolvers::"
)
