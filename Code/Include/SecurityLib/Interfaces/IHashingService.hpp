#include <string>

namespace securitylib {
	class IHashingService {
		public:
			virtual std::string Hash(std::string data) = 0;
	};
}
