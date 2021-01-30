#include <cryptlib.h>
#include <eccrypto.h>
#include <oids.h>
#include <osrng.h>
#include <filters.h>
#include <string>
#include <SecurityLib/Implementation/ElipticCurveKeyGenerationService.hpp>

namespace securitylib {
	void ElipticCurveKeyGenerationService::GenerateKeys(std::string& private_key, std::string& public_key) {
		// Initial stuff
		CryptoPP::AutoSeededRandomPool rng;
		bool result;

		// Generate the private key
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey privateKey;
		privateKey.Initialize(rng, CryptoPP::ASN1::secp256k1() );

		result = privateKey.Validate(rng, 3);

		if (!result) { 
			// TODO: Handle this result...
		}

		// Generate the public key
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;
		privateKey.MakePublicKey(publicKey);

		result = publicKey.Validate(rng, 3);
		
		if (!result) {
			// TODO: Handle this result...
		}

		// Save the keys to the strings
		CryptoPP::StringSink privateKeySink(private_key);
		CryptoPP::StringSink publicKeySink(public_key);

		privateKey.Save(privateKeySink);
		publicKey.Save(publicKeySink);

	}
}
