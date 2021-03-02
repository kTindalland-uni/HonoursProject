cmake_minimum_required(VERSION 3.13.4)


include_directories(../Include)
add_executable(CommandServer main.cpp TcpServer.cpp)