#include <string>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>

namespace securitylib {
	class ConfigurationGenerator {
		public:
			SecurityConfiguration GenerateConfigFromFile(std::string filepath);
			SecurityConfiguration GenerateDefaultConfiguration();
	};
}
