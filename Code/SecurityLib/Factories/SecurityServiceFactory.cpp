#include <string>

// Interface definitions
#include <SecurityLib/Interfaces/IEncryptionService.hpp>
#include <SecurityLib/Interfaces/IKeyExchangeService.hpp>
#include <SecurityLib/Interfaces/ISignatureService.hpp>
#include <SecurityLib/Interfaces/IHashingService.hpp>
#include <SecurityLib/Interfaces/ISymmetricKeyGenerationService.hpp>

// Implementation definitions
#include <SecurityLib/Implementation/SecurityServiceFactory.hpp>
#include <SecurityLib/Implementation/AESEncryptionService.hpp>
#include <SecurityLib/Implementation/DiffieHelmanKeyExchangeService.hpp>
#include <SecurityLib/Implementation/ElipticCurveKeyGenerationService.hpp>
#include <SecurityLib/Implementation/SHA3HashingService.hpp>
#include <SecurityLib/Implementation/SignatureService.hpp>

namespace securitylib {

	IEncryptionService* SecurityServiceFactory::MakeEncryptionService(std::string method) {
		if (method == "AES") {
			return new AESEncryptionService();
		}
		else {
			return new AESEncryptionService();
		}
	}

	IKeyExchangeService* SecurityServiceFactory::MakeKeyExchangeService(std::string method) {
		if (method == "Diffie-Helman") {
			return new DiffieHelmanKeyExchangeService();
		}
		else {
			return new DiffieHelmanKeyExchangeService();
		}
	}

	ISignatureService* SecurityServiceFactory::MakeSignatureService(std::string method) {
		if (method == "Default") {
			return new SignatureService();
		}
		else {
			return new SignatureService();
		}
		
	}


	IHashingService* SecurityServiceFactory::MakeHashingService(std::string method) {
		if (method == "SHA3") {
			return new SHA3HashingService();
		}
		else {
			return new SHA3HashingService();
		}
	}

	ISymmetricKeyGenerationService* SecurityServiceFactory::MakeKeyGenerationService(std::string method) {
		if (method == "Eliptic-Curve") {
			return new ElipticCurveKeyGenerationService();
		}
		else {
			return new ElipticCurveKeyGenerationService();
		}
	}
}
