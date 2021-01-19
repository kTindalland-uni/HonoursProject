#include <string>

namespace securitylib {
	struct SecurityConfiguration {
		std::string EncryptionMethod;
		std::string KeyExchangeMethod;
		std::string SignatureMethod;
		std::string HashingMethod;
		std::string SymmetricKeyGenerationMethod;
	};
}
