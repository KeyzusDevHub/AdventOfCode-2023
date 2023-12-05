#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <numeric>

int main(int argc, char* argv[]){
    if (argc < 2){
        exit(-1);
    }
    std::ifstream inFile(argv[1]); 
    int cards_num = std::count(std::istreambuf_iterator<char>(inFile), 
             std::istreambuf_iterator<char>(), '\n') + 1;

    std::vector<int> cards_number(cards_num, 1);

    std::vector<int> card;
    std::vector<int> winners;

    std::string line;
    int card_index = 0;

    while(std::getline(std::cin, line)){
        int index = 0;
        std::string tmp_num = "";
        while (line[index] != ':'){
            index++;
        }
        bool to_card = true;
        while(index != line.length()){
            if (isdigit(line[index])){
                tmp_num += line[index];
                if (index + 1 == line.length()){
                    winners.push_back(std::stoi(tmp_num));
                }
            }
            else if (line[index] == '|'){
                to_card = false;
            }
            else{
                if (tmp_num != ""){
                    if (to_card){
                        card.push_back(std::stoi(tmp_num));
                    }
                    else{
                        winners.push_back(std::stoi(tmp_num));
                    }
                }
                tmp_num = "";
            }
            index++;
        }

        int tmp_idx = card_index + 1;
        for (auto a : card){
            for (auto b : winners){
                if (a == b){
                    cards_number[tmp_idx] += cards_number[card_index];
                    tmp_idx++;
                }
            }
        }
        card.clear();
        winners.clear();
        card_index++;
    }
    auto sum = std::reduce(cards_number.begin(), cards_number.end());
    std::cout << sum << std::endl;
}