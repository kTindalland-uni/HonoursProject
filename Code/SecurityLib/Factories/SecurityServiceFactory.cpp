#include <string>

// Interface definitions
#include <SecurityLib/Interfaces/IEncryptionService.hpp>
#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>
#include <SecurityLib/Interfaces/ISignatureService.hpp>
#include <SecurityLib/Interfaces/IHashingService.hpp>
#include <SecurityLub/Interfaces/ISymmetricKeyGenerationService.hpp>

// Implementation definitions
#include <SecurityLib/Implementation/SecurityServiceFactory.hpp>
#include <SecurityLib/Implementation/AESEncryptionService.hpp>
#include <SecurityLib/Implementation/DiffieHelmanKeyExchangeService.hpp>
#include <SecurityLib/Implementation/ElipticCurveKeyGenerationService.hpp>
#include <SecurityLib/Implementation/SHA3HashingService.hpp>
#include <SecurityLib/Implementation/SignatureService.hpp>

namespace securitylib {

	IEncryptionService* SecurityServiceFactory::MakeEncryptionService(std::string method) {
		switch (method) {
			case "AES":
				return new AESEncryptionService();
			default:
				return new AESEncryptionService();
		}
	}

	IKeyExchangeService* SecurityServiceFactory::MakeKeyExchangeService(std::string method) {
		switch (method) {
			case "Diffie-Helman":
				return new DiffieHelmanKeyExchangeService();
			default:
				return new DiffieHelmanKeyExchangeService();
		}
	}

	ISignatureService* SecurityServiceFactory::MakeSignatureService(std::string method) {
		switch (method) {
			default:
				return new SignatureService();
		}
	}


	IHashingService* SecurityServiceFactory::MakeHashingService(std::string method) {
		switch (method) {
			case "SHA3":
				return new SHA3HashingService();
			default:
				return new SHA3HashingService();
		}
	}

	ISymmetricKeyGenerationService* SecurityServiceFactory::MakeKeyGenerationService(std::string method) {
		switch (method) {
			case "Eliptic-Curve":
				return new ElipticCurveKeyGenerationService();
			default:
				return new ElipticCurveKeyGenerationService();
		}
	}
}
