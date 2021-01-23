#ifndef __XMLFILEIO
#define __XMLFILEIO

#include <string>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <SecurityLib/Interfaces/IFileIO.hpp>

namespace securitylib {
	class XMLFileIO: public IFileIO {
		SecurityConfiguration ReadConfiguration(std::string filepath);
		void WriteConfiguration(SecurityConfiguration config, std::string filepath);
	};
}

#endif
