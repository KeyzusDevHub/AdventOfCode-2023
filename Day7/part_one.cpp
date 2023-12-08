#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>

class Hand{
    public:
        Hand(std::string c, int b){
            bid = b;
            cards = c;
        }

        int hand_strength() const{
            std::map<char, int> cards_num;
            for (auto a : cards){
                if (cards_num.count(a) > 0){
                    cards_num[a] += 1;
                }
                else{
                    cards_num[a] = 1;
                }
            }
            if (cards_num.size() == 1){
                return 7;
            }
            else if (cards_num.size() == 2 && (cards_num.begin()->second == 1 || cards_num.begin()->second == 4)){
                return 6;
            }
            else if (cards_num.size() == 2 && (cards_num.begin()->second == 2 || cards_num.begin()->second == 3)){
                return 5;
            }
            else if (cards_num.size() == 3){
                for(auto a : cards_num){
                    if (a.second == 3){
                        return 4;
                    }
                    else if (a.second == 2){
                        return 3;
                    }
                }
            }
            else if (cards_num.size() == 4){
                return 2;
            }
            else{
                return 1;
            }
            return 0;
        }

        int high_card(int index) const{
            std::map<char, int> t;
            t['A'] = 14;
            t['K'] = 13;
            t['Q'] = 12;
            t['J'] = 11;
            t['T'] = 10;
            char a = cards[index];
            if (std::isdigit(a)){
                return  a - '0';
            }
            else{
                return t[a];
            }
        }

        friend bool operator<(const Hand& l, const Hand& r){
            if (l.hand_strength() == r.hand_strength()){
                for (int i = 0; i < 5; i++){
                    if (l.high_card(i) != r.high_card(i)){
                        return l.high_card(i) < r.high_card(i);
                    }
                }
            }
            return l.hand_strength() < r.hand_strength();
        }

        friend bool operator>(const Hand& l, const Hand& r){
            return !(l < r);
        }

        int money(){
            return bid;
        }

        void data(){
            std::cout << cards << " " << bid << std::endl;
        }

        ~Hand(){};
    private:
        std::string cards;
        int bid;
};

int main(){
    std::vector<Hand> all_hands;
    std::vector<Hand*> all_hands_ptrs;
    std::string line;
    std::string card_data;
    int bid;
    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        ss >> card_data >> bid;
        Hand* h = new Hand(card_data, bid);
        all_hands.push_back(*h);
        all_hands_ptrs.push_back(h);
    }
    std::sort(all_hands.begin(), all_hands.end());
    int sum = 0;
    int rank = 1;
    for (auto a : all_hands){
        sum += rank * a.money();
        rank++;
    }
    std::cout << sum << std::endl;
    while (!all_hands_ptrs.empty()){
        Hand* tmp = all_hands_ptrs.back();
        delete tmp;
        all_hands_ptrs.pop_back();
    }
}