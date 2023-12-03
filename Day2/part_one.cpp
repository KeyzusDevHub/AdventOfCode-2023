#include <iostream>
#include <bits/stdc++.h>
#include<algorithm>

int main(){
    int red_max = 12;
    int green_max = 13;
    int blue_max = 14;
    int sum = 0;
    std::string line;

    while (getline(std::cin, line)){
        std::stringstream ss(line);
        std::string part_one;
        std::string part_two;
        std::string gameID;
        bool ok = true;
        ss >> part_one >> gameID;
        part_two.erase(remove(part_two.begin(), part_two.end(), ':'), part_two.end());
        while (ss >> part_one >> part_two){
            part_two.erase(remove(part_two.begin(), part_two.end(), ','), part_two.end());
            part_two.erase(remove(part_two.begin(), part_two.end(), ';'), part_two.end());
            if (part_two == "red" && stoi(part_one) > red_max){
                ok = false;
            }
            else if (part_two == "green" && stoi(part_one) > green_max){
                ok = false;
            }
            else if (part_two == "blue" && stoi(part_one) > blue_max){
                ok = false;
            }
        }
        if (ok){
            sum += stoi(gameID);
        }
    }
    std::cout << sum << std::endl;
}