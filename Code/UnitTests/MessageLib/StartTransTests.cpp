#include <gtest/gtest.h>
#include <MessageLib/StartTransMessage.hpp>
#include <cstring>

#include <iostream>

TEST(StartTransTests, SunnyDay) {
    // Arrange
    msglib::StartTransMessage tx_message("Kai");
    msglib::StartTransMessage rx_message;

    unsigned char buffer[4096];
    std::memset(buffer, 0, 4096);

    // Act
    tx_message.Pack(buffer);

    rx_message.Unpack(buffer);

    // Assert
    ASSERT_TRUE(rx_message.name == "Kai");
}
