cmake_minimum_required(VERSION 3.13.4)

include_directories(${CMAKE_SOURCE_DIR}/Code/Include ${CMAKE_SOURCE_DIR}/Code/cryptopp)

add_executable(SHA3HashingUnitTests SHA3HashingTests.cpp)

target_link_libraries(SHA3HashingUnitTests PUBLIC
	gtest_main
	security
)

add_test (
	NAME SHA3Hashing
	COMMAND SHA3HashingUnitTests
)

# XML File IO Tests
add_executable(XMLFileIOUnitTests XMLFileTesting.cpp)

target_link_libraries(XMLFileIOUnitTests PUBLIC
	gtest_main
	security
	pugixml-static
)

add_test (
	NAME XMLFileIO
	COMMAND XMLFileIOUnitTests
)

# Config generator
add_executable(ConfigGeneratorUnitTests ConfigGeneratorTests.cpp Mocks/FileIOMock.hpp)

target_link_libraries(ConfigGeneratorUnitTests PUBLIC
	gmock_main
	security
)

add_test (
	NAME ConfigGenerator
	COMMAND ConfigGeneratorUnitTests
)

# Key Gen
add_executable(KeyGenerationUnitTests ElipticCurveKeyGenerationUnitTests.cpp)

target_link_libraries(KeyGenerationUnitTests PUBLIC
	gtest_main
	security
	crypto_pp
)

add_test(
	NAME ElipticCurveKeyGen
	COMMAND KeyGenerationUnitTests
)

# Signature Service
add_executable(SignatureServiceTests SignatureServiceUnitTests.cpp TestFixtures/SignatureServiceTest.hpp)

target_link_libraries(SignatureServiceTests PUBLIC
	gtest_main
	security
	crypto_pp
)

add_test(
	NAME SignatureServiceTests
	COMMAND SignatureServiceUnitTests
)

configure_file(KnownGoodConfig.xml KnownGoodConfig.xml COPYONLY)
configure_file(Config.xml Config.xml COPYONLY)
