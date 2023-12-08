#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>

long int gcd(long int a, long int b)
{
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
}
 
long int lcm_find(std::vector<long int> nums){
    long int lcm = -1;
 
    for (auto a : nums){
        if (lcm == -1){
            lcm = a;
        }
        else{
            lcm = (((a * lcm)) / (gcd(a, lcm)));
        }
    }
 
    return lcm;
}

int main(){
    std::vector<std::string> current_locs;
    std::string steps;
    std::map<std::string, std::pair<std::string, std::string>> desert_map;
    std::getline(std::cin, steps);
    std::string line;
    std::getline(std::cin, line);
    while(std::getline(std::cin, line)){
        line.erase(remove(line.begin(), line.end(), '='), line.end());
        line.erase(remove(line.begin(), line.end(), ','), line.end());
        line.erase(remove(line.begin(), line.end(), '('), line.end());
        line.erase(remove(line.begin(), line.end(), ')'), line.end());
        std::stringstream ss(line);
        std::string s, d_l, d_r;
        ss >> s >> d_l >> d_r;
        if (s[s.size() - 1] == 'A'){
            current_locs.push_back(s);
        }
        desert_map[s] = std::make_pair(d_l, d_r);
    }

    std::vector<long int> to_lcm;
    for(auto a : current_locs){
        std::string first_ap = "NONE";
        std::string curr = a;
        long int steps_num = 0;
        bool to_change = false;
        while (curr != first_ap){
            char direction = steps[steps_num % steps.size()];
            if (to_change){
                first_ap = curr;
                to_change = false;
            }
            if (direction == 'L'){
                curr = desert_map[curr].first;
            }
            else {
                curr = desert_map[curr].second;
            }
            if (curr[curr.size() - 1] == 'Z'){
                to_change = true;
            }
            steps_num++;
        }
        to_lcm.push_back(steps_num / 2);
    }
    std::cout << lcm_find(to_lcm) << std::endl;
}