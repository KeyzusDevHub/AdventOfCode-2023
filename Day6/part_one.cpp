#include <iostream>
#include <vector>
#include <bits/stdc++.h>


int main(){
    std::vector<int> times;
    std::vector<int> distances;

    std::string line;

    std::getline(std::cin, line);
    std::string tmp;
    std::stringstream ss(line);
    ss >> tmp;
    while (ss >> tmp){
        times.push_back(std::stoi(tmp));
    }

    std::getline(std::cin, line);
    std::stringstream ss2(line);
    ss2 >> tmp;
    while (ss2 >> tmp){
        distances.push_back(std::stoi(tmp));
    }
    int prod = 1;
    int options = 0;
    for (int i = 0; i < times.size(); i++){
        options = 0;
        for (int j = 0; j < times[i]; j++){
            if (j * (times[i] - j) > distances[i]){
                options++;
            }
        }
        prod *= options;
    }
    std::cout << prod << std::endl;
}