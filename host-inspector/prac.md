# Linux Host Inspector Notes

## What does the tool do?
-> Reads /proc/loadavg to get CPU load (1m, 5m, 15m)
-> Reads /proc/meminfo to get RAM stats (total, available, used %)

None of these are real files on the hard disk or SSD. They are stored in RAM.
They are live memory windows into your Linux kernel. Every time you open them, the kernel generates the current stats on the fly.

---

## What was wrong with v1 code?
Earlier, everything was dumped inside one single main() function:
1) Open CPU file
2) Read CPU values
3) Print CPU
4) Open RAM file
5) Read RAM values line by line
6) Do RAM math
7) Print RAM

Why is this bad?
The hotel analogy:
-> In a hotel, if one person takes orders, cooks food, washes dishes, collects cash, and does cleaning...
-> If 5 more people order at the same time, the person collapses and the system dies.
-> Same in code: If you want to add 10 more things later (network packets, disk I/O, temperature), main.cpp becomes an unreadable mess that is impossible to maintain.

---

## What did we do to solve this?
-> Used the Modular Collector Pattern (the same pattern used by Prometheus and Datadog).
-> Split the jobs out of main() into dedicated worker classes (collectors):
   - A worker (CpuCollector) for CPU stats
   - A worker (MemoryCollector) for RAM stats

---

## How we split the code into 3 files

### 1. cpucollector.hpp (The blueprint)
Tells the program what data to expect and what functions exist.

```cpp
#pragma once

// Struct: A custom box with 3 compartments for our numbers
struct CpuMetrices {
    double load1m{0.0};
    double load5m{0.0};
    double load15m{0.0};
};

// Class: The worker blueprint
class CpuCollector {
public:
    CpuMetrices collect();
};
```

Key points:
-> #pragma once stops duplicate inclusion errors.
-> struct CpuMetrices bundles the 3 load numbers into one package.
-> {0.0} zero-initializes the values so there is no garbage memory.

### 2. cpucollector.cpp (The worker)
Does the actual file reading and parsing.

```cpp
#include <iostream>
#include <fstream>
#include "cpucollector.hpp"
using namespace std;

CpuMetrices CpuCollector::collect() {
    CpuMetrices metrices; 

    ifstream file("/proc/loadavg");
    if (!file.is_open()) {
        cerr << "[!] Error: Failed to open /proc/loadavg\n";
        return metrices;
    }

    file >> metrices.load1m >> metrices.load5m >> metrices.load15m;
    return metrices;
}
```

Key points:
-> CpuCollector::collect() uses the scope resolution operator (::) to tell the compiler this function belongs to CpuCollector.
-> ifstream uses RAII. When the function returns, the file closes automatically. No memory leaks, no dangling file descriptors.
-> The >> operator skips spaces and converts ASCII text directly into numbers.

### 3. main.cpp (The manager)
main() no longer touches files or parsing. It just calls the worker:

```cpp
#include <iostream>
#include "cpucollector.hpp"
using namespace std;

int main() {
    CpuCollector cpuCol;
    CpuMetrices cpu = cpuCol.collect();

    cout << "[+] CPU Load (1m / 5m / 15m):\n";
    cout << "    " << cpu.load1m << " / " << cpu.load5m << " / " << cpu.load15m << "\n";
    return 0;
}
```

---

## Why did the compiler fail with "undefined reference"?
When clicking run in VS Code, it only ran:
g++ main.cpp -o main

In C++, compilation has two steps:
1) Compilation: g++ turns each .cpp into machine code (.o).
2) Linking: ld glues all the .o files together into the final executable.

Because cpucollector.cpp was not in the command, the linker could not find the code for CpuCollector::collect().

The fix:
Compile all .cpp files together:
g++ -std=c++17 -Wall -Wextra *.cpp -o main && ./main


//colors
ANSI 
So they star with special characaters, Escape Characters \033 -> octal
\x1B -> hex followed by [

    * \033[32m -> text to green
    yellow is 33m
    red is 31m 
    0m is reset that is they are normal text;

    void is a fxn that dosentt returny anything.
    

