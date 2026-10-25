# host-inspector

A C++ utility that reads Linux system metrics directly from the `/proc` virtual filesystem.

## Features

- CPU metrics: active utilization percentage calculated across a 200 ms sampling window from `/proc/stat`, plus 1, 5, and 15 minute load averages from `/proc/loadavg`.
- Memory stats: total, available, and used memory calculated from `/proc/meminfo` with gigabyte conversions.
- System uptime: elapsed seconds from `/proc/uptime`, converted into days, hours, minutes, and seconds.
- Standard library only: uses C++17 streams and RAII file handles without external packages.

## Requirements

- Linux with `/proc` mounted
- C++17 compiler (GCC 7+ or Clang 5+)
- CMake 3.16+ (optional)

## Build and run

### Using CMake

```bash
cmake -B build -S .
cmake --build build
./build/host_inspector
```

### Direct compilation with g++

```bash
g++ -std=c++17 -Wall -Wextra host-inspector/*.cpp -o host_inspector
./host_inspector
```

## Example output

```text
=======================================
     Linux Host Inspector (v2.3)       
=======================================
[+] CPU Metrics:
    Usage     : 10.3896 %
    Load avg  : 0.41 / 1.19 / 1.27

[+] RAM / Memory Usage:
    Total     : 6.99787 GB
    Available : 2.71944 GB
    Used      : 61.139 %

[+] System Uptime:
Total seconds: 75178.4s
Formatted: 0d 20h 52m 58s
```

## Kernel sources

The program gathers data through four virtual files:

- `/proc/stat`: sampled twice with a 200 ms sleep between reads. Active CPU percentage is computed by comparing total and idle tick deltas.
- `/proc/loadavg`: parsed for the 1, 5, and 15 minute system load averages.
- `/proc/meminfo`: parsed for `MemTotal` and `MemAvailable`. Used memory is derived by subtracting available memory from total memory.
- `/proc/uptime`: the first field provides total uptime in seconds. Modulo and division convert the raw seconds into days, hours, minutes, and seconds.

## Project layout

```text
host-inspector/
├── CMakeLists.txt                 # CMake configuration
├── README.md                      # Project documentation
├── .gitignore                     # Git ignore rules
└── host-inspector/
    ├── cpucollector.hpp           # CPU collector interface
    ├── cpucollector.cpp           # /proc/loadavg and /proc/stat parser
    ├── memorycollector.hpp        # Memory collector interface
    ├── memorycollector.cpp        # /proc/meminfo parser
    ├── uptimecollector.hpp        # Uptime collector interface
    ├── uptimecollector.cpp        # /proc/uptime parser
    ├── main.cpp                   # Entry point and terminal output
    └── prac.md                    # Architecture and practice notes
```
