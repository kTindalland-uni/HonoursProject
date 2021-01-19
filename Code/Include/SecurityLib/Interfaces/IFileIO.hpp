#include <string>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>

namespace securitylib {
	class IFileIO {
		virtual SecurityConfiguration ReadConfiguration(std::string filepath) = 0;
		virtual void WriteConfiguration(SecurityConfiguration config, std::string filepath) = 0;
	};
}
