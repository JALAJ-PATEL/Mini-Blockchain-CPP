cmake_minimum_required(VERSION 3.25)
project(MiniBlockchain)

set(CMAKE_CXX_STANDARD 17)

if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

include_directories(include)
add_executable(mini-blockchain
    src/main.cpp
    src/blockchain.cpp
)

# Link OpenSSL
find_package(OpenSSL REQUIRED)
target_link_libraries(mini-blockchain PRIVATE OpenSSL::SSL OpenSSL::Crypto)
