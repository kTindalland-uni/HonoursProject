#include <SecurityLib/Interfaces/IKeyExchangeService>

namespace securitylib {
	class DiffieHelmanKeyExchangeService: public IKeyExchangeService {
		public:
			int GenerateIntermediateKey(int common_secret, int private_secret);
			int GenerateFinalKey(int swapped_secret, int private_secret);
	};
}
