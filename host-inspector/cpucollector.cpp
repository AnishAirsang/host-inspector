#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

#include "cpucollector.hpp"
using namespace std;

CpuMetrices CpuCollector::collect()
{
    CpuMetrices metrices;

    ifstream file("/proc/loadavg");
    if (!file.is_open())
    {
        cerr << "[!] Error: Failed to open /proc/loadavg\n";
        return metrices;
    }
    file >> metrices.load1m >> metrices.load5m >> metrices.load15m;
    file.close(); 

    CpuSnapshot snap1 = readStatSnapshot();

    this_thread::sleep_for(chrono::milliseconds(200));

    CpuSnapshot snap2 = readStatSnapshot();

    uint64_t deltaTotal = snap2.totalTicks - snap1.totalTicks;
    uint64_t deltaIdle = snap2.idleTicks - snap1.idleTicks;

    if (deltaTotal > 0)
    {
        uint64_t deltaActive = deltaTotal - deltaIdle;
        metrices.usagePercent = (static_cast<double>(deltaActive) / deltaTotal) * 100.0;
    }

    return metrices;
}

CpuSnapshot CpuCollector::readStatSnapshot()
{
    CpuSnapshot snapshot;

    ifstream file("/proc/stat");
    if (!file.is_open())
    {
        cerr << "[!] Error: Failed to open /proc/stat\n";
        return snapshot;
    }

    string label;
    uint64_t user{0}, nice{0}, system{0}, idle{0}, iowait{0};
    uint64_t irq{0}, softirq{0}, steal{0};

    file >> label >> user >> nice >> system >> idle >> iowait >> irq >> softirq >>
        steal;

    snapshot.idleTicks = idle + iowait;

    snapshot.totalTicks = user + nice + system + idle + iowait + irq + softirq + steal;

    return snapshot;
}
