#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

void new_seeds_location (std::vector<long int>& seeds, std::vector<bool>& checked, long int start, long int dest, long int range){
    for (long int i = 0; i < seeds.size(); i++){
        if (!checked[i] && seeds[i] >= start && seeds[i] <= start + range){
            seeds[i] -= start;
            seeds[i] += dest;
            checked[i] = true;
        }
    }
}

long int return_minimal_from_range(int start, int range, std::vector<std::vector<long int>> dsr){
    std::vector<long int> seeds;
    for (int i = 0; i < range; i++){
        seeds.push_back(start + i);
    }
    std::vector<bool> checked(seeds.size(), false);
    bool go_inside = true;
    for (int i = 0; i < dsr.size(); i++){
        if (dsr[i][0] == -1 && dsr[i][1] == -1 && dsr[i][2] == -1){
            std::fill(checked.begin(), checked.end(), false);
            go_inside = true;
        }
        else if (go_inside){
            new_seeds_location(seeds, checked, dsr[i][1], dsr[i][0], dsr[i][2]);
        }
    }
    auto min_value = *std::min_element(seeds.begin(), seeds.end());
    return min_value;
}

int main(){
    std::vector<long int> seeds_input;
    std::vector<long int> minimals;
    std::vector<std::vector<long int>> dsr;
    std::string line;
    bool skip = false;

    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string tmp;
    ss >> tmp;
    int s;
    while (ss >> s){
        seeds_input.push_back(s);
    }

    while(std::getline(std::cin, line)){
        if (line == ""){
            skip = true;
            std::vector<long int> tmp;
            tmp.push_back(-1);
            tmp.push_back(-1);
            tmp.push_back(-1);
            dsr.push_back(tmp);
        }
        else{
            long int start, dest, range;
            if(!skip){
                std::stringstream nums(line);
                nums >> dest >> start >> range;
                range--;
                std::vector<long int> tmp;
                tmp.push_back(dest);
                tmp.push_back(start);
                tmp.push_back(range);
                dsr.push_back(tmp);
            }
            skip = false;
        }
    }

    for (int i = 0; i < seeds_input.size(); i += 2){
        minimals.push_back(return_minimal_from_range(seeds_input[i], seeds_input[i + 1], dsr));
    }
    auto min_value = *std::min_element(minimals.begin(), minimals.end());
    std::cout << min_value << std::endl;
}