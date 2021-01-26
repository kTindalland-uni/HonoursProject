cmake_minimum_required(VERSION 3.13.4)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 99) # Use C99
set(CMAKE_CXX_STANDARD 17) # Use C++17

enable_testing()

add_subdirectory(Code)
