cmake_minimum_required(VERSION 3.14)
project(MiniBlockchain)

set(CMAKE_CXX_STANDARD 17)

# Use vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(OpenSSL REQUIRED)

add_executable(MiniBlockchain
    src/main.cpp
    src/Block.cpp
    src/Blockchain.cpp
    src/Transaction.cpp
    src/Wallet.cpp
    src/utils/Hashing.cpp
    src/utils/MerkelTree.cpp
    src/utils/Timestamp.cpp
)

target_include_directories(MiniBlockchain PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
)# Links the SSL and Crypto libraries from OpenSSL into executable
target_link_libraries(MiniBlockchain PRIVATE OpenSSL::SSL OpenSSL::Crypto)
