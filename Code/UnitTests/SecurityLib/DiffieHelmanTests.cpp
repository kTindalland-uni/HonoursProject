#include <gtest/gtest.h>
#include <SecurityLib/Implementation/DiffieHelmanKeyExchangeService.hpp>

TEST(DiffieHelmanTesting, SunnyDay) {
    // Arrange
    securitylib::DiffieHelmanKeyExchangeService dhA;
    securitylib::DiffieHelmanKeyExchangeService dhB;
    std::string privA, pubA, privB, pubB, resultA, resultB;

    // Act
    dhA.GenerateIntermediateKeys(privA, pubA);
    dhB.GenerateIntermediateKeys(privB, pubB);

    resultA = dhA.GenerateFinalKey(privA, pubB);
    resultB = dhB.GenerateFinalKey(privB, pubA);

    // Assert
    ASSERT_TRUE(resultA == resultB);

}