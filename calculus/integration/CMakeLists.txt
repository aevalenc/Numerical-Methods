# CMakeLists.txt for the integration module
# This file is part of the Calculus library.

add_library(trapezoidal_method
    trapezoidal_method/trapezoidal_method.cpp
)

target_include_directories(trapezoidal_method PUBLIC
    ${CMAKE_SOURCE_DIR}
)

add_executable(
    quadrature_methods_tests
    test/quadrature_methods_tests.cpp
)

target_include_directories(
    quadrature_methods_tests
    PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    quadrature_methods_tests
    PUBLIC
    trapezoidal_method
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(quadrature_methods_tests)
