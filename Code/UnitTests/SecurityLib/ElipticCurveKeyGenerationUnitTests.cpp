#include <gtest/gtest.h>
#include <SecurityLib/Implementation/ElipticCurveKeyGenerationService.hpp>
#include <string>
#include <cryptlib.h>
#include <eccrypto.h>
#include <oids.h>
#include <osrng.h>
#include <filters.h>


TEST(ElipticCurveUnitTests, SunnyDay) {
	// Arrange
	securitylib::ElipticCurveKeyGenerationService key_gen;
	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey privateKey;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;

	
	std::string pub_key, priv_key, signature;
	std::string message = "It's over Anakin, I have the high ground!";

	// Act
	key_gen.GenerateKeys(priv_key, pub_key);

	CryptoPP::StringSource privateSource(priv_key, true);
	CryptoPP::StringSource publicSource(pub_key, true);

	privateKey.Load(privateSource);
	publicKey.Load(publicSource);

	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(privateKey);

	// Sign message
	CryptoPP::StringSource s(message, true,
			new CryptoPP::SignerFilter(prng,
				signer,
				new CryptoPP::StringSink(signature)
			)
		);
	
	// Verify message
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(publicKey);
	bool result = false;
	
	CryptoPP::StringSource ss(signature+message, true,
			new CryptoPP::SignatureVerificationFilter(
				verifier,
				new CryptoPP::ArraySink( (CryptoPP::byte*)&result, sizeof(result) )
			)
		);

	// Assert
	ASSERT_TRUE(result);
}
