#include <iostream>
#include <string>

int main(){
    std::string line;
    int sum = 0;
    while (getline(std::cin, line)){
        int first = -1;
        int last = -1;
        for (auto a : line){
            if (std::isdigit(a)){
                if (first == -1){
                    first = a - '0';
                }
                else{
                    last = a - '0';
                }
            }
        }
        if (last == -1){
            last = first;
        }
        sum += first * 10 + last;
    }
    std::cout << sum << std::endl;
}