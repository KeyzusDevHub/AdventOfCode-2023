#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <climits>

class Segment{
    public:
        Segment(long int s, long int e){
            start = s;
            end = e;
        }

        long int min(){
            return start;
        }

        std::pair<long int, long int> segment(){
            return std::make_pair(start, end);
        }

        void data(){
            std::cout << "START: " << start << " END: " << end << std::endl;
        }

        std::pair<std::vector<Segment*>, Segment*> division(long int s, long int d, long int r){
            std::vector<Segment*> segments_unchecked;
            if (s > end || s + r < start){
                segments_unchecked.push_back(new Segment(start, end));
                return std::make_pair(segments_unchecked, nullptr);
            }
            else if (s <= end && s > start){
                if (s + r >= end){
                    segments_unchecked.push_back(new Segment(start, s - 1));
                    return std::make_pair(segments_unchecked, new Segment(d, end - s + d));
                }
                else{
                    segments_unchecked.push_back(new Segment(start, s - 1));
                    segments_unchecked.push_back(new Segment(s + r + 1, end));
                    return std::make_pair(segments_unchecked, new Segment(d, d + r));
                }
            }
            else if (s <= start && s + r >= start){
                if (s + r >= end){
                    return std::make_pair(segments_unchecked, new Segment(start - s + d, end - s + d));
                }
                else{
                    segments_unchecked.push_back(new Segment(s + r + 1, end));
                    return std::make_pair(segments_unchecked, new Segment(start - s + d, d + r));
                }
            }
            segments_unchecked.push_back(new Segment(start, end));
            return std::make_pair(segments_unchecked, nullptr);
        }

        ~Segment(){};

    private:
        long int start;
        long int end;
};

class SegmentControll{
    public:
        SegmentControll();
        SegmentControll(std::vector<std::pair<long int, long int>> seg_ranges) {
            for (auto a : seg_ranges){
                Segment* s = new Segment(a.first, a.first + a.second - 1);
                segments.push_back(s);
            }
        }

        void segments_step (std::vector<long int> starts, std::vector<long int> destinations, std::vector<long int> ranges){
            std::vector<Segment*> seg_checked;
            std::vector<Segment*> seg_unchecked = segments;
            std::vector<Segment*> tmp;
            for (int i = 0; i < starts.size(); i++){
                while (!seg_unchecked.empty()){
                    Segment* s = seg_unchecked.back();
                    std::pair<std::vector<Segment*>, Segment*> p = s->division(starts[i], destinations[i], ranges[i]);
                    seg_unchecked.pop_back();
                    if (p.second != nullptr){
                        seg_checked.push_back(p.second);
                    }
                    while (!p.first.empty()){
                        Segment* tmp_s = p.first.back();
                        tmp.push_back(tmp_s);
                        p.first.pop_back();
                    }
                    delete s;
                }
                seg_unchecked = tmp;
                tmp.clear();
            }
            segments.clear();
            segments = seg_checked;
            while(!seg_unchecked.empty()){
                Segment* s = seg_unchecked.back();
                segments.push_back(s);
                seg_unchecked.pop_back();
            }
        }

        long int getResult(){
            long int min = LONG_MAX;
            for (auto a : segments){
                if (a->min() < min){
                    min = a->min();
                }
            }
            return min;
        }

        ~SegmentControll(){
            while (!segments.empty()){
                delete segments.back();
                segments.pop_back();
            }
        }

    private:
        std::vector<Segment*> segments;
};

int main(){
    std::vector<std::pair<long int, long int>> seeds_input;
    std::vector<long int> starts;
    std::vector<long int> dests;
    std::vector<long int> ranges;

    std::string line;
    bool skip = false;

    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string tmp;
    ss >> tmp;
    long int s;
    long int s2;
    while (ss >> s >> s2){
        seeds_input.push_back(std::make_pair(s, s2));
    }
    SegmentControll* sc = new SegmentControll(seeds_input);

    while(std::getline(std::cin, line)){
        if (line == ""){
            skip = true;
            if (!starts.empty()){
                sc->segments_step(starts, dests, ranges);
            }
            starts.clear();
            dests.clear();
            ranges.clear();
        }
        else{
            long int start, dest, range;
            if(!skip){
                std::stringstream nums(line);
                nums >> dest >> start >> range;
                range--;
                dests.push_back(dest);
                starts.push_back(start);
                ranges.push_back(range);
            }
            skip = false;
        }
    }
    if (!starts.empty()){
        sc->segments_step(starts, dests, ranges);
    }

    std::cout << sc->getResult() << std::endl;
}