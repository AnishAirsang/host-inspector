#pragma once
#include <cstdint>

struct CpuMetrices
{
    double load1m{0.0};
    double load5m{0.0};
    double load15m{0.0};
    double usagePercent{0.0};
};

struct CpuSnapshot{
    uint64_t totalTicks{0};
    uint64_t idleTicks{0};
};
class CpuCollector {
    public:
        CpuMetrices collect();
  
    private:
        CpuSnapshot readStatSnapshot();
    };

