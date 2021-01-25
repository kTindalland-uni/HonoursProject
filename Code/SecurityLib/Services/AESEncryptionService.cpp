#include <iostream>
#include <string>
#include <SecurityLib/Implementation/AESEncryptionService.hpp>
#include "filters.h"
#include "aes.h"
#include "cfb.h"
#include "secblock.h"

namespace securitylib {

	std::string AESEncryptionService::EncryptData(std::string key, std::string iv, std::string data) {
		// Turn the key into a secure byte block
		CryptoPP::SecByteBlock key_block(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());
		
		// Turn the initialisation vector into a secure byte block.
		CryptoPP::SecByteBlock iv_block(reinterpret_cast<const CryptoPP::byte*>(&iv[0]), iv.size())

		std::string ciphertext;

		CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption enc;
		enc.SetKeyWithIV(key_block, key_block.size(), iv_block);

		CryptoPP::StringSource source(data, true,
			new CryptoPP::StreamTransformation(enc,
				new CryptoPP::StringSink(ciphertext)
			)
		);

		return ciphertext;
	}

	std::string AESEncryptionService::DecryptData(std::string key, std::string iv, std::string data) {
		std::cout << "Hello world!\n";
		return "Hello";
	}
}
