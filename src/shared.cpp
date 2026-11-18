#include <iostream>
#include <memory>
#include <string>

class Logger {
public:
    Logger() { std::cout << "Logger initialized.\n"; }
    ~Logger() { std::cout << "Logger destroyed.\n"; }
    
    void log(const std::string& msg) {
        std::cout << "[LOG]: " << msg << "\n";
    }
};

class Service {
private:
    std::shared_ptr<Logger> logger_; // Shared ownership
    std::string name_;

public:
    Service(std::string name, std::shared_ptr<Logger> logger)
        : name_(std::move(name)), logger_(std::move(logger)) {}

    void run() {
        logger_->log(name_ + " is running.");
    }
};

int main() {
    // Prefer std::make_shared over 'new' for better performance and exception safety
    std::shared_ptr<Logger> sharedLogger = std::make_shared<Logger>();
    std::cout << "Reference count: " << sharedLogger.use_count() << "\n"; // 1

    {
        Service authService("AuthService", sharedLogger);
        Service paymentService("PaymentService", sharedLogger);
        
        std::cout << "Reference count inside scope: " << sharedLogger.use_count() << "\n"; // 3
        authService.run();
        paymentService.run();
    } // authService and paymentService are destroyed here, decrementing count back to 1

    std::cout << "Reference count after scope: " << sharedLogger.use_count() << "\n"; // 1
    return 0;
} // sharedLogger goes out of scope; count hits 0 and Logger destructor runs