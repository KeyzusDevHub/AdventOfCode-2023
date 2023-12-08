#include <iostream>
#include <vector>
#include <bits/stdc++.h>


int main(){
    long int time;
    long int distance;

    std::string line;

    std::getline(std::cin, line);
    std::string tmp;
    std::string tmp2;
    std::stringstream ss(line);
    ss >> tmp;
    while (ss >> tmp){
        tmp2 += tmp;
    }
    time = std::stol(tmp2);

    std::getline(std::cin, line);
    std::stringstream ss2(line);
    tmp2 = "";
    ss2 >> tmp;
    while (ss2 >> tmp){
        tmp2 += tmp;
    }
    distance = std::stol(tmp2);

    int options = 0;
    for (int i = 0; i < time; i++){
        if (i * (time - i) > distance){
            options++;
        }
    }
    std::cout << options << std::endl;
}