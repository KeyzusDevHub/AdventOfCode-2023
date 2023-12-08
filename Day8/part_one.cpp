#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>

int main(){
    std::string dest = "ZZZ";
    std::string current_loc = "AAA";
    std::string steps;
    std::map<std::string, std::pair<std::string, std::string>> desert_map;
    std::getline(std::cin, steps);
    std::string line;
    std::getline(std::cin, line);
    while(std::getline(std::cin, line)){
        line.erase(remove(line.begin(), line.end(), '='), line.end());
        line.erase(remove(line.begin(), line.end(), ','), line.end());
        line.erase(remove(line.begin(), line.end(), '('), line.end());
        line.erase(remove(line.begin(), line.end(), ')'), line.end());
        std::stringstream ss(line);
        std::string s, d_l, d_r;
        ss >> s >> d_l >> d_r;
        desert_map[s] = std::make_pair(d_l, d_r);
    }

    int steps_num = 0;
    while(current_loc != dest){
        char direction = steps[steps_num % steps.size()];
        if (direction == 'L'){
            current_loc = desert_map[current_loc].first;
        }
        else {
            current_loc = desert_map[current_loc].second;
        }
        steps_num++;
    }
    std::cout << steps_num << std::endl;
}