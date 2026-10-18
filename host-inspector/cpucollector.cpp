#include <iostream>
#include <fstream>
#include "cpucollector.hpp"
using namespace std;

CpuMetrices CpuCollector::collect(){
    CpuMetrices metrices; 


    
    ifstream file("/proc/loadavg");
    if(!file.is_open()){
        cerr << "[!] Error: Failed to open /proc/loadavg\n";
        return metrices;
    }
    file >> metrices.load1m >> metrices.load5m >> metrices.load15m;
    return metrices;
}