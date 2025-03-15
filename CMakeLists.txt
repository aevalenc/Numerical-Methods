cmake_minimum_required(VERSION 3.1)
project(NumericalMethods)

add_library(NumericalMethods SHARED
    root_finders/newtons_method.cpp
)

target_include_directories(NumericalMethods PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/root_finders
)