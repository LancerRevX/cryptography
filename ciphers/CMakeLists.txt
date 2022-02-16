cmake_minimum_required(VERSION 3.14)

project(ciphers LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ciphers STATIC
    atbash.cpp
    scytale.cpp
    polybius_square.cpp
    caesar_cipher.cpp
    cardan_grille.cpp
    richelieu.cpp
    alberti_disk.cpp
    gronsveld.cpp
    vigenere.cpp
    playfair.cpp
    ciphers.hpp
    hill.cpp
    vernam.cpp
    xor_cipher.cpp
    des.cpp
)
target_compile_definitions(ciphers PRIVATE CIPHERS_LIBRARY)
link_directories(matrix/)
target_link_libraries(ciphers PUBLIC C:/Users/nikitakirenkov/Projects/cryptography/ciphers/matrix/libmatrix.a)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ciphers_tests tests/main.cpp)
target_link_libraries(ciphers_tests gtest ciphers)
