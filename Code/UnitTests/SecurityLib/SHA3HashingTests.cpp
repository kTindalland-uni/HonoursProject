#include <gtest/gtest.h>
#include <string>
#include <SecurityLib/Implementation/SHA3HashingService.hpp>

TEST(SHA3Hashing, SunnyDay) {
	// Arrange
	std::string test_data = "Hello there";
	securitylib::SHA3HashingService hashing_service;
	std::string result;

	// Act
	result = hashing_service.Hash(test_data);

	// Assert
	std::string correct_result = "E034863118F611CAE9CE9FE1C66E2E7BF750CCBD64F7FCB6A777B3D517332AC6";

	ASSERT_EQ(result, correct_result);

}
