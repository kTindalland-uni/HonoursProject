#include <iostream>
#include <string>
#include <SecurityLib/Implementation/AESEncryptionService.hpp>

namespace securitylib {

	std::string AESEncryptionService::EncryptData(std::string key, std::string data) {
		std::cout << "Hello world!\n";
		return "Hello";
	}

	std::string AESEncryptionService::DecryptData(std::string key, std::string data) {
		std::cout << "Hello world!\n";
		return "Hello";
	}
}
