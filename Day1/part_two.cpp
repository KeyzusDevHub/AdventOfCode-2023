#include <iostream>
#include <string>
#include <map>

int main(){
    std::string line;
    std::map<std::string, int> numbers = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
                                          {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    int sum = 0;
    while (std::getline(std::cin, line)){
        int first = -1;
        int first_index = -1;
        int last = -1;
        int last_index = -1;
        int index = 0;

        for (auto a : line){
            if (std::isdigit(a)){
                if (first == -1){
                    first = a - '0';
                    first_index = index;
                }
                else{
                    last = a - '0';
                    last_index = index;
                }
            }
            index++;
        }

        if (last_index == -1){
            last = first;
            last_index = first_index;
        }

        for(std::map<std::string,int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
            if (line.find(it->first) < first_index || first_index == -1){
                first = it->second;
                first_index = line.find(it->first);
            }
        }

        if (last_index == -1){
            last = first;
            last_index = first_index;
        }

        for(std::map<std::string, int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
            if (line.find(it->first, last_index) < line.length()){
                last = it->second;
                last_index = line.find(it->first, last_index) + 1;
                it = numbers.begin();
            }
        }
        sum += first * 10 + last;
    }
    std::cout << sum << std::endl;
}