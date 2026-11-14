#include <iostream>

enum class SystemState { BOOTING, ACTIVE, EMERGENCY_STOP, MAINTENANCE };

int main() {
    SystemState current_state = SystemState::ACTIVE;
    int battery_level = 15;

    // 1. C++17 if-init: 'is_low' exists only inside this if/else block
    if (bool is_low = (battery_level < 20); is_low) {
        current_state = SystemState::MAINTENANCE;
    }

    // 2. Clean State Switching
    switch (current_state) {
        case SystemState::BOOTING:
            std::cout << "System is warming up...\n";
            [[fallthrough]]; 
        case SystemState::ACTIVE:
            std::cout << "Mission in progress. Battery: " << battery_level << "%\n";
            break;
        case SystemState::EMERGENCY_STOP:
            std::cerr << "HALT: Mechanical failure detected!\n";
            break;
        case SystemState::MAINTENANCE:
            std::cout << "Heading to charging dock.\n";
            break;
    }
}