cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("../Include")

add_library(securitylib Services/AESEncryptionService.cpp)

