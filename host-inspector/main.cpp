#include <iostream>
#include "cpucollector.hpp"
#include "memorycollector.hpp"
#include "uptimecollector.hpp"

using namespace std;

int main()
{
    cout << "=======================================\n";
    cout << "     Linux Host Inspector (v2.3)       \n";
    cout << "=======================================\n";

    CpuCollector cpuCol;
    CpuMetrices cpu = cpuCol.collect();
    cout << "[+] CPU Metrics:\n";
    cout << "    Usage     : " << cpu.usagePercent << " %\n";
    cout << "    Load avg  : " << cpu.load1m << " / " << cpu.load5m << " / " << cpu.load15m << "\n\n";

    MemoryCollector memCol;
    MemoryMetrices mem = memCol.collect();
    cout << "[+] RAM / Memory Usage:\n";
    cout << "    Total     : " << mem.totalGb() << " GB\n";
    cout << "    Available : " << mem.availableGb() << " GB\n";
    cout << "    Used      : " << mem.usedPercent << " %\n\n";

    UptimeCollector uptimecol;
    uptimemetrices uptime = uptimecol.collect();
    cout << "[+] System Uptime:\n";
    cout << "Total seconds: " << uptime.totalSeconds << "s\n";
    cout << "Formatted: " << uptime.days() << "d "
         << uptime.hours() << "h "
         << uptime.minutes() << "m "
         << uptime.seconds() << "s\n\n";

    return 0;
}
