#include <string>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <SecurityLib/Interfaces/IFileIO.hpp>

namespace securitylib {
	class ConfigurationGenerator {
		public:
			ConfigurationGenerator(IFileIO* fileio_method);
			ConfigurationGenerator();
			~ConfigurationGenerator();
			SecurityConfiguration GenerateConfigFromFile(std::string filepath);
			SecurityConfiguration GenerateDefaultConfiguration();
		private:
			IFileIO* fileio;
	};
}
