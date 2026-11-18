
#include "project/common.h"
#include <array>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <map>

#include <unordered_map>
#include <set>

int main(int, char**){
    std::cout << "Hello, from projects!\n";
    // vector<vector<int>> coordinates = {{0,0},{1,0},{-1,0}};
    // vector<vector<int>> coordinates = {{0,0},{0,1},{0,-1}};
    // vector<vector<int>> coordinates = {{0,0},{0,5},{5,5} ,{5,0}};
    // std::cout << std::boolalpha << checkStraightLine2(coordinates) << "\n";


    // vector
    std::vector<int> tmp ;
    tmp.reserve(1024);
    tmp.push_back(1);
    tmp.push_back(8);
    tmp.push_back(4);
    tmp.push_back(7);
    tmp.push_back(2);


    std::cout << "Vector" << std::endl;
    for (const auto& i: tmp){
        std::cout << i << "\n";
    }
    std::cout << "Vector pop" << std::endl;

    tmp.pop_back();
    for (const auto& i: tmp){
            std::cout << i << "\n";
        }

    std::sort(tmp.begin(), tmp.end());
    auto  tmpppp = std::find(tmp.begin(), tmp.end(), 4);
    std::cout << "Vector find" << std::endl;
    std::cout << *tmpppp << std::endl;

    if (tmpppp != tmp.end()) {
        int index =  std::distance(tmp.begin(), tmpppp);
        std::cout << index << std::endl;
    }
    else{
        std::cout << "not found" << std::endl;
    }

    std::cout << "Vector sort" << std::endl;
    for (const auto& i: tmp){
            std::cout << i << "\n";
    }

    std::cout << "array" << std::endl;
    // array
    std::array<int, 4> tmp2;
    tmp2[0] =1;
    tmp2[2] = 3;

    for ( const auto& i: tmp2){
        std::cout << i << "\n";
    }

    std::cout << "Deque" << std::endl;
    // deque
    std::deque<int> deq1;
    deq1.push_front(4);
    deq1.push_back(5);

    for (const auto& i : deq1){
        std::cout << i << std::endl;

    }

    //que
    std::cout << "Queue" << std::endl;
    std::queue<int> q1;
    q1.push(1);
    q1.push(8);
    q1.push(3);

    while(!q1.empty()) {
         std::cout << q1.front() << std::endl;
         q1.pop();
    }

    //stack
    std::cout << "stack" << std::endl;
    std::stack<int> st;
    st.push(0);
    st.push(8);
    st.push(3);

    while(!st.empty()){
        std::cout << st.top() << "  " << st.size() << std::endl;
        st.pop();
    }

    //map
    std::cout << "map" << std::endl;
    std::map<std::string, int> ma;
    ma["1"] = 4;
    ma["45"] = 8;
    ma["3"] = 0;

    for (const auto& [name,number]: ma){
        std::cout << name << "   " << number << std::endl;
    }

    if (ma.find("45") != ma.end()){
        std::cout << "\n45 in phone book.\n";
    }

    ma.erase("45");

    for (const auto& [name,number]: ma){
        std::cout << name << "   " << number << std::endl;
    }

    //unordered map
    std::cout << "unordered_map" << std::endl;

    std::unordered_map<std::string, int> uma;
    uma["1"] = 4;
    uma["45"] = 8;
    uma["3"] = 0;

    for (const auto& [name,number] : uma) {
        std::cout << name << "   " << number << std::endl;

    }
    if (uma.find("45") != uma.end()){
        std::cout << "\n45 in phone book.\n";
    }

    uma.erase("45");

    //set
    std::cout << "set" << std::endl;
    std::set<int> se;
    se.insert(1);
    se.insert(8);
    se.insert(4);
    se.insert(4);

    for (const auto& i: se){
        std::cout<< i <<std::endl;
    }
    se.erase(8);
    std::cout << "New size: " << se.size() << "\n";

    //
    std::cout << "set" << std::endl;
}

