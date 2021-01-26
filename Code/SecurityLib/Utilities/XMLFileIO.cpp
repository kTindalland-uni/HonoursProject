#include <string>
#include <iostream>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <SecurityLib/Implementation/XMLFileIO.hpp>
#include "pugixml.hpp"

namespace securitylib {
	SecurityConfiguration XMLFileIO::ReadConfiguration(std::string filepath) {
		SecurityConfiguration result_config;

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(filepath.c_str());

		if (!result) {
			// TODO: Handle invalid xml document.
		}

		result_config.HashingMethod = doc.child("SecConfig").child("HashingMethod").attribute("Method").value();

		return result_config;
	}

	void XMLFileIO::WriteConfiguration(SecurityConfiguration config, std::string filepath) {

	}
}
