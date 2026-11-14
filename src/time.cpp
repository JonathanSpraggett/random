

#include <chrono>
#include <iostream>
#include <thread>

int main() {
    using namespace std::chrono;

    // 1. Measure elapsed time (Control Loop Profiling)
    auto start = steady_clock::now();
    std::this_thread::sleep_for(milliseconds(10)); // Simulate work
    auto end = steady_clock::now();
    
    // Duration arithmetic — type-safe unit conversion
    auto elapsed_us = duration_cast<microseconds>(end - start).count();
    std::cout << "Loop took: " << elapsed_us << " µs\n";

    // 2. Deadline checking ("Did we miss our 10ms window?")
    constexpr auto DEADLINE = milliseconds(10);
    if ((end - start) > DEADLINE) {
        std::cerr << "[WARN] Control loop overran deadline!\n";
    }

    // 3. C++14 Duration Literals (cleaner syntax)
    auto timeout = 500ms;   // std::chrono::milliseconds(500)
    auto period  = 10us;    // std::chrono::microseconds(10)
    auto delay   = 2s;      // std::chrono::seconds(2)
}