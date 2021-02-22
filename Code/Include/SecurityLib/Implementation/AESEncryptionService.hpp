#ifndef __AESENCSERV
#define __AESENCSERV

#include <string>
#include <SecurityLib/Interfaces/IEncryptionService.hpp>

namespace securitylib {
	class AESEncryptionService: public IEncryptionService {
		public:
			std::string EncryptData(std::string key, std::string iv, std::string data);
			std::string DecryptData(std::string key, std::string iv, std::string data);
	};
}

#endif
