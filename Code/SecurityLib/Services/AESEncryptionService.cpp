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

		std::string ciphertext;

        // Create encryptor with instance of AES block cipher
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor(key_block, key_block.size(), iv_block);

        CryptoPP::StringSource(data, true,
        new CryptoPP::StreamTransformationFilter(encryptor,
            new CryptoPP::StringSink(ciphertext)
            )
        );

        return ciphertext;

	}

	std::string AESEncryptionService::DecryptData(std::string key, std::string iv, std::string data) {
		// Turn the key into a secure byte block
		CryptoPP::SecByteBlock key_block(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());

		// Turn the initialisation vector into a secure byte block.
		CryptoPP::SecByteBlock iv_block(reinterpret_cast<const CryptoPP::byte*>(&iv[0]), iv.size());

		std::string plaintext;

        // Create decryptor with instance of AES block cipher
        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryptor(key_block, key_block.size(), iv_block);

        CryptoPP::StringSource(data, true,
        new CryptoPP::StreamTransformationFilter(decryptor,
            new CryptoPP::StringSink(plaintext)
            )
        );

        return plaintext;
	}
}
