# WebSocket Client Framework

## Overview
C++ WebSocket client framework built with Boost.Beast and provide asynchronous WebSocket communication.
Implementation example for HyperLiquid API.

## Features
- Asynchronous WebSocket communication
- Modular design with base client interface
- Concrete implementation for HyperLiquid API
- Real-time market data subscription

## Requirements
- C++17 compliant compiler
- CMake 3.28.3 or higher
- vcpkg package manager
- Dependencies are managed through vcpkg manifest:
  - Boost.Beast
  - Boost.ASIO
  - OpenSSL
  - nlohmann_json

## Project Structure
```
.
├── CMakeLists.txt          # Main CMake configuration
├── build.sh                # Build automation script
├── executables/            # Example executables
│   ├── CMakeLists.txt
│   └── main.cpp           # Usage example
├── vcpkg.json             # Dependencies manifest
└── xwsclient/             # Library source
    ├── CMakeLists.txt
    ├── common/            # Common WebSocket functionality
    │   ├── ws_common.cpp
    │   └── ws_common.hpp
    └── hyperliquid/       # HyperLiquid specific implementation
        ├── hlclient.cpp
        └── hlclient.hpp
```

## Building

### Basic Build
The project includes a build script (`build.sh`) that handles the build process:

```bash
./build.sh
```

The script performs the following operations:
1. Cleans the build directory
2. Configures CMake with vcpkg toolchain
3. Builds the project

### Build Options

- Debug build:
```bash
cmake -S . -B out/build/ -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug
```

- Release build (default):
```bash
cmake -S . -B out/build/ -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
```

## API Documentation

### Methods
- `subscribe()`: Subscribes to real-time candlestick data
- `run()`: Starts the WebSocket client
- `onWrite()`: Handles write completion
- `onRead()`: Handles read completion

### Supported Features
- Real-time candlestick data subscription
- Asynchronous message handling
- Error handling and logging

## Common Build Issues
- Verify vcpkg manifest mode is enabled
- Ensure VCPKG_ROOT environment variable is set
- Verify vcpkg is properly installed
- Check CMAKE_TOOLCHAIN_FILE path

## Acknowledgments
- HyperLiquid API documentation
- Boost.Beast library
- Contributors and maintainers
