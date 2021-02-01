#include <gtest/gtest.h>
#include <SecurityLib/Implementation/ElipticCurveKeyGenerationService.hpp>
#include <string>
#include <cryptlib.h>
#include <osrng.h>

TEST(ElipticCurveUnitTests, SunnyDay) {
	// Arrange
	securitylib::ElipticCurveKeyGenerationService key_gen;
	CryptoPP::AutoSeededRandomPool prng;
	
	std::string pub_key, priv_key;

	// Act
	
	// Assert
	
}
