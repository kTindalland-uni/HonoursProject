cmake_minimum_required(VERSION 3.13.4)

include_directories(${CMAKE_SOURCE_DIR}/Code/Include)

add_executable(SHA3HashingUnitTests SHA3HashingTests.cpp)

target_link_libraries(SHA3HashingUnitTests PUBLIC
	gtest_main
	security
)

add_test (
	NAME SHA3Hashing
	COMMAND SHA3HashingUnitTests
)
