#pragma once

//load -> 1m, 5m, 15m

struct CpuMetrices {
    double load1m{0.0};
    double load5m{0.0};
    double load15m{0.0};
};

class CpuCollector {
    public:
    CpuMetrices collect();
};
