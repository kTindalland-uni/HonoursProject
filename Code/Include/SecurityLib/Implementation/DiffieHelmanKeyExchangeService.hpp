#ifndef __DIFHELKEYEXSERV
#define __DIFHELHEYEXSERV

#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>

namespace securitylib {
	class DiffieHelmanKeyExchangeService: public IKeyExchangeService {
		public:
			int GenerateIntermediateKey(int common_secret, int private_secret);
			int GenerateFinalKey(int swapped_secret, int private_secret);
	};
}

#endif
