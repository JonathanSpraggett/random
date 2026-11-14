#include <iostream>
#include <vector>
#include <string>
#include <map>

std::vector<std::string> names = {"Alice", "Bob", "Carol"};

//  const auto& — no copy, cannot accidentally modify
for (const auto& name : names) {
    std::cout << name << '\n';
}

//  auto& — modify elements in-place
for (auto& name : names) {
    name += "_processed";
}

//  Index loop — use size_t
for (std::size_t i = 0; i < names.size(); ++i) {
    std::cout << i << ": " << names[i] << '\n';
}

//  C++17 structured binding in range-for
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 88}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << '\n';
}

//  Safe hardware parsing loop with break/continue
while (true) {
    auto message = read_sensor_data();
    if (message.empty()) continue; // Skip bad reading
    if (message == "STOP") break;  // Exit loop safely
    process(message);
}

//  do-while — ideal for hardware polling or user validation
// Guarantees the code inside the loop runs AT LEAST ONCE before checking the condition.
int motor_speed;
do {
    std::cout << "Enter motor speed (0-100): ";
    std::cin >> motor_speed;
} while (motor_speed < 0 || motor_speed > 100);