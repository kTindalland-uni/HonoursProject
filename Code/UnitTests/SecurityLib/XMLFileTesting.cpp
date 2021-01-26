#include <string>
#include <SecurityLib/Implementation/XMLFileIO.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <gtest/gtest.h>

TEST(XMLFileIOReading, SunnyDay) {
	// Arrange
	std::string known_good_file = "KnownGoodConfig.xml";
	securitylib::XMLFileIO fileio;
	securitylib::SecurityConfiguration config;

	// Act
	config = fileio.ReadConfiguration(known_good_file.c_str());

	// Assert
	ASSERT_EQ(config.HashingMethod, "SHA3");

}

