#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

std::vector<long int> new_seeds_location (std::vector<long int> seeds, std::vector<bool>& changed, long int start, long int dest, long int range){
    for (int i = 0; i < seeds.size(); i++){
        if (seeds[i] >= start && seeds[i] <= start + range && !changed[i]){
            seeds[i] -= start;
            seeds[i] += dest;
            changed[i] = true;
        }
    }
    return seeds;
}

int main(){
    std::vector<long int> seeds;
    std::string line;
    bool skip = false;

    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string tmp;
    ss >> tmp;
    while (ss >> tmp){
        seeds.push_back(std::stol(tmp));
    }
    std::vector<bool> changed(seeds.size(), false);

    while(std::getline(std::cin, line)){
        if (line == ""){
            skip = true;
            std::fill(changed.begin(), changed.end(), false);
        }
        else{
            long int start, dest, range;
            if(!skip){
                std::stringstream nums(line);
                nums >> dest >> start >> range;
                range--;
                seeds = new_seeds_location(seeds, changed, start, dest, range);
            }
            skip = false;
        }
    }
    auto min_value = *std::min_element(seeds.begin(), seeds.end());
    std::cout << min_value << std::endl;
}