#include <string>
#include <SecurityLib/Implementation/SignatureService.hpp>

namespace securitylib {
	std::string SignatureService::SignData(std::string data, std::string private_key) {
		return "Not Implemented";
	}

	bool CheckSignature(std::string signed_data, std::string public_key, std::string check_hash) {
		return false;
	}
}

