#ifndef __SECSERV
#define __SECSERV

#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <SecurityLib/Interfaces/IEncryptionService.hpp>
#include <SecurityLib/Interfaces/IHashingService.hpp>
#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>
#include <SecurityLib/Interfaces/ISignatureService.hpp>
#include <SecurityLib/Interfaces/ISymmetricKeyGenerationService.hpp>

namespace securitylib {
	class SecurityService {
		public:
			// Constructor
			SecurityService(SecurityConfiguration config);

			// Destructor
			~SecurityService();

			// Public Fields
			IEncryptionService* encryptionService;
			IHashingService* hashingService;
			IKeyExchangeService* keyExchangeService;
			ISignatureService* signatureService;
			ISymmetricKeyGenerationService* symmetricKeyGenerationService;
	};
}

#endif
