#ifndef __SECSERVFAC
#define __SECSERVFAC

#include <string>
#include <SecurityLib/Interfaces/IEncryptionService.hpp>
#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>
#include <SecurityLib/Interfaces/ISignatureService.hpp>
#include <SecurityLib/Interfaces/IHashingService.hpp>
#include <SecurityLib/Interfaces/ISecurityServiceFactory.hpp>

namespace securitylib {
	class SecurityServiceFactory: public ISecurityServiceFactory {
		public:
			IEncryptionService* MakeEncryptionService(std::string method);
			IKeyExchangeService* MakeKeyExchangeService(std::string method);
			ISignatureService* MakeSignatureService(std::string method);
			IHashingService* MakeHashingService(std::string method);
			ISymmetricKeyGenerationService* MakeKeyGenerationService(std::string method);
	};
}

#endif
