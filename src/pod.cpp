#include <iostream>
#include <chrono>

// 1. POD Struct: Zero-overhead data bag
struct IMUPacket {
    double accel_x, accel_y, accel_z;
    std::chrono::steady_clock::time_point timestamp;
};

int main() {
    // 2. Aggregate Initialization
    auto now = std::chrono::steady_clock::now();
    IMUPacket data = {0.05, -9.81, 0.02, now};

    // 3. C++17 Structured Bindings: Immediate unpacking
    auto [ax, ay, az, time] = data;

    // Convert time to nanoseconds safely
    auto time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count();
    std::cout << "Gravity Vector Y: " << ay << " m/s^2 at T=" << time_ns << "ns\n";
}