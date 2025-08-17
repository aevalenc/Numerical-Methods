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

include(GoogleTest)
gtest_discover_tests(RootFindersTests LABELS fast)
