#include <iostream>

bool search_symbol(std::string prev, std::string curr, std::string next, int pos, int max){
    bool to_return = true;
    int start = pos - 1;
    int len = 3;
    if (pos + 1 == max){
        len--;
    }
    if (start < 0){
        start++;
        len--;
    }
    std::string fragment = curr.substr(start, len);
    if (fragment.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890.") != std::string::npos){
        return true;
    }
    if (prev != ""){
        fragment = prev.substr(start, len);
        if (fragment.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890.") != std::string::npos){
            return true;
        }
    }
    if (next != ""){
        fragment = next.substr(start, len);
        if (fragment.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890.") != std::string::npos){
            return true;
        }
    }
    return false;
}

int main(){
    std::string line_prev = "";
    std::string line_curr = "";
    std::string line_next = "";
    int sum = 0;
    std::getline(std::cin, line_curr);
    bool run_next = true;
    while (std::getline(std::cin, line_next) || run_next){
        if (line_next == line_curr){
            run_next = false;
            line_next = "";
        }
        std::string tmp_num;
        bool should_count = false;
        for (int i = 0; i < line_curr.length(); i++){
            if (isdigit(line_curr[i])){
                tmp_num += line_curr[i];
                if (!should_count){
                    should_count = search_symbol(line_prev, line_curr, line_next, i, line_curr.length());
                } 
            }
            else {
                if (should_count){
                    sum += stoi(tmp_num);
                }
                tmp_num = "";
                should_count = false;
            }
            if (i + 1 == line_curr.length()){
                if (should_count){
                    sum += stoi(tmp_num);
                }
                tmp_num = "";
                should_count = false;
            }
        }
        std::string tmp = line_curr;
        line_curr = line_next;
        line_prev = tmp;
    }
    std::cout << sum << std::endl;
}