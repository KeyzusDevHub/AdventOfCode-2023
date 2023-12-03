#include <iostream>
#include <algorithm>

bool search_number(std::string prev, std::string curr, std::string next, int pos, int max){
    int start = pos - 1;
    int len = 3;
    if (pos + 1 == max){
        len--;
    }
    if (start < 0){
        start++;
        len--;
    }
    std::string fragment1 = curr.substr(start, len);
    std::string fragment2 = "";
    std::string fragment3 = "";
    if (prev != ""){
        fragment2 = prev.substr(start, len);
    }
    if (next != ""){
        fragment3 = next.substr(start, len);
    }
    if (std::any_of(fragment1.begin(), fragment1.end(), ::isdigit) && std::any_of(fragment2.begin(), fragment2.end(), ::isdigit)){
        return true;
    }
    else if (std::any_of(fragment1.begin(), fragment1.end(), ::isdigit) && std::any_of(fragment3.begin(), fragment3.end(), ::isdigit)){
        return true;
    }
    else if (std::any_of(fragment2.begin(), fragment2.end(), ::isdigit) && std::any_of(fragment3.begin(), fragment3.end(), ::isdigit)){
        return true;
    }
    return false;
}

bool two_in_line(std::string line, int pos, int max){
    if (pos + 1 == max || pos == 0 || line == ""){
        return false;
    }
    if (isdigit(line[pos - 1]) && isdigit(line[pos + 1]) && !isdigit(line[pos])){
        return true;
    }
    return false;
}

int mult_two_in_line (std::string line, int pos){
    std::string tmp_num = "";
    int mult = 1;
    int index = pos - 1;
    while (isdigit(line[index])){
        tmp_num += line[index];
        index--;
    }
    std::reverse(tmp_num.begin(), tmp_num.end());
    std::cout << tmp_num << " ";
    mult *= stoi(tmp_num);

    index = pos + 1;
    tmp_num = "";
    
    while (isdigit(line[index])){
        tmp_num += line[index];
        index++;
    }
    std::cout << tmp_num << std::endl;
    mult *= stoi(tmp_num);
    return mult;
}

int extract_number (std::string line, int pos, int max){
    if (line == ""){
        return 1;
    }
    int start = pos - 3 > 0 ? pos - 3 : 0;
    int end = pos + 4 < max ? pos + 4 : max;
    std::string tmp_num = "";
    for (int i = start; i < end; i++){
        if (isdigit(line[i])){
            tmp_num += line[i];
        }
        else{
            if (i - 1 - int(tmp_num.length()) <= pos && i >= pos && tmp_num != ""){
                return stoi(tmp_num);
            }
            tmp_num = "";
        }
        if (i + 1 == end){
            if (i - int(tmp_num.length()) <= pos && i >= pos && tmp_num != ""){
                return stoi(tmp_num);
            }
        }
    }
    return 1;
}

int main(){
    std::string line_prev = "";
    std::string line_curr = "";
    std::string line_next = "";
    long int sum = 0;
    std::getline(std::cin, line_curr);
    bool run_next = true;
    while (std::getline(std::cin, line_next) || run_next){
        if (line_next == line_curr){
            run_next = false;
            line_next = "";
        }
        bool should_count = false;
        for (int i = 0; i < line_curr.length(); i++){
            if (line_curr[i] == '*'){
                should_count = search_number(line_prev, line_curr, line_next, i, line_curr.length());
                if (should_count){
                    std::cout << extract_number(line_prev, i, line_curr.length()) << " " << extract_number(line_curr, i, line_curr.length()) << " " << extract_number(line_next, i, line_curr.length()) << std::endl;
                    sum += extract_number(line_prev, i, line_curr.length()) * extract_number(line_curr, i, line_curr.length()) * extract_number(line_next, i, line_curr.length());
                }
                else if (two_in_line(line_prev, i, line_curr.length())){
                    sum += mult_two_in_line(line_prev, i);
                }
                else if (two_in_line(line_next, i, line_curr.length())){
                    sum += mult_two_in_line(line_next, i);
                }
                else if (two_in_line(line_curr, i, line_curr.length())){
                    sum += mult_two_in_line(line_curr, i);
                }
            }
        }
        std::string tmp = line_curr;
        line_curr = line_next;
        line_prev = tmp;
    }
    std::cout << sum << std::endl;
}