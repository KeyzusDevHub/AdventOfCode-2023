#include <iostream>
#include <sstream>
#include <vector>

bool empty_column(std::vector<std::vector<char>> data_input, int index){
    for (int i = 0; i < data_input.size(); i++){
        if (data_input[i][index] == '#'){
            return false;
        }
    }
    return true;
}

bool empty_row(std::vector<std::vector<char>> data_input, int index){
    for (int i = 0; i < data_input[0].size(); i++){
        if (data_input[index][i] == '#'){
            return false;
        }
    }
    return true;
}

long int sum_galaxies(std::vector<std::pair<int, int>> galaxies){
    long int sum = 0;
    for (int i = 0; i < galaxies.size(); i++){
        for (int j = i + 1; j < galaxies.size(); j++){
            sum += abs(galaxies[j].first - galaxies[i].first) + abs(galaxies[j].second - galaxies[i].second);
        }
    }
    return sum;
}

int main(){
    std::string line;
    std::vector<std::vector<char>> data_input;
    std::vector<std::pair<int, int>> galaxies;

    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        char c;
        std::vector<char> c_v;
        while (ss >> c){
            c_v.push_back(c);
        }
        data_input.push_back(c_v);
    }
    int real_row = 0, real_col = 0;
    for (int row = 0; row < data_input.size(); row++){
        if (!empty_row(data_input, row)){
            for (int col = 0; col < data_input[row].size(); col++){
                if (!empty_column(data_input, col)){
                    if (data_input[row][col] == '#'){
                        galaxies.push_back(std::make_pair(real_row, real_col));
                    }
                }
                else{
                    real_col += 999999;
                }
                real_col++;
            }
        }
        else{
            real_row += 999999;
        }
        real_row++;
        real_col = 0;
    }
    std::cout << sum_galaxies(galaxies) << std::endl;
}