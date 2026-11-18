
#include "project/common.h"
#include <array>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <memory>

class Vehicle{
    public:
        std::string brand = "ford";
        std::string model = "Mustadng";
        Vehicle() {std::cout << " Create Vehicle\n";}
        // ~Vehicle() {std::cout << " Delete Vehicle\n";}

        virtual void honk(){
            std::cout << "Beep\n";
        }

        virtual ~Vehicle() {std::cout << " Delete Vehicle\n";}
};

class Car : public Vehicle{
    public:
        Car() {std::cout << " Create Car\n";}
        ~Car() {std::cout << " Delete Car\n";}

        std::string model = "Mustang";

        void honk() override {
            std::cout << model << " Beep Beep\n";
        }
};

int main(int, char**){
    std::cout << "Hello, from projects!\n";
    Vehicle * car = new Car();
    car->honk();
    std::cout << car->brand << " " << car->model<< std::endl;

    delete car;
    //

}

