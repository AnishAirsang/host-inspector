#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "cpucollector.hpp"

using namespace std;

int main()
{
    cout << "=======================================\n";
    cout << "     Linux Host Inspector (v2.0)       \n";
    cout << "=======================================\n";

    // 1. Modular CPU Collector
    CpuCollector cpuCol;
    CpuMetrices cpu = cpuCol.collect();
    cout << "[+] CPU Load (1m / 5m / 15m):\n";
    cout << "    " << cpu.load1m << " / " << cpu.load5m << " / " << cpu.load15m << "\n\n";

    // 2. RAM stats (we will modularize this next into MemoryCollector!)
    ifstream memFile("/proc/meminfo");
    if (!memFile.is_open())
    {
        cerr << "Error: Could not open /proc/meminfo\n";
        return 1;
    }

    string key;
    uint64_t value;
    string unit;

    uint64_t totalMem = 0;
    uint64_t availMem = 0;

    while (memFile >> key >> value >> unit)
    {
        if (key == "MemTotal:")
        {
            totalMem = value;
        }
        else if (key == "MemAvailable:")
        {
            availMem = value;
        }
    }

    double usedPercent = 0.0;
    if (totalMem > 0)
    {
        uint64_t usedMem = totalMem - availMem;
        usedPercent = (static_cast<double>(usedMem) / totalMem) * 100.0;
    }

    cout << "[+] RAM / Memory Usage:\n";
    cout << "    Total     : " << (totalMem / 1024.0 / 1024.0) << " GB\n";
    cout << "    Available : " << (availMem / 1024.0 / 1024.0) << " GB\n";
    cout << "    Used      : " << usedPercent << " %\n\n";

    return 0;
}
