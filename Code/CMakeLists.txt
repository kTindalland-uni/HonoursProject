cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(KAI "bleh" OFF)

enable_testing()

add_subdirectory(googletest)

add_subdirectory(SecurityLib)

add_subdirectory(TestingDir)
