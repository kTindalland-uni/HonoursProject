#include <iostream>
#include <string>
#include <SecurityLib/Implementation/AESEncryptionService.hpp>
#include <filters.h>
#include <aes.h>
#include <secblock.h>
#include <modes.h>
#include <cstring>

namespace securitylib {

	std::string AESEncryptionService::EncryptData(std::string key, std::string iv, std::string data) {
		// Turn the key into a secure byte block
		CryptoPP::SecByteBlock key_block(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());
		
		// Turn the initialisation vector into a secure byte block.
		CryptoPP::SecByteBlock iv_block(reinterpret_cast<const CryptoPP::byte*>(&iv[0]), iv.size());

        CryptoPP::byte plainText[data.size()];
        std::memcpy(&data[0], &plainText[0], data.size());

		CryptoPP::byte ciphertext[data.size()];

        // Create encryptor with instance of AES block cipher
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor(key_block, key_block.size(), iv_block);
        encryptor.ProcessData(ciphertext, plainText, data.size());

        std::string result;
        result.resize(data.size());

        std::memcpy(&result[0], &ciphertext[0], result.size());


		return result;
	}

	std::string AESEncryptionService::DecryptData(std::string key, std::string iv, std::string data) {
		std::cout << "Hello world!\n";
		std::string result = "Hello";

		return result;
	}
}
