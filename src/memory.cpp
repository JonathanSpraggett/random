#include <memory_resource>
#include <vector>

void process_1000hz_control_loop() {
    // 1. Allocate a fixed memory buffer directly on the stack 
    std::array<std::byte, 1024> buffer; 
    
    // 2. Create a fast, lock-free memory resource mapped strictly to this buffer
    std::pmr::monotonic_buffer_resource memory_resource(buffer.data(), buffer.size());

    // 3. This vector will NEVER hit the OS heap (unless it exceeds 1024 bytes).
    // It safely reuses the deterministic stack buffer. Real-time guaranteed.
    std::pmr::vector<int> real_time_points{&memory_resource};
}