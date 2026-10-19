# host-inspector

A lightweight C++ utility for Linux that inspects host metrics directly from the `/proc` filesystem.

## What's new in v2.0

Version 2.0 introduces a modular collector architecture, separating data collection from presentation:

- **Modular CPU Collector**: CPU load averages are parsed through a dedicated `CpuCollector` class returning a typed `CpuMetrices` struct.
- **Multi-file build setup**: Separated headers and implementation files with updated CMake and direct compiler configurations.
- **Extensible structure**: Lays the foundation for upcoming modules like `MemoryCollector` and disk/network inspectors.

## Features

- **CPU Load**: Extracts 1-minute, 5-minute, and 15-minute load averages from `/proc/loadavg`.
- **Memory Stats**: Reads `MemTotal` and `MemAvailable` from `/proc/meminfo` and calculates memory usage percentage.
- **Zero Dependencies**: Queries the Linux kernel directly using standard C++ streams and RAII, without external daemon or library requirements.

## Prerequisites

- Linux OS with `/proc` mounted
- C++17 compatible compiler (GCC 7+ or Clang 5+)
- CMake 3.16+ (optional for CMake builds)

## Build and run

### Using CMake

```bash
# Configure build directory
cmake -B build -S .

# Compile
cmake --build build

# Run the inspector
./build/host_inspector
```

### Direct compilation with g++

Because v2.0 uses modular source files, compile all implementation files together:

```bash
g++ -std=c++17 -Wall -Wextra host-inspector/main.cpp host-inspector/cpucollector.cpp -o host_inspector
./host_inspector
```

Or using a wildcard:

```bash
g++ -std=c++17 -Wall -Wextra host-inspector/*.cpp -o host_inspector
./host_inspector
```

## Example output

```text
=======================================
     Linux Host Inspector (v2.0)       
=======================================
[+] CPU Load (1m / 5m / 15m):
    3.25 / 2.2 / 1.37

[+] RAM / Memory Usage:
    Total     : 6.99787 GB
    Available : 2.56472 GB
    Used      : 63.3499 %
```

## How it works

`host-inspector` reads kernel counters exposed through the Linux `/proc` virtual filesystem:

- `/proc/loadavg` exposes system load over 1, 5, and 15 minutes. `CpuCollector::collect()` opens this stream using RAII (`std::ifstream`), extracts the three values into a `CpuMetrices` struct, and automatically closes the file handle when out of scope.
- `/proc/meminfo` provides real-time memory distribution. The program scans for `MemTotal` and `MemAvailable`, converts values to gigabytes, and derives the active usage percentage.

## Project structure

```text
host-inspector/
├── CMakeLists.txt                 # CMake configuration
├── README.md                      # Project documentation
├── .gitignore                     # Git ignore rules
└── host-inspector/
    ├── cpucollector.hpp           # CPU collector interface and data structures
    ├── cpucollector.cpp           # /proc/loadavg reader implementation
    ├── main.cpp                   # Application entry point and output formatting
    └── prac.md                    # Engineering design notes
```
