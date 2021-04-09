cmake_minimum_required(VERSION 3.13.4)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Sources
	StartTransMessage.cpp
	RequestMessage.cpp
	ResponseMessage.cpp
	EncryptedMessage.cpp
)

include_directories(../Include)
add_library(messages ${Sources}) 