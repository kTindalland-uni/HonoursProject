cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("../cryptopp")
include_directories("../pugixml/src")
include_directories("../Include")

#add_library(pugixml STATIC IMPORTED)
#set_target_properties(pugixml PROPERTIES
#		IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/build/Code/pugixml/libpugixml.a)

set(Sources
	Factories/SecurityServiceFactory.cpp
	Services/AESEncryptionService.cpp
	Services/SecurityService.cpp
	Services/DiffieHelmanKeyExchangeService.cpp
	Services/SHA3HashingService.cpp
	Services/ElipticCurveKeyGenerationService.cpp
	Services/SignatureService.cpp
	Utilities/ConfigurationGenerator.cpp
	Utilities/XMLFileIO.cpp
)

add_library(security ${Sources})
target_link_libraries(security crypto_pp pugixml-static)
