cmake_minimum_required(VERSION 3.27)
project(MShare)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    MShare
    src/main.cpp
    src/CryptoContext.cpp

    src/CryptoContext.hpp
)

target_include_directories(
    MShare
    PRIVATE
        src/
        ./
)

target_link_directories(
    MShare
    PRIVATE
        cryptopp/
)

target_link_libraries(
    MShare
    cryptopp
)
