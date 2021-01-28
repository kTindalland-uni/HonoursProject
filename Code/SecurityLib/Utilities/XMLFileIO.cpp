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

		auto config = doc.child("SecConfig");

		result_config.HashingMethod = config.child("Hashing").attribute("Method").value();

		result_config.EncryptionMethod = config.child("Encryption").attribute("Method").value();

		result_config.KeyExchangeMethod = config.child("KeyExchange").attribute("Method").value();

		result_config.SignatureMethod = config.child("KeyExchange").attribute("Method").value();

		result_config.SymmetricKeyGenerationMethod = config.child("KeyGeneration").attribute("Method").value();

		return result_config;
	}

	void XMLFileIO::WriteConfiguration(SecurityConfiguration config, std::string filepath) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(filepath.c_str());

		if (!result) {
			// TODO: Handle invalid xml document
		}

		auto config_node = doc.child("SecConfig");

		config_node.child("Hashing").remove_attribute("Method");
		config_node.child("Hashing").append_attribute("Method") = config.HashingMethod.c_str();

		config_node.child("Encryption").remove_attribute("Method");
		config_node.child("Encryption").append_attribute("Method") = config.EncryptionMethod.c_str();

		config_node.child("KeyExchange").remove_attribute("Method");
		config_node.child("KeyExchange").append_attribute("Method") = config.KeyExchangeMethod.c_str();

		config_node.child("Signature").remove_attribute("Method");
		config_node.child("Signature").append_attribute("Method") = config.SignatureMethod.c_str();

		config_node.child("KeyGeneration").remove_attribute("Method");
		config_node.child("KeyGeneration").append_attribute("Method") = config.SymmetricKeyGenerationMethod.c_str();

		doc.save_file(filepath.c_str(), PUGIXML_TEXT("	"));


	}
}
