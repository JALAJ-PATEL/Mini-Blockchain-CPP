cmake_minimum_required(VERSION 3.14)
project(MiniBlockchain)

set(CMAKE_CXX_STANDARD 17)

# Use vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(OpenSSL REQUIRED)

add_executable(MiniBlockchain
    main.cpp
    Block.cpp
)

target_include_directories(MiniBlockchain PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(MiniBlockchain PRIVATE OpenSSL::SSL OpenSSL::Crypto)
