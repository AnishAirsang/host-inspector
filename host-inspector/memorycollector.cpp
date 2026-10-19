#include "memorycollector.hpp" 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

MemoryMetrices MemoryCollector::collect()
{
    MemoryMetrices metrics;
    ifstream memFile("/proc/meminfo");
    if (!memFile.is_open())
    {
        cerr << "[!] Error: Could not open /proc/meminfo\n";
        return metrics;
    }
    string key;
    uint64_t value = 0;
    string unit;

    while (memFile >> key >> value >> unit)
    {
        if (key == "MemTotal:")
        {
            metrics.totalkb = value;
        }
        else if (key == "MemAvailable:")
        {
            metrics.availablekb = value;
        }
    }

    
    if (metrics.totalkb > 0)
    {
        uint64_t usedKb = metrics.totalkb - metrics.availablekb;
        metrics.usedPercent = (static_cast<double>(usedKb) / metrics.totalkb) * 100.0;
    }

    return metrics;
}
