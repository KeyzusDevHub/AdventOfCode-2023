#include <iostream>
#include <bits/stdc++.h>
#include<algorithm>

int main(){
    int sum = 0;
    std::string line;

    while (getline(std::cin, line)){
        int min_red = 0;
        int min_green = 0;
        int min_blue = 0;

        std::stringstream ss(line);
        std::string part_one;
        std::string part_two;
        std::string gameID;

        ss >> part_one >> gameID;
        part_two.erase(remove(part_two.begin(), part_two.end(), ':'), part_two.end());

        while (ss >> part_one >> part_two){
            part_two.erase(remove(part_two.begin(), part_two.end(), ','), part_two.end());
            part_two.erase(remove(part_two.begin(), part_two.end(), ';'), part_two.end());
            
            if (part_two == "red" && stoi(part_one) > min_red){
                min_red = stoi(part_one);
            }
            else if (part_two == "green" && stoi(part_one) > min_green){
                min_green = stoi(part_one);
            }
            else if (part_two == "blue" && stoi(part_one) > min_blue){
                min_blue = stoi(part_one);
            }
        }
        sum += min_blue * min_green * min_red;
    }
    std::cout << sum << std::endl;
}