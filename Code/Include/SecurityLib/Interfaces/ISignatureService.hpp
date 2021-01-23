#ifndef __ISIGSERV
#define __ISIGSERV

#include <string>

namespace securitylib {
	class ISignatureService {
		public:
			virtual std::string SignData(std::string data, std::string private_key) = 0;
			virtual bool CheckSignature(std::string signed_data, std::string public_key, std::string check_hash) = 0;
	};
}

#endif
