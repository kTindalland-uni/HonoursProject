#ifndef __DIFHELKEYEXSERV
#define __DIFHELHEYEXSERV

#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>
#include <tuple>
#include <integer.h>
#include <dh.h>
#include <string>

namespace securitylib {
	class DiffieHelmanKeyExchangeService: public IKeyExchangeService {
		public:
			DiffieHelmanKeyExchangeService();
			void GenerateIntermediateKeys(std::string& privKey, std::string& pubKey);
			std::string GenerateFinalKey(std::string swapped_secret, std::string private_secret);

		private:
			CryptoPP::Integer p;
			CryptoPP::Integer g;
			CryptoPP::Integer q;
			CryptoPP::DH dh;

	};
}

#endif
