#include <string>
#include <SecurityLib/Implementation/SHA3HashingService.hpp>
#include <cryptlib.h>
#include <sha3.h>

// Code based on an example from https://www.cryptopp.com/wiki/SHA

namespace securitylib {
	std::string SHA3HashingService::Hash(std::string data) {
		CryptoPP::SHA3_256 hash;

		std::string digest;

		hash.Update((const CryptoPP::byte*)data.data(), data.size());
		digest.resize(hash.DigestSize());
		hash.Final((CryptoPP::byte*)&digest[0]);

		return digest;
	}
}
