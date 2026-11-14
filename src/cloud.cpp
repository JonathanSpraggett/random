#include <iostream>
#include <vector>

int main() {
    // 1. A simulated Lidar point cloud (Distances in meters)
    std::vector<double> scan = {1.2, 0.5, 15.0, 0.1, 4.2};
    std::vector<double> filtered_scan;
    
    // 2. Optimization: Pre-allocate memory
    filtered_scan.reserve(scan.size());

    // 3. Clean Range-for with read-only constraint
    for (const auto& distance : scan) {
        if (distance > 0.2) { // Minimum safety standoff
            filtered_scan.push_back(distance);
        }
    }

    std::cout << "Filtered " << (scan.size() - filtered_scan.size()) << " noise points.\n";
}