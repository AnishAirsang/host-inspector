# host-inspector

A lightweight C++ utility for Linux that inspects host metrics directly from the `/proc` filesystem.

## What's new in v2.2

Version 2.2 introduces active CPU utilization monitoring alongside existing load averages and memory tracking:

- **Real-Time CPU Speedometer**: Computes active CPU percentage using a dual-snapshot delta of kernel clock ticks from `/proc/stat` over a 200ms sample window.
- **Tick Snapshot Architecture**: Encapsulates raw tick parsing into a private `readStatSnapshot()` helper and dedicated `CpuSnapshot` struct, separating user/system/idle tick tracking from the public consumer API.
- **Unified CPU Metrics Block**: Updated CLI output format grouping instant CPU usage percentage with 1m, 5m, and 15m load averages under a single section.

## Features

- **CPU Metrics**: Real-time active CPU utilization percentage (`/proc/stat`) and 1m / 5m / 15m load averages (`/proc/loadavg`).
- **Memory Stats**: Reads `MemTotal` and `MemAvailable` from `/proc/meminfo` and calculates active memory utilization percentage with gigabyte conversion helpers.
- **Zero Dependencies**: Uses standard C++17 streams, `<thread>`, `<chrono>`, and RAII file handling without external libraries or background daemons.

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
     Linux Host Inspector (v2.2)       
=======================================
[+] CPU Metrics:
    Usage     : 14.8 %
    Load avg  : 1.52 / 1.6 / 1.33

[+] RAM / Memory Usage:
    Total     : 6.99786 GB
    Available : 2.38596 GB
    Used      : 65.9044 %
```

## How it works

`host-inspector` reads kernel counters exposed through the Linux `/proc` virtual filesystem:

- `/proc/stat` exposes cumulative CPU clock ticks across execution modes (`user`, `nice`, `system`, `idle`, `iowait`, `irq`, etc.). `CpuCollector::collect()` takes two snapshots separated by a 200ms window (`std::this_thread::sleep_for`), computes total and active delta ticks, and calculates the true utilization percentage.
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
    ├── cpucollector.cpp           # /proc/loadavg & /proc/stat reader implementation
    ├── memorycollector.hpp        # Memory collector interface and structs
    ├── memorycollector.cpp        # /proc/meminfo reader implementation
    ├── main.cpp                   # Application entry point and coordinator
    └── prac.md                    # Architecture and practice notes
```
