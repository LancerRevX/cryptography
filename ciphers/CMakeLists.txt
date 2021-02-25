cmake_minimum_required(VERSION 3.14)

project(ciphers LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ciphers STATIC
    atbash.cpp
    scytale.cpp
    ciphers.hpp
)

target_compile_definitions(ciphers PRIVATE CIPHERS_LIBRARY)
