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
	std::string correct_result = "e034863118f611cae9ce9fe1c66e2e7bf750ccbd64f7fcb6a777b3d517332ac6";

	ASSERT_EQ(result, correct_result);

}
