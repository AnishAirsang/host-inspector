#pragma once
#include <cstdint>

struct uptimemetrices
{
    double totalSeconds{0.0};

    int days() const { return static_cast<int>(totalSeconds) / 86400; }
    int hours() const { return (static_cast<int>(totalSeconds) % 86400) / 3600; }
    int minutes() const { return (static_cast<int>(totalSeconds) % 3600) / 60; }
    int seconds() const { return static_cast<int>(totalSeconds) % 60; }
};

class UptimeCollector
{
public:
    uptimemetrices collect();
};
