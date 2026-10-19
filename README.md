# host-inspector

A lightweight C++ utility for Linux that inspects host metrics directly from the `/proc` filesystem.

## What's new in v2.1

Version 2.1 continues modularizing the codebase by separating memory metrics extraction out of `main.cpp`:

- **Modular Memory Collector**: Memory metrics are now collected through a dedicated `MemoryCollector` class returning a typed `MemoryMetrices` struct.
- **Unit Conversion Helpers**: `MemoryMetrices` includes inline helper methods (`totalGb()`, `availableGb()`) to convert raw kilobyte values into gigabytes.
- **Clean Main Coordinator**: `main.cpp` now acts strictly as an orchestrator, delegating metric collection to `CpuCollector` and `MemoryCollector`.

## Features

- **CPU Load**: Extracts 1-minute, 5-minute, and 15-minute load averages from `/proc/loadavg`.
- **Memory Stats**: Reads `MemTotal` and `MemAvailable` from `/proc/meminfo` and calculates active memory utilization percentage.
- **Zero Dependencies**: Uses standard C++17 streams and RAII file handling without external libraries or background daemons.

## Prerequisites

- Linux OS with `/proc` mounted
- C++17 compiler (GCC 7+ or Clang 5+)
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

Compile all source files together:

```bash
g++ -std=c++17 -Wall -Wextra host-inspector/main.cpp host-inspector/cpucollector.cpp host-inspector/memorycollector.cpp -o host_inspector
./host_inspector
```

Or compile with a wildcard:

```bash
g++ -std=c++17 -Wall -Wextra host-inspector/*.cpp -o host_inspector
./host_inspector
```

## Example output

```text
=======================================
     Linux Host Inspector (v2.1)       
=======================================
[+] CPU Load (1m / 5m / 15m):
    2.03 / 1.17 / 0.56

[+] RAM / Memory Usage:
    Total     : 6.99786 GB
    Available : 3.1215 GB
    Used      : 55.3936 %
```

## How it works

`host-inspector` reads kernel counters exposed through the Linux `/proc` virtual filesystem:

- `/proc/loadavg` exposes system load over 1, 5, and 15 minutes. `CpuCollector::collect()` reads this file with `std::ifstream`, stores the values in `CpuMetrices`, and relies on RAII to close the stream handle when execution leaves scope.
- `/proc/meminfo` exposes kernel memory statistics. `MemoryCollector::collect()` reads `MemTotal:` and `MemAvailable:`, computes used memory and percentage, and returns a populated `MemoryMetrices` struct.

## Project structure

```text
host-inspector/
├── CMakeLists.txt                 # CMake configuration
├── README.md                      # Project documentation
├── .gitignore                     # Git ignore rules
└── host-inspector/
    ├── cpucollector.hpp           # CPU collector interface and structs
    ├── cpucollector.cpp           # /proc/loadavg reader implementation
    ├── memorycollector.hpp        # Memory collector interface and structs
    ├── memorycollector.cpp        # /proc/meminfo reader implementation
    ├── main.cpp                   # Application entry point and coordinator
    └── prac.md                    # Architecture and practice notes
```
