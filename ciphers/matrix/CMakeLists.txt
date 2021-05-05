cmake_minimum_required(VERSION 3.14)

project(matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


add_library(matrix STATIC
  matrix.cpp
  matrix.hpp
)
target_compile_definitions(matrix PRIVATE MATRIX_LIBRARY)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(matrix_tests tests/main.cpp)
target_link_libraries(matrix_tests gtest matrix)

