#ifndef __SHA3HASHSERV
#define __SHA3HASHSERV

#include <string>
#include <SecurityLib/Interfaces/IHashingService.hpp>

namespace securitylib {
	class SHA3HashingService: public IHashingService {
		public:
			std::string Hash(std::string data);
	};
}

#endif
