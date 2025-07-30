cmake_minimum_required(VERSION 3.31)
project(NumericalMethods)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# add_subdirectory(calculus)
# add_subdirectory(matrix_solvers)
add_subdirectory(optimization)
add_subdirectory(root_finders)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  FetchContent_MakeAvailable(googletest)
 