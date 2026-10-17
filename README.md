# host-inspector

A lightweight C++ utility for Linux that inspects system host metrics directly from the `/proc` filesystem.

## Overview

`host-inspector` reads kernel counters exposed by Linux virtual files to report real-time system performance data without external monitoring dependencies:

- **CPU load average**: Reads 1-minute, 5-minute, and 15-minute load averages from `/proc/loadavg`.
- **Memory metrics**: Parses `/proc/meminfo` for total memory, available memory, and calculates the active utilization percentage.

## Prerequisites

- Linux OS with `/proc` mounted
- C++17 compiler (GCC 7+ or Clang 5+)
- CMake 3.16+ (optional for CMake builds)

## Build instructions

### Using CMake

```bash
# Configure the build directory
cmake -B build -S .

# Compile the executable
cmake --build build

# Run the program
./build/host_inspector
```

### Direct compilation with g++

```bash
g++ -std=c++17 -Wall -Wextra host-inspector/main.cpp -o host_inspector
./host_inspector
```

## Example output

```text
=======================================
     Linux Host Inspector (v1.0)       
=======================================
[+] CPU Load (1m / 5m / 15m):
    2.81 / 1.63 / 1.13

[+] RAM / Memory Usage:
    Total     : 6.99786 GB
    Available : 2.04153 GB
    Used      : 70.8264 %
```

## Project structure

```text
host-inspector/
├── CMakeLists.txt         # CMake build configuration
├── host-inspector/
│   └── main.cpp           # Inspector source code
├── .gitignore
└── README.md
```
