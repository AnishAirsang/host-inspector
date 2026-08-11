#include <iostream>
#include <fstream> // For reading files

int main() {
    std::cout << "=======================================\n";
    std::cout << "     Linux Host Inspector (v1.0)       \n";
    std::cout << "=======================================\n";
    
    // 1. Open /proc/loadavg
    std::ifstream file("/proc/loadavg");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open /proc/loadavg\n";
        return 1;
    }
    
    // 2. Read the values
    double load1m, load5m, load15m;
    file >> load1m >> load5m >> load15m;
    
    // 3. Print the results
    std::cout << "[+] CPU Load (1m / 5m / 15m):\n";
    std::cout << "    " << load1m << " / " << load5m << " / " << load15m << "\n\n";
    
    return 0;
}
