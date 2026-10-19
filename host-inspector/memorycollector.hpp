#pragma once
#include <cstdint>

struct MemoryMetrices {
    uint64_t totalkb{0};
    uint64_t availablekb{0};
    double usedPercent{0.0};

    double totalGb() const{return totalkb / (1024.0 * 1024.0);}
    double availableGb() const{return availablekb / (1024.0 * 1024.0);}
};
class MemoryCollector {
    public:
    MemoryMetrices collect();
};