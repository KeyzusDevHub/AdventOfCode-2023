#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

enum Dirs{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NONE
};

class Pipe{
    public:
        Pipe(char symbol){
            if (symbol == '|'){
                possible_dirs.push_back(UP);
                possible_dirs.push_back(DOWN);
            }
            else if (symbol == '-'){
                possible_dirs.push_back(LEFT);
                possible_dirs.push_back(RIGHT);
            }
            else if (symbol == 'L'){
                possible_dirs.push_back(UP);
                possible_dirs.push_back(RIGHT);
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
                possible_dirs.push_back(RIGHT);
            }
            s = symbol;
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

        char symbol(){
            return s;
        }

        bool is_start(){
            return s == 'S';
        }

        ~Pipe(){};
    private:
        std::vector<Dirs> possible_dirs;
        char s;
};

class Point{
    public:
        Point(int x, int y){
            r = x;
            c = y;
        }

        bool operator==(const Point& p){
            return p.row() == r && p.col() == c;
        }

        int row() const{
            return r;
        }

        int col() const{
            return c;
        }

        ~Point(){};
    private:
        int r, c;
};

std::pair<bool, std::vector<Point>> find_loop(std::vector<std::vector<Pipe*>>& map, int row, int col, Dirs from, std::vector<Point> loop){
    if (row < 0 || col < 0 || row >= map.size() || col >= map[0].size()){
        loop.clear();
        return std::make_pair(false, loop);
    }
    Pipe* p = map[row][col];
    loop.push_back(Point(row, col));
    if (p->is_start()){
        return std::make_pair(true, loop);
    }
    if (p->can_pass(from)){
        Dirs to_go = p->where_to_go(from);
        if (to_go == DOWN){
            return find_loop(map, row + 1, col, UP, loop);
        }
        else if (to_go == UP){
            return find_loop(map, row - 1, col, DOWN, loop);
        }
        else if (to_go == LEFT){
            return find_loop(map, row, col - 1, RIGHT, loop);
        }
        else if (to_go == RIGHT){
            return find_loop(map, row, col + 1, LEFT, loop);
        }
    }
    loop.clear();
    return std::make_pair(false, loop);
}

bool check_if_inside(Point p, std::vector<Point> loop, std::vector<std::vector<Pipe*>>& map){
    int intersect = 0;
    int max_col = map[0].size();
    int max_row = map.size();
    bool one_line= false;
    for (int col = p.col(), row = p.row(); col < max_col && row < max_row ;col++, row++){
        if(std::find(loop.begin(), loop.end(), Point(row, col)) != loop.end()){
            if (map[row][col]->symbol() == 'L' || map[row][col]->symbol() == '7'){
                intersect++;
            }
            intersect++;
        }
    }
    return intersect % 2;
}

int count_inside(std::vector<std::vector<Pipe*>>& map, int row, int col, std::vector<Point> loop){
    int count = 0;
    for (int row = 0; row < map.size(); row++){
        for (int col = 0; col < map[0].size(); col++){
            if (!(std::find(loop.begin(), loop.end(), Point(row, col)) != loop.end())){
                if (check_if_inside(Point(row, col), loop, map)){
                    count++;
                }
            }
        }
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
    std::pair<bool, std::vector<Point>> ret;
    std::vector<Point> loop;
    loop.push_back(Point(s_row, s_col));
    if ((ret = find_loop(map, s_row - 1, s_col, DOWN, loop)).first){
        result = count_inside(map, s_row - 1, s_col, ret.second);
    }
    else if ((ret = find_loop(map, s_row + 1, s_col, UP, loop)).first){
        result = count_inside(map, s_row + 1, s_col, ret.second);
    }
    else if ((ret = find_loop(map, s_row, s_col - 1, RIGHT, loop)).first){
        result = count_inside(map, s_row, s_col - 1, ret.second);
    }
    else if ((ret = find_loop(map, s_row, s_col + 1, LEFT, loop)).first){
        result = count_inside(map, s_row, s_col + 1, ret.second);
    }
    std::cout << result << std::endl;
    
}