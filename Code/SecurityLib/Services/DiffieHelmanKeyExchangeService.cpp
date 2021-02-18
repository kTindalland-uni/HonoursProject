#include <tuple>
#include <SecurityLib/Implementation/DiffieHelmanKeyExchangeService.hpp>
#include <dh.h>
#include <cryptlib.h>
#include <osrng.h>
#include <integer.h>
#include <stdexcept>
#include <string>

namespace securitylib {
	DiffieHelmanKeyExchangeService::DiffieHelmanKeyExchangeService() {
		// Use the standard values for p, g, and q from RFC 5114's 1024 bit group.

		p = CryptoPP::Integer("0xB10B8F96A080E01DDE92DE5EAE5D54EC52C99FBCFB06A3C6"
	"9A6A9DCA52D23B616073E28675A23D189838EF1E2EE652C0"
	"13ECB4AEA906112324975C3CD49B83BFACCBDD7D90C4BD70"
	"98488E9C219A73724EFFD6FAE5644738FAA31A4FF55BCCC0"
	"A151AF5F0DC8B4BD45BF37DF365C1A65E68CFDA76D4DA708"
	"DF1FB2BC2E4A4371");

		g = CryptoPP::Integer("0xA4D1CBD5C3FD34126765A442EFB99905F8104DD258AC507F"
	"D6406CFF14266D31266FEA1E5C41564B777E690F5504F213"
	"160217B4B01B886A5E91547F9E2749F4D7FBD7D3B9A92EE1"
	"909D0D2263F80A76A6A24C087A091F531DBF0A0169B6A28A"
	"D662A4D18E73AFA32D779D5918D08BC8858F4DCEF97C2A24"
	"855E6EEB22B3B2E5");

		q = CryptoPP::Integer("0xF518AA8781A8DF278ABA4E7D64B7CB9D49462353");

		dh = CryptoPP::DH();

	}

	void DiffieHelmanKeyExchangeService::GenerateIntermediateKeys(std::string& privKey, std::string& pubKey) {
		
		CryptoPP::AutoSeededRandomPool prng;
		dh.AccessGroupParameters().Initialize(p, q, g);

		if (!dh.AccessGroupParameters().ValidateGroup(prng, 3)) {
			// Failed validation...
			throw std::runtime_error("Failed to validate prime and generator.");
		}

		CryptoPP::SecByteBlock private_key(dh.PrivateKeyLength());
		CryptoPP::SecByteBlock public_key(dh.PublicKeyLength());
		dh.GenerateKeyPair(prng, private_key, public_key);

		privKey = reinterpret_cast<const char*>(&private_key[0], private_key.size());
		pubKey = reinterpret_cast<const char*>(&public_key[0], public_key.size());
	}

	std::string DiffieHelmanKeyExchangeService::GenerateFinalKey(std::string privA, std::string pubB) {
		// Assume dh has been initialised...

		// Initialise shared byte block
		CryptoPP::SecByteBlock shared(dh.AgreedValueLength());

		// Load the keys into byte blocks.
		CryptoPP::SecByteBlock privABytes(reinterpret_cast<const CryptoPP::byte*>(&privA[0]), privA.size());
		CryptoPP::SecByteBlock pubBBytes(reinterpret_cast<const CryptoPP::byte*>(&pubB[0]), pubB.size());

		if (!dh.Agree(shared, privABytes, pubBBytes)) {
			throw std::runtime_error("Failed to reach a shared secret.");
		}

		// Save the shared secret to a string.
		std::string result(reinterpret_cast<const char*>(&shared[0]), shared.size());
		
		return result;
	}
}
