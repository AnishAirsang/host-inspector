#include <iostream>
#include "cpucollector.hpp"
#include "memorycollector.hpp"

using namespace std;

int main()
{
    cout << "=======================================\n";
    cout << "     Linux Host Inspector (v2.2)       \n";
    cout << "=======================================\n";

    // 1. CPU Collector
    CpuCollector cpuCol;
    CpuMetrices cpu = cpuCol.collect();
    cout << "[+] CPU Metrics:\n";
    cout << "    Usage     : " << cpu.usagePercent << " %\n";
    cout << "    Load avg  : " << cpu.load1m << " / " << cpu.load5m << " / " << cpu.load15m << "\n\n";

    // 2. Memory Collector
    MemoryCollector memCol;
    MemoryMetrices mem = memCol.collect();
    cout << "[+] RAM / Memory Usage:\n";
    cout << "    Total     : " << mem.totalGb() << " GB\n";
    cout << "    Available : " << mem.availableGb() << " GB\n";
    cout << "    Used      : " << mem.usedPercent << " %\n\n";

    return 0;
}
