cmake_minimum_required(VERSION 3.13.4)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
include_directories(../Include)

add_executable(Client main.cpp Client.cpp)
target_link_libraries(Client PRIVATE Threads::Threads messages security)