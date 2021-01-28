#include<SecurityLib/Structures/SecurityConfiguration.hpp>
#include<string>
#include<SecurityLib/Interfaces/IFileIO.hpp>
#include<gmock/gmock.h>

namespace securitylib {
	class FileIOMock: public IFileIO {
		public:
			MOCK_METHOD(SecurityConfiguration, ReadConfiguration, (std::string filepath), (override));
			MOCK_METHOD(void, WriteConfiguration, (SecurityConfiguration config, std::string filepath), (override));
	};
}
