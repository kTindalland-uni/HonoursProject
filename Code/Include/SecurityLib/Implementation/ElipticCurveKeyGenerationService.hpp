#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>

namespace securitylib {
	class ElipticCurveKeyGenerationService: public IKeyExchangeService {
		public:
			int GenerateIntermediateKey(int common_key, int private_key);
			int GenerateFinalKey(int swapped_secret, int private_key);
	};
}
