
#include "project/common.h"
#include <array>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <memory>

class Player{
    private:
        std::string name_;
        int health_;
    public:
        Player (std::string name, int health) : name_(std::move (name)), health_(health){
            std::cout << "Player created" << name_ <<std::endl;
        }

        ~Player() {
            std::cout << "Player destroyed" << name_ <<std::endl;

        }

        void attack() const {
            std::cout << name_ << " attacks! (HP: " << health_ << ")\n";
        }

};

void take(std::unique_ptr<Player> p){
    p->attack();
}

int main(int, char**){
    std::cout << "Hello, from projects!\n";
    std::unique_ptr<Player> p1 = std::make_unique<Player>("archer", 100);

    p1->attack();

    std::unique_ptr<Player> p2 = std::move(p1);

    if (!p1) {
        std::cout << "p1 is now null\n";
    }

    take(std::move(p2));
    std::cout << "End of main.\n";

    //
    std::cout << "set" << std::endl;
}

