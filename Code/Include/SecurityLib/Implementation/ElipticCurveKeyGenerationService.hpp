#ifndef __ELIPKEYGENSERV
#define __ELIPKEYGENSERV

#include <SecurityLib/Interfaces/ISymmetricKeyGenerationService.hpp>

namespace securitylib {
	class ElipticCurveKeyGenerationService: public ISymmetricKeyGenerationService {
		public:
			void GenerateKeys(std::string& private_key, std::string& public_key);
	};
}

#endif
