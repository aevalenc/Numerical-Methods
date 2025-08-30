# Matrix Solver CMakeLists.txt

add_library(utilities STATIC utilities.cpp)
target_include_directories(utilities PUBLIC
    ${CMAKE_SOURCE_DIR}
)

add_library(operations STATIC operations/operations.cpp)
target_include_directories(operations PUBLIC
    ${CMAKE_SOURCE_DIR}
)

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

add_library(
    iterative_solvers
    STATIC
    iterative_solvers/conjugate_gradient.cpp
    iterative_solvers/jacobi.cpp
    iterative_solvers/gauss_seidel.cpp
    iterative_solvers/jacobi.cpp
)

target_include_directories(
    iterative_solvers 
    PUBLIC
    operations 
    utilities 
    ${CMAKE_SOURCE_DIR}
)

add_executable(
    utilities_tests
    utilities_tests.cpp
)
target_include_directories(
    utilities_tests 
    PUBLIC
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(
    utilities_tests 
    PUBLIC
    utilities
    GTest::gtest_main
)

add_executable(
    direct_solvers_tests
    direct_solvers/test/direct_solvers_tests.cpp
)

target_include_directories(
    direct_solvers_tests 
    PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    direct_solvers_tests
    PUBLIC
    direct_solvers
    utilities
    operations
    GTest::gtest_main
)

add_executable(
        iterative_solvers_tests
        iterative_solvers/test/iterative_solver_tests.cpp
)

target_include_directories(
    iterative_solvers_tests 
    PUBLIC
    operations
    utilities
    iterative_solvers
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    iterative_solvers_tests
    PUBLIC
    iterative_solvers
    operations
    utilities
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utilities_tests)
gtest_discover_tests(direct_solvers_tests)
gtest_discover_tests(iterative_solvers_tests)
