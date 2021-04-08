#include <string>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <SecurityLib/ConfigurationGenerator.hpp>
#include <SecurityLib/Interfaces/IFileIO.hpp>
#include <SecurityLib/Implementation/XMLFileIO.hpp>

namespace securitylib {
	ConfigurationGenerator::ConfigurationGenerator() {
		fileio = NULL;
	}

	ConfigurationGenerator::ConfigurationGenerator(IFileIO* fileio_method) {
		fileio = fileio_method;
	}

	ConfigurationGenerator::~ConfigurationGenerator() {
		if (fileio != NULL) {
			delete fileio;
		}
	}

	SecurityConfiguration ConfigurationGenerator::GenerateConfigFromFile(std::string filepath) {
		SecurityConfiguration result;

		result = fileio->ReadConfiguration(filepath);

		return result;
	}

	SecurityConfiguration ConfigurationGenerator::GenerateDefaultConfiguration() {
		SecurityConfiguration result;

		result.HashingMethod = "SHA3";
		result.EncryptionMethod = "AES";
		result.KeyExchangeMethod = "Diffie-Helman";
		result.SymmetricKeyGenerationMethod = "Eliptic-Curve";
		result.SignatureMethod = "Default";

		return result;
	}
}
