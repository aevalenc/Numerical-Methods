cmake_minimum_required(VERSION 3.1)
project(RootFinders)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  FetchContent_MakeAvailable(googletest)
  
enable_testing()

add_library(
  RootFindersLib
  STATIC
  ./newtons_method.cpp
)

set_property(TARGET RootFindersLib PROPERTY CXX_STANDARD 17)
target_include_directories(RootFindersLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/root_finders
)

add_executable(
  RootFindersTests
  ./test/newtons_method_tests.cpp
)
target_include_directories(RootFindersTests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
set_property(TARGET RootFindersTests PROPERTY CXX_STANDARD 17)

target_link_libraries(
    RootFindersTests
    PUBLIC
    RootFindersLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(RootFindersTests)
