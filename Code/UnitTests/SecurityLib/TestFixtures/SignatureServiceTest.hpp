#include <gtest/gtest.h>
#include <SecurityLib/Implementation/SignatureService.hpp>
#include <cryptlib.h>
#include <eccrypto.h>
#include <oids.h>
#include <osrng.h>
#include <filters.h>

class SignatureServiceTest: public ::testing::Test {
	protected:
		securitylib::SignatureService signature_service;
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey privateKey;
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;

		std::string private_key, public_key;

		virtual void SetUp() {
			// Load keys
			private_key = "MHQCAQEEICyLzIYrJqTyMmsX3XP+vEZPIrpaSySpmiBKvuPyoYJxoAcGBSuBBAAKoUQDQgAE9gtE8rnW2tqXgQKzs/umc4DkVBKjWOsmfbszBGcWzHUBkwW/9B9MIE/3Qgs+ADGdFbIZ0YbfU2jt7M6SxKlU9A==";
			public_key = "MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAE9gtE8rnW2tqXgQKzs/umc4DkVBKjWOsmfbszBGcWzHUBkwW/9B9MIE/3Qgs+ADGdFbIZ0YbfU2jt7M6SxKlU9A==";

			CryptoPP::StringSource private_key_source(private_key, true);
			CryptoPP::StringSource public_key_source(public_key, true);

			privateKey.Load(private_key_source);
			publicKey.Load(public_key_source);
		}
};
