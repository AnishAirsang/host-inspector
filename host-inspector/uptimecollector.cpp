#include <iostream>
#include <fstream>
#include "uptimecollector.hpp"
using namespace std;

uptimemetrices UptimeCollector::collect()
{
    uptimemetrices metrics;

    ifstream file("/proc/uptime");
    if (!file.is_open())
    {
        cerr << "[!] Error: Failed to open /proc/uptime\n";
        return metrics;
    }
    file >> metrics.totalSeconds;
    return metrics;
}
