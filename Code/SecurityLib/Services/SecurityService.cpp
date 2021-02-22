#include <SecurityLib/SecurityService.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>

// Interfaces
#include <SecurityLib/Interfaces/IEncryptionService.hpp>
#include <SecurityLib/Interfaces/IHashingService.hpp>
#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>
#include <SecurityLib/Interfaces/ISignatureService.hpp>
#include <SecurityLib/Interfaces/ISymmetricKeyGenerationService.hpp>

// Factory
#include <SecurityLib/Implementation/SecurityServiceFactory.hpp>

namespace securitylib {
	SecurityService::SecurityService(SecurityConfiguration config) {
		auto factory = SecurityServiceFactory();

		encryptionService = factory.MakeEncryptionService(config.EncryptionMethod);
		hashingService = factory.MakeHashingService(config.HashingMethod);
		keyExchangeService = factory.MakeKeyExchangeService(config.KeyExchangeMethod);
		signatureService = factory.MakeSignatureService(config.SignatureMethod);
		symmetricKeyGenerationService = factory.MakeKeyGenerationService(config.SymmetricKeyGenerationMethod);

	}

	SecurityService::~SecurityService() {
		delete encryptionService;
		delete hashingService;
		delete keyExchangeService;
		delete signatureService;
		delete symmetricKeyGenerationService;
	}
}
