#include <iostream>
#include <optional>
#include <string_view>

// 1. Compile-time Configuration (Zero Runtime Cost)
struct BotSpecs {
    static constexpr std::string_view SERIAL = "TITAN-X1";
    static constexpr double CRITICAL_TEMP = 85.0;
};
// NOTE: `constexpr std::string` is NOT valid in C++17 because std::string
// allocates heap memory, which is forbidden in constexpr contexts.
// Use `constexpr std::string_view` for compile-time string constants.
// (C++20 adds constexpr allocator support, making `constexpr std::string` possible.)

// 2. Safe Sensor Handling with optional
std::optional<double> getCPUHeat() {
    bool is_sensor_working = false; // Simulated failure
    if (!is_sensor_working) return std::nullopt;
    return 42.5;
}

int main() {
    // 1. Explicit check
    auto current_heat = getCPUHeat();
    if (current_heat.has_value()) {
        std::cout << BotSpecs::SERIAL << " Temp: " << *current_heat << "C\n";
    } else {
        std::cerr << "[ERROR] Hardware failure on " << BotSpecs::SERIAL << '\n';
    }

    // 2. Elegant fallback using .value_or() (avoids boilerplate if/else)
    // Assume worst-case maximum heat if the hardware sensor fails to respond
    double safe_heat = current_heat.value_or(100.0); 
}