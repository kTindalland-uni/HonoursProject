#ifndef __ISYMKEYGENSERV
#define __ISYMKEYGENSERV

#include <string>

namespace securitylib {
	class ISymmetricKeyGenerationService  {
		public:
			virtual void GenerateKeys(std::string& private_key, std::string& public_key) = 0;
	};
}

#endif
