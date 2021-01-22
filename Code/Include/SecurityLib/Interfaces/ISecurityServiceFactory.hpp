#include <string>
#include <SecurityLib/Interfaces/IEncryptionService.hpp>
#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>
#include <SecurityLib/Interfaces/ISignatureService.hpp>
#include <SecurityLib/Interfaces/IHashingService.hpp>

namespace securitylib {
	class ISecurityServiceFactory {
		public:
			virtual IEncryptionService* MakeEncryptionService(std::string method) = 0;
			virtual IKeyExchangeService* MakeKeyExchangeService(std::string method) = 0;
			virtual ISignatureService* MakeSignatureService(std::string method) = 0;
			virtual IHashingService* MakeHashingService(std::string method) = 0;
			virtual ISymmetricKeyGenerationService* MakeKeyGenerationService(std::string method) = 0;
	};
}
