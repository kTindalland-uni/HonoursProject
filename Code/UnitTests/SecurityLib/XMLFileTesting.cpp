#include <string>
#include <SecurityLib/Implementation/XMLFileIO.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>
#include "pugixml.hpp"

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

TEST(XMLFileIOWriting, SunnyDay) {
	// Arrange
	std::string filepath = "Config.xml";
	securitylib::XMLFileIO fileio;
	securitylib::SecurityConfiguration config;

	std::srand(std::time(nullptr));
	int random_number = std::rand();

	std::string number = std::to_string(random_number);
	config.HashingMethod = number;

	// Act
	fileio.WriteConfiguration(config, filepath);
	
	// Assert
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filepath.c_str());

	std::string result_string = doc.child("SecConfig").child("Hashing").attribute("Method").value();

	ASSERT_EQ(result_string, config.HashingMethod);
	
}
