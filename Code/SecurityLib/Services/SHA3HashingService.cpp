#include <string>
#include <SecurityLib/Implementation/SHA3HashingService.hpp>
#include <cryptlib.h>
#include <filters.h>
#include <hex.h>
#include <sha3.h>

// Code based on an example from https://www.cryptopp.com/wiki/SHA

namespace securitylib {
	std::string SHA3HashingService::Hash(std::string data) {
		std::string result;
		CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(result));

		CryptoPP::SHA3_256 hash;

		std::string digest;

		hash.Update((const CryptoPP::byte*)data.data(), data.size());
		digest.resize(hash.DigestSize());
		hash.Final((CryptoPP::byte*)&digest[0]);

		CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));

		return result;
	}
}
