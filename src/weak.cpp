#include <iostream>
#include <memory>
#include <string>

class Player; // Forward declaration

class Guild {
public:
    std::string name;
    // Strong ownership: The Guild owns its member
    std::shared_ptr<Player> leader;

    Guild(std::string n) : name(n) {
        std::cout << "Guild " << name << " created.\n";
    }
    ~Guild() {
        std::cout << "Guild " << name << " destroyed.\n";
    }
};

class Player {
public:
    std::string username;
    // Weak reference: Breaks the circular dependency
    std::weak_ptr<Guild> guild;

    Player(std::string u) : username(u) {
        std::cout << "Player " << username << " created.\n";
    }
    ~Player() {
        std::cout << "Player " << username << " destroyed.\n";
    }

    void printGuild() {
        // Convert weak_ptr to shared_ptr before accessing members
        if (std::shared_ptr<Guild> g = guild.lock()) {
            std::cout << username << " belongs to " << g->name << ".\n";
        } else {
            std::cout << username << " has no active guild.\n";
        }
    }
};

int main() {
    {
        auto myGuild = std::make_shared<Guild>("Knights");
        auto myPlayer = std::make_shared<Player>("Arthur");

        myGuild->leader = myPlayer; // Reference count of myPlayer becomes 2
        myPlayer->guild = myGuild;  // Reference count of myGuild stays 1

        myPlayer->printGuild();
    } // Both objects go out of scope and are properly destroyed here

    return 0;
}