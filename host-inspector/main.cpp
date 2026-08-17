#include <iostream>
#include <fstream>
#include <string>   // <-- Needed for string variables
#include <cstdint>  // <-- Needed for uint64_t (large numbers)

using namespace std;

int main()
{
    cout << "=======================================\n";
    cout << "     Linux Host Inspector (v1.0)       \n";
    cout << "=======================================\n";

    // 1. Open /proc/loadavg
    ifstream file("/proc/loadavg");
    if (!file.is_open())
    {
        cerr << "Error: Could not open /proc/loadavg\n";
        return 1;
    }

    // 2. Read the values
    double load1m, load5m, load15m;
    file >> load1m >> load5m >> load15m;

    // 3. Print the results
    cout << "[+] CPU Load (1m / 5m / 15m):\n";
    cout << "    " << load1m << " / " << load5m << " / " << load15m << "\n\n";

    
        // 4. Open /proc/meminfo to read RAM stats
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

    // Read /proc/meminfo word by word
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

    // 5. Calculate RAM Usage %
    double usedPercent = 0.0;
    if (totalMem > 0)
    {
        uint64_t usedMem = totalMem - availMem;
        usedPercent = (static_cast<double>(usedMem) / totalMem) * 100.0;
    }

    // 6. Print RAM results
    cout << "[+] RAM / Memory Usage:\n";
    cout << "    Total     : " << (totalMem / 1024.0 / 1024.0) << " GB\n";
    cout << "    Available : " << (availMem / 1024.0 / 1024.0) << " GB\n";
    cout << "    Used      : " << usedPercent << " %\n\n";
}
