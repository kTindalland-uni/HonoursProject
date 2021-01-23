#ifndef __IHASHSERV
#define __IHASHSERV

#include <string>

namespace securitylib {
	class IHashingService {
		public:
			virtual std::string Hash(std::string data) = 0;
	};
}

#endif
