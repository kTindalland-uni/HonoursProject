#include <string>
#include <cryptlib.h>
#include <osrng.h>
#include <filters.h>
#include <oids.h>
#include <eccrypto.h>
#include <SecurityLib/Implementation/SignatureService.hpp>

namespace securitylib {
	std::string SignatureService::SignData(std::string data, std::string private_key) {
		// Load in private key
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey privateKey;
		CryptoPP::StringSource key_source(private_key, true);
		privateKey.Load(key_source);

		std::string signature;
		CryptoPP::AutoSeededRandomPool prng;
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(privateKey);

		CryptoPP::StringSource s(data, true,
				new CryptoPP::SignerFilter(prng,
					signer,
					new CryptoPP::StringSink(signature)
				)
			);

		return signature;
	}

	bool SignatureService::CheckSignature(std::string signed_data, std::string public_key, std::string check_hash) {
		// Load in public key
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;
		CryptoPP::StringSource key_source(public_key, true);
		publicKey.Load(key_source);

		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(publicKey);

		bool result = false;

		CryptoPP::StringSource ss(signed_data+check_hash, true,
				new CryptoPP::SignatureVerificationFilter(
					verifier,
					new CryptoPP::ArraySink( (CryptoPP::byte*)&result, sizeof(result) )
				)
			);

		return result;
	}
}

