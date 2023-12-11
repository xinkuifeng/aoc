#include <cassert>
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

const string g_dirs = "ESWN";

const unordered_map<char, vector<int>> g_go = {
    {'N', {-1, 0}},
    {'S', {1, 0}},
    {'E', {0, 1}},
    {'W', {0, -1}},
};

// in bounding
const unordered_map<char, vector<char>> g_d2p = {
    {'N', {'|', '7', 'F'}},
    {'S', {'|', 'L', 'J'}},
    {'E', {'-', '7', 'J'}},
    {'W', {'-', 'F', 'L'}},
};

// out bounding
const unordered_map<char, vector<char>> g_p2d = {
    {'|', {'N', 'S'}},
    {'-', {'W', 'E'}},
    {'F', {'S', 'E'}},
    {'7', {'S', 'W'}},
    {'J', {'N', 'W'}},
    {'L', {'N', 'E'}},
};

bool is_in(const vector<char> & vc, char c) {
    for (const auto & d : vc) {
        if (c == d) return true;
    }
    return false;
}

char change_dir(char cp, char cd) {
    if (cp == '-' || cp == '|') return cd;
    if (cp == 'F') {
        if (cd == 'N') return 'E';
        if (cd == 'W') return 'S';
        return cd;
    }
    if (cp == '7') {
        if (cd == 'E') return 'S';
        if (cd == 'N') return 'W';
        return cd;
    }
    if (cp == 'J') {
        if (cd == 'S') return 'W';
        if (cd == 'E') return 'N';
        return cd;
    }
    if (cp == 'L') {
        if (cd == 'W') return 'N';
        if (cd == 'S') return 'E';
        return cd;
    }
    assert(false);
}

bool can_move(char cp, char np, char cd) {
    const auto & dirs = g_p2d.at(cp);
    if (!is_in(dirs, cd)) return false;

    char nd = change_dir(cp, cd);
    const auto & pipes = g_d2p.at(nd);
    return is_in(pipes, np);
}

bool in_range(int M, int N, int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

void debug_board(const vector<string> & board) {
    for (const auto & str : board) {
        cout << str << endl;
    }
}

int main(int argc, char ** argv)
{
    if (argc != 2) {
        cout << "usage: ./a.out FILE_NAME" << endl;
        return -1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cout << "failed to open " << argv[1] << endl;
        return -1;
    }

    int row = 0;
    vector<string> maze;
    Point start_pos;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto col = line.find("S");
            if (col != string::npos) {
                start_pos.x = row;
                start_pos.y = col;
            }

            maze.push_back(line);
            ++row;
        }
    }

    cout << "start position: " << start_pos << endl;

    int ans = 0;
    int M = maze.size();
    int N = maze[0].size();
    vector<char> choices = {'|', '-', 'L', 'J', '7', 'F'};
    for (const auto & c : choices) {
        cout << "start with " << c << endl;
        maze[start_pos.x][start_pos.y] = c;

        unordered_set<Point> seen;
        queue<Point> q;
        q.push(start_pos);
        int level = -1;
        bool valid = true;
        while (!q.empty() && valid) {
            int size = q.size();
            while (size--) {
                auto curr_pos = q.front();
                q.pop();

                int conn = 0;
                char curr_c = maze[curr_pos.x][curr_pos.y];
                seen.insert(curr_pos);
                for (const auto & dir : g_dirs) {
                    const auto & v = g_go.at(dir);
                    int next_x = curr_pos.x + v[0];
                    int next_y = curr_pos.y + v[1];

                    if (!in_range(M, N, next_x, next_y)) continue;

                    auto next_pos = Point(next_x, next_y);
                    char next_c = maze[next_x][next_y];
                    if (can_move(curr_c, next_c, dir)) {
                        ++conn;
                        if (seen.find(next_pos) == seen.end()) q.push(next_pos);
                    }
                }
                if (conn != 2) {
                    cout << "error: it's not the main loop." << endl;
                    valid = false;
                    break;
                }
            }
            if (valid) ++level;
        }
        if (!valid) continue;

        cout << "farthest: " << level << endl;
        if (level > ans) ans = level;
    }

    cout << "ans:" << ans << endl;
    return 0;
}
