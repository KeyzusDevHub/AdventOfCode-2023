#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

bool all_same(std::vector<int> v){
    if (std::adjacent_find( v.begin(), v.end(), std::not_equal_to<>() ) == v.end() ){
        return true;
    }
    return false;
}


int last_extrapolated(std::vector<int> dataset){
    std::vector<std::vector<int>> extrapolations;
    extrapolations.push_back(dataset);
    std::vector<int> current = dataset;
    while(!all_same(current)){
        std::vector<int> tmp;
        for(int i = 1; i < current.size(); i++){
            int diff = current[i] - current[i - 1];
            tmp.push_back(diff);
        }
        extrapolations.push_back(tmp);
        current = tmp;
    }
    int extrapolated = 0;
    for (auto a : extrapolations){
        extrapolated += a[a.size() - 1];
    }
    return extrapolated;
}


int main(){
    std::string line;
    std::vector<std::vector<int>> datasets;
    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        int tmp;
        std::vector<int> ds;
        while (ss >> tmp){
            ds.push_back(tmp);
        }
        datasets.push_back(ds);
    }
    int sum = 0;
    for (auto a : datasets){
        sum += last_extrapolated(a);
    }
    std::cout << sum << std::endl;
}