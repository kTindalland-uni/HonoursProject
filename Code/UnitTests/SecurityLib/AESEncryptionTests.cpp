#include <gtest/gtest.h>
#include <SecurityLib/Implementation/AESEncryptionService.hpp>
#include <string>

TEST(AES_Encryption_Tests, SunnyDay) {
    // Arrange
    securitylib::AESEncryptionService service;    

    // Act
    std::string ciphertext = service.EncryptData("HHHHHHHHHHHHHHHH", "AAAAAAAAAAAAAAAA", "Hello world!");

    std::string result = service.DecryptData("HHHHHHHHHHHHHHHH", "AAAAAAAAAAAAAAAA", ciphertext);

    // Assert
    ASSERT_TRUE("Hello world!" == result);

}
