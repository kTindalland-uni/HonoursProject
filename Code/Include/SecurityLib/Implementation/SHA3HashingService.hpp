#include <string>

namespace securitylib {
	class SHA3HashingService: public IHashingService {
		public:
			std::string Hash(std::string data);
	};
}
