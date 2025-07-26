# Mini-Blockchain-CPP

A tiny blockchain in modern C++ with OpenSSL (via vcpkg).

## Build

```powershell
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build build --config Release
