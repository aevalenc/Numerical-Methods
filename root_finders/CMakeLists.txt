# CMakeLists.txt for RootFinders library

add_library(
  RootFindersLib
  STATIC
  newtons_method.cpp
)

target_include_directories(RootFindersLib PUBLIC
    ${CMAKE_SOURCE_DIR}
)

add_library(
  bisection_method
  bisection_method/bisection_method.cpp
)

target_include_directories(
  bisection_method 
  PUBLIC
  ${CMAKE_SOURCE_DIR}
)

add_library(
  secant_method
  secant_method/secant_method.cpp
)

target_include_directories(
  secant_method 
  PUBLIC
  ${CMAKE_SOURCE_DIR}
)

add_executable(
  RootFindersTests
  ./test/newtons_method_tests.cpp
)
target_include_directories(RootFindersTests PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    RootFindersTests
    PUBLIC
    RootFindersLib
    GTest::gtest_main
)

add_executable(
  bisection_method_tests
  ./test/bisection_method_tests.cpp
)
target_include_directories(bisection_method_tests PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    bisection_method_tests
    PUBLIC
    bisection_method
    GTest::gtest_main
)

add_executable(
  secant_method_tests
  ./test/secant_method_tests.cpp
)
target_include_directories(secant_method_tests PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    secant_method_tests
    PUBLIC
    secant_method
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(RootFindersTests LABELS fast)
gtest_discover_tests(bisection_method_tests)
gtest_discover_tests(secant_method_tests)
