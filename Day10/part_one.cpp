#include <iostream>
#include <vector>
#include <sstream>

enum Dirs{
    RIGTH,
    LEFT,
    UP,
    DOWN,
    NONE
};

class Pipe{
    public:
        Pipe(char symbol){
            start = false;
            if (symbol == '|'){
                possible_dirs.push_back(UP);
                possible_dirs.push_back(DOWN);
            }
            else if (symbol == '-'){
                possible_dirs.push_back(LEFT);
                possible_dirs.push_back(RIGTH);
            }
            else if (symbol == 'L'){
                possible_dirs.push_back(UP);
                possible_dirs.push_back(RIGTH);
            }
            else if (symbol == 'J'){
                possible_dirs.push_back(UP);
                possible_dirs.push_back(LEFT);
            }
            else if (symbol == '7'){
                possible_dirs.push_back(DOWN);
                possible_dirs.push_back(LEFT);
            }
            else if (symbol == 'F'){
                possible_dirs.push_back(DOWN);
                possible_dirs.push_back(RIGTH);
            }
            else if (symbol == 'S'){
                start = true;
            }
        }

        bool can_pass(Dirs d){
            for (auto a : possible_dirs){
                if (a == d){
                    return true;
                }
            }
            return false;
        }

        Dirs where_to_go(Dirs d){
            for (auto a : possible_dirs){
                if (a != d){
                    return a;
                }
            }
            return NONE;
        }

        bool is_start(){
            return start;
        }

        ~Pipe(){};
    private:
        std::vector<Dirs> possible_dirs;
        bool start;
};

bool find_loop(std::vector<std::vector<Pipe*>>& map, int row, int col, Dirs from){
    if (row < 0 || col < 0 || row >= map.size() || col >= map[0].size()){
        return false;
    }
    Pipe* p = map[row][col];
    if (p->is_start()){
        return true;
    }
    if (p->can_pass(from)){
        Dirs to_go = p->where_to_go(from);
        if (to_go == DOWN){
            return find_loop(map, row + 1, col, UP);
        }
        else if (to_go == UP){
            return find_loop(map, row - 1, col, DOWN);
        }
        else if (to_go == LEFT){
            return find_loop(map, row, col - 1, RIGTH);
        }
        else if (to_go == RIGTH){
            return find_loop(map, row, col + 1, LEFT);
        }
    }
    return false;
}

int count_loop(std::vector<std::vector<Pipe*>>& map, int row, int col, Dirs from){
    Pipe* p = map[row][col];
    int count = 0;
    while (!p->is_start()){
        Dirs to_go = p->where_to_go(from);
        if (to_go == DOWN){
            row++;
            from = UP;
        }
        else if (to_go == UP){
            row--;
            from = DOWN;
        }
        else if (to_go == LEFT){
            col--;
            from = RIGTH;
        }
        else if (to_go == RIGTH){
            col++;
            from = LEFT;
        }
        p = map[row][col];
        count++;
    }
    return count;
}

int main(){
    std::vector<std::vector<Pipe*>> map;
    int s_row, s_col;

    std::string line;
    char symbol;
    int row = 0;
    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        int col = 0;
        std::vector<Pipe*> p;
        while (ss >> symbol){
            if (symbol == 'S'){
                s_row = row;
                s_col = col;
            }
            p.push_back(new Pipe(symbol));
            col++;
        }
        map.push_back(p);
        row++;
    }
    int result = -1;
    if (find_loop(map, s_row - 1, s_col, DOWN)){
        result = count_loop(map, s_row - 1, s_col, DOWN);
    }
    else if (find_loop(map, s_row + 1, s_col, UP)){
        result = count_loop(map, s_row + 1, s_col, UP);
    }
    else if (find_loop(map, s_row, s_col - 1, RIGTH)){
        result = count_loop(map, s_row, s_col - 1, RIGTH);
    }
    else if (find_loop(map, s_row, s_col + 1, LEFT)){
        result = count_loop(map, s_row, s_col + 1, LEFT);
    }
    if (result % 2){
        result /= 2;
        result++;
    }
    else{
        result /= 2;
    }
    std::cout << result << std::endl;
}