#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>
#include <unordered_map>





enum class Dir {north, east, west, south};
bool isRobotBounded(std::string instructions) {
        std::unordered_map<Dir, std::unordered_map<char, Dir>> compute_rotate;
        compute_rotate[Dir::north]['L'] = Dir::west;
        compute_rotate[Dir::north]['R'] = Dir::east;
        compute_rotate[Dir::east]['L'] = Dir::north;
        compute_rotate[Dir::east]['R'] = Dir::south;
        compute_rotate[Dir::west]['L'] = Dir::south;
        compute_rotate[Dir::west]['R'] = Dir::north;
        compute_rotate[Dir::south]['L'] = Dir::east;
        compute_rotate[Dir::south]['R'] = Dir::west;


        


        int x = 0, y = 0;

        Dir current_dir = Dir::north;


        for (const auto& i : instructions){
            // std::cout << i << std::endl;
            if (i == 'G') {
                switch (current_dir){
                    case Dir::north:
                        y+=1;
                        break;
                    case Dir::east:
                        x+=1;
                        break;
                    case Dir::west:
                        x-=1;
                        break;
                    case Dir::south:
                        y-=1;
                        break;
                    }
            }
            else {
                current_dir = compute_rotate[current_dir][i];
            }

        }
        
        std::cout << x << " " << y << "  " << static_cast<int>(current_dir) << std::endl;


        if (current_dir == Dir::north){
            if (x == 0 && y == 0){
                return true;
            }

        }
        else if (current_dir == Dir::south){
            return true;
          
        }

        else if (current_dir == Dir::east){
             return true;
            // if (x == 0 && y == 0){
            //     return true;
            // }
        }

        else if (current_dir == Dir::west){
             return true;
            // if (x == 0 && y == 0){
            //     return true;
            // }
        }
        return false;
    }

int main(int, char**){
   
    std::cout << std::boolalpha << isRobotBounded("GGLLGG") << std::endl;
    std::cout << std::boolalpha << isRobotBounded("GL") << std::endl;
    std::cout << std::boolalpha << isRobotBounded("GG") << std::endl;

    std::cout << std::boolalpha << isRobotBounded("LLGRL") << std::endl;
        

}

