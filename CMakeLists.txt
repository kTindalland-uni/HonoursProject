cmake_minimum_required(VERSION 3.13.4)
set(CMAKE_BUILD_TYPE Debug)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_C_STANDARD 99) # Use C99
set(CMAKE_CXX_STANDARD 17) # Use C++17

enable_testing()

add_library(crypto_pp STATIC IMPORTED)
set_target_properties(crypto_pp PROPERTIES
	IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Code/cryptopp/libcryptopp.a)

add_subdirectory(Code)
