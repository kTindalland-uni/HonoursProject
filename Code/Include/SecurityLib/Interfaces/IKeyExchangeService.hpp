#ifndef __IKEYEXSERV
#define __IKEYEXSERV

#include <string>

namespace securitylib {

	class IKeyExchangeService {
		public:
			virtual void GenerateIntermediateKeys(std::string& privKey, std::string& pubKey) = 0;
			virtual std::string GenerateFinalKey(std::string swapped_secret, std::string private_secret) = 0;
	};

}

#endif
