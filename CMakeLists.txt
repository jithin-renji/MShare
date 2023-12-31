cmake_minimum_required(VERSION 3.27)
project(MShare)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    mshared
    src/mshared/main.cpp
    src/ArgParser.cpp
    src/Logger.cpp
    src/Crypto.cpp
    src/Packet.cpp
    src/mshared/MessageServer.cpp

    src/ArgParser.hpp
    src/Logger.hpp
    src/Crypto.hpp
    src/Packet.hpp
    src/mshared/MessageServer.hpp
)

target_include_directories(
    mshared
    PRIVATE
        ./
        src/
        src/mshared/
)

target_link_directories(
    mshared
    PRIVATE
        cryptopp/
)

target_link_libraries(
    mshared
    cryptopp
)
