#ifndef __IKEYEXSERV
#define __IKEYEXSERV

namespace securitylib {

	class IKeyExchangeService {
		public:
			virtual int GenerateIntermediateKey(int common_secret, int private_secret) = 0;
			virtual int GenerateFinalKey(int swapped_secret, int private_secret) = 0;
	};

}

#endif
