#include "Mocks/FileIOMock.hpp"
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <SecurityLib/ConfigurationGenerator.hpp>
#include <string>
#include <gtest/gtest.h>

using ::testing::Return;

TEST(ConfigGeneratorTests, SunnyDay) {
	// Arrange
	securitylib::FileIOMock fileio;
	securitylib::SecurityConfiguration expected_result;
	expected_result.HashingMethod = "Testing";
	
	EXPECT_CALL(fileio, ReadConfiguration("FakePath")).WillRepeatedly(Return(expected_result));
	securitylib::SecurityConfiguration result;
	securitylib::ConfigurationGenerator generator(&fileio);

	// Act
	result = generator.GenerateConfigFromFile("FakePath");
	
	// Assert
	ASSERT_EQ(result.HashingMethod, expected_result.HashingMethod);

}
