# Optimization library

add_library(
  ternary_search
  STATIC
  ternary/ternary.cpp
)

target_include_directories(ternary_search PUBLIC
    ${CMAKE_SOURCE_DIR}
)

add_executable(
  ternary_search_tests
  ./ternary/test/ternary_search_tests.cpp
)

target_include_directories(ternary_search_tests PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
    ternary_search_tests
    PUBLIC
    ternary_search
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ternary_search_tests)
