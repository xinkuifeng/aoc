#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Point.h"

using namespace std;
using namespace fxk;

struct Wind {
    int id;
    char c;
    Point p;

    Wind(int b, char d, Point q) : id(b), c(d), p(q) {}
};

std::ostream & operator<<(std::ostream & os, const Wind & w) {
    os << "Wind " << w.id << " " << w.c << ": " << w.p;
    return os;
}

vector<Wind> parse(string line, int i, int & id) {
    vector<Wind> vec;
    for (int j = 0; j < line.size(); ++j) {
        if (line[j] != '#' && line[j] != '.') {
            Point p(i, j);
            vec.push_back(Wind(id++, line[j], p));
        }
    }
    return vec;
}

unordered_map<string, Point> g_directions = {
    {"N", Point(-1, 0)},
    {"S", Point(1, 0)},
    {"W", Point(0, -1)},
    {"E", Point(0, 1)},
    {"Wait", Point(0, 0)},
};

unordered_map<char, Point> g_wind_dirs = {
    {'^', Point(-1, 0)},
    {'v', Point(1, 0)},
    {'<', Point(0, -1)},
    {'>', Point(0, 1)},
};

struct BoardInfo {
    int row;
    int col;
    Point start;
    Point end;
};

void move_wind(const BoardInfo & info, Wind & w) {
    auto diff = g_wind_dirs.at(w.c);
    w.p += diff;
    if (w.p.y > info.col - 2) {
        w.p.y = 1;
    }
    if (w.p.y < 1) {
        w.p.y = info.col - 2;
    }
    if (w.p.x > info.row - 2) {
        w.p.x = 1;
    }
    if (w.p.x < 1) {
        w.p.x = info.row - 2;
    }
}

void simulate_bliz(const BoardInfo & info, unordered_map<int, Wind> & bliz) {
    for (auto & kv : bliz) {
        move_wind(info, kv.second);
    }
}

void print_board(
    const BoardInfo & info,
    const unordered_map<int, Wind> & bliz,
    const Point & curr)
{
    vector<vector<char>> board = vector<vector<char>>(info.row, vector<char>(info.col, '.'));

    for (int j = 0; j < info.col; ++j) {
        board[0][j] = '#';
    }
    for (int j = 0; j < info.col; ++j) {
        board[info.row - 1][j] = '#';
    }
    for (int i = 0; i < info.row; ++i) {
        board[i][0] = '#';
    }
    for (int i = 0; i < info.row; ++i) {
        board[i][info.col - 1] = '#';
    }
    board[info.start.x][info.start.y] = '.';
    board[info.end.x][info.end.y] = '.';

    unordered_map<Point, int> counter;
    for (const auto & kv : bliz) {
        const auto & w = kv.second;
        counter[w.p]++;
        if (counter[w.p] == 1) {
            board[w.p.x][w.p.y] = w.c;
        } else {
            board[w.p.x][w.p.y] = '0' + counter[w.p];
        }
    }

    board[curr.x][curr.y] = 'E';

    for (const auto & vec : board) {
        for (const auto & c : vec) {
            cout << c;
        }
        cout << endl;
    }
}

bool valid(const BoardInfo & info, const Point & curr) {
    if (curr == info.start || curr == info.end) return true;

    if (curr.x <= 0 || curr.x >= info.row - 1 || curr.y <= 0 || curr.y >= info.col -1) {
        return false;
    }
    return true;
}

vector<Point> propose_moves(
    const BoardInfo & info,
    const unordered_set<Point> & st,
    const Point & curr)
{
    vector<Point> vec;
    for (const auto & kv : g_directions) {
        Point next = curr + kv.second;
        if (valid(info, next)) {
            if (st.find(next) == st.end()) {
                vec.push_back(next);
            }
        }
    }
    return vec;
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
    unordered_map<int, Wind> bliz;
    int col = 0;
    int row = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto vec = parse(line, row, cnt);
            for (const auto & w : vec) {
                bliz.insert({w.id, w});
            }

            ++row;
            col = line.size();
        }
    }

    BoardInfo info;
    info.start = Point(0, 1);
    info.end = Point(row - 1, col - 2);
    info.row = row;
    info.col = col;

    for (const auto & kv : bliz) {
        cout << kv.second << endl;
    }

    cout << " == Initial State == " << endl;
    print_board(info, bliz, info.start);

    Point curr = info.start;
    int round = 0;
    queue<Point> q;
    q.push(curr);
    bool reached = false;
    while (!reached && !q.empty()) {
        ++round;
        simulate_bliz(info, bliz);

        unordered_set<Point> forbidden;
        for (const auto & kv : bliz) {
            const auto & w = kv.second;
            forbidden.insert(w.p);
        }

        int size = q.size();
        unordered_set<Point> st;
        while (size--) {
            curr = q.front();
            q.pop();

            if (curr == info.end) {
                reached = true;
                break;
            }

            auto moves = propose_moves(info, forbidden, curr);
            for (const auto & move : moves) {
                st.insert(move);
            }
        }
        for (const auto & pos : st) {
            q.push(pos);
        }
    }

    cout << " == End of Round " << round << " == " << endl;
    print_board(info, bliz, curr);

    cout << "ans: " << round - 1 << endl;

    return 0;
}
