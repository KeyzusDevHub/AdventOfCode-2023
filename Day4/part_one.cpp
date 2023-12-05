#include <iostream>
#include <vector>

int main(){
    std::vector<int> card;
    std::vector<int> winners;

    std::string line;
    int sum = 0;

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

        int card_value = 0;
        for (auto a : card){
            for (auto b : winners){
                if (a == b && card_value == 0){
                    card_value = 1;
                }
                else if (a == b){
                    card_value *= 2;
                }
            }
        }
        sum += card_value;
        card.clear();
        winners.clear();
    }
    std::cout << sum << std::endl;
}