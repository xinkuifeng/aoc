#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Point.h"

using namespace std;
using namespace fxk;

struct Elf {
    int id;
    Point p;

    Elf(int i) : id(i), p() {}
    Elf(int i, Point q) : id(i), p(q) {}
};

std::ostream & operator<<(std::ostream & os, const Elf & e) {
    os << "Elf " << e.id << ": " << e.p;
    return os;
}

vector<Elf> parse(string line, int i, int & id) {
    vector<Elf> vec;
    for (int j = 0; j < line.size(); ++j) {
        if (line[j] == '#') {
            Point p(i, j);
            vec.push_back(Elf(id++, p));
        }
    }
    return vec;
}

unordered_map<string, Point> g_directions = {
    {"N", Point(-1, 0)},
    {"S", Point(1, 0)},
    {"W", Point(0, -1)},
    {"E", Point(0, 1)},
    {"NW", Point(-1, -1)},
    {"NE", Point(-1, 1)},
    {"SW", Point(1, -1)},
    {"SE", Point(1, 1)},
};

void print_board(const unordered_map<int, Elf> & elves) {
    unordered_set<Point> st;
    int x_min = INT_MAX, x_max = INT_MIN;
    int y_min = INT_MAX, y_max = INT_MIN;
    for (const auto & kv : elves) {
        x_min = std::min(x_min, kv.second.p.x);
        x_max = std::max(x_max, kv.second.p.x);
        y_min = std::min(y_min, kv.second.p.y);
        y_max = std::max(y_max, kv.second.p.y);
        st.insert(kv.second.p);
    }

    for (int i = x_min; i <= x_max; ++i) {
        for (int j = y_min; j <= y_max; ++j) {
            Point p(i, j);
            if (st.find(p) != st.end()) {
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }

    int w = y_max - y_min + 1;
    int h = x_max - x_min + 1;
    int total = w * h;
    int free = total - elves.size();
    cout << "ans: " << free << endl;
}

bool should_move(const Elf & elf, const unordered_map<Point, vector<int>> & pos) {
    for (const auto & kv : g_directions) {
        auto diff = kv.second;
        auto p = elf.p + diff;
        if (pos.find(p) != pos.end()) return true;
    }
    return false;
}

bool simulation(
    unordered_map<int, Elf> & elves,
    unordered_map<Point, vector<int>> & pos,
    deque<vector<string>> & rules)
{
    // first half: propose move
    unordered_map<Point, vector<int>> tmp_pos;
    for (const auto & kv : elves) {
        auto r = rules;
        auto & elf = kv.second;
        bool go = should_move(elf, pos);
        while (!r.empty() && go) {
            auto dirs = r.front();
            r.pop_front();

            bool move = true;
            for (const auto & s : dirs) {
                auto diff = g_directions.at(s);
                auto p = elf.p + diff;
                if (pos.find(p) != pos.end()) {
                    move = false;
                    break;
                }
            }
            if (move) {
                auto diff = g_directions.at(dirs[0]);
                auto p = elf.p + diff;
                tmp_pos[p].push_back(elf.id);
                break;
            }
        }
    }

    // second half: update elves
    bool moved = false;
    for (const auto & kv : tmp_pos) {
        const auto & vec = kv.second;
        if (vec.size() > 1) continue;

        auto & elf = elves.at(vec[0]);
        elf.p = kv.first;
        moved = true;
    }

    // end: update positions
    unordered_map<Point, vector<int>> next_pos;
    for (const auto & kv : elves) {
        next_pos[kv.second.p].push_back(kv.first);
    }
    swap(pos, next_pos);
    auto vec = rules.front();
    rules.pop_front();
    rules.push_back(vec);

    return moved;
}

int main(int argc, char ** argv)
{
    cout << "Hello, World!" << endl;
    if (argc != 2) {
        cout << "usage: ./a.out FILE_NAME" << endl;
        return -1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cout << "failed to open " << argv[1] << endl;
        return -1;
    }

    int cnt = 0;
    unordered_map<int, Elf> elves;
    while (!file.eof()) {
        int row = 0;
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto vec = parse(line, row, cnt);
            ++row;
            for (const auto & elf : vec) {
                elves.insert({elf.id, elf});
            }
        }
    }

    cout << " == Initial State == " << endl;
    print_board(elves);

    // init
    deque<vector<string>> rules;
    rules.push_back({"N", "NE", "NW"});
    rules.push_back({"S", "SE", "SW"});
    rules.push_back({"W", "NW", "SW"});
    rules.push_back({"E", "NE", "SE"});

    unordered_map<Point, vector<int>> positions;
    for (const auto & kv : elves) {
        positions[kv.second.p].push_back(kv.second.id);
    }

    // running
    int round = 0;
    while (round < 10) {
        ++round;

        simulation(elves, positions, rules);
    }

    // end
    cout << " == End of Round " << round << " == " << endl;
    print_board(elves);

    return 0;
}
