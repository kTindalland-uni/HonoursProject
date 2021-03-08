cmake_minimum_required(VERSION 3.13.4)

include_directories(${CMAKE_SOURCE_DIR}/Code/Include)

add_executable(StartTransTests StartTransTests.cpp)

target_link_libraries(StartTransTests PUBLIC
	gtest_main
	messages
)

add_test (
	NAME StartTransTests
	COMMAND StartTransTests
)