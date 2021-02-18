#include <tuple>
#include <SecurityLib/Implementation/DiffieHelmanKeyExchangeService.hpp>
#include <dh.h>
#include <cryptlib.h>
#include <osrng.h>
#include <integer.h>

namespace securitylib {
	std::tuple<CryptoPP::Integer, CryptoPP::Integer,CryptoPP::Integer, CryptoPP::Integer> DiffieHelmanKeyExchangeService::GenerateInitialParameters() {
		CryptoPP::DH dh;
		CryptoPP::AutoSeededRandomPool prng;

		dh.AccessGroupParameters().GenerateRandomWithKeySize(prng, 3072);

		const CryptoPP::Integer p = dh.GetGroupParameters().GetModulus();
		CryptoPP::Integer q = (p-1)/2;
		const CryptoPP::Integer g = dh.GetGroupParameters().GetGenerator();
		CryptoPP::Integer r = dh.GetGroupParameters().GetSubgroupOrder();


		auto result = std::make_tuple(p, g, q, r);

		return result;
	}

	int DiffieHelmanKeyExchangeService::GenerateIntermediateKey(int common_secret, int private_secret) {
		// Get / Generate Parameters
		// Just generating for now
		auto params = GenerateInitialParameters();
		CryptoPP::Integer p, g, q, r;
		std::tie (p, g, q, r) = params;

		
		CryptoPP::AutoSeededRandomPool prng;
		CryptoPP::DH dh;
		dh.AccessGroupParameters().Initialize(p, q, g);

		CryptoPP::SecByteBlock private_key(dh.PrivateKeyLength());
		CryptoPP::SecByteBlock public_key(dh.PublicKeyLength());
		dh.GenerateKeyPair(prng, private_key, public_key);

		return 0;
	}

	int DiffieHelmanKeyExchangeService::GenerateFinalKey(int swapped_secret, int private_key) {
		return 0;
	}
}
