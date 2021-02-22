#include <gtest/gtest.h>
#include <SecurityLib/SecurityService.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>

using securitylib::SecurityConfiguration;
using securitylib::SecurityService;

TEST(DiffieHelmanTesting, SunnyDay) {
    // Arrange
    SecurityConfiguration config;
    config.EncryptionMethod = "AES";
    config.HashingMethod = "SHA3";
    config.SymmetricKeyGenerationMethod = "Eliptic-Curve";
    config.KeyExchangeMethod = "Diffie-Helman";
    config.SignatureMethod = "Default";

    // Act
    SecurityService service(config);

    // Assert
    ASSERT_NE(nullptr, service.encryptionService);
    ASSERT_NE(nullptr, service.hashingService);
    ASSERT_NE(nullptr, service.keyExchangeService);
    ASSERT_NE(nullptr, service.signatureService);
    ASSERT_NE(nullptr, service.symmetricKeyGenerationService);

}
