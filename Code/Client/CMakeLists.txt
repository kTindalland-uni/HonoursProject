cmake_minimum_required(VERSION 3.13.4)

include_directories(../Include)

add_executable(Client main.cpp Client.cpp)
target_link_libraries(Client PRIVATE messages security)