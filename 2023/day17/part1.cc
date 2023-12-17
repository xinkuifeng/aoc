#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "Point.h"

using namespace std;
using namespace fxk;

const unordered_map<char, Point> g_go = {
    {'^', Point(-1, 0)},
    {'v', Point(1, 0)},
    {'>', Point(0, 1)},
    {'<', Point(0, -1)},
};

struct SuperPoint {
    Point pos;
    char head;
    int n;

    string to_string() const {
        stringstream ss;
        ss << pos << "+" << head << "+" << n;
        return ss.str();
    }

    void display(std::ostream & os) const {
        os << to_string();
    }
};

std::ostream & operator<<(std::ostream & os, const SuperPoint & sp) {
    sp.display(os);
    return os;
}

using pair_t = std::pair<int, SuperPoint>;

vector<char> compute_dirs(const SuperPoint & sp) {
    vector<char> dirs;
    if (sp.head == '>') {
        dirs.push_back('^');
        dirs.push_back('v');
        if (sp.n < 3) {
            dirs.push_back('>');
        }
    } else if (sp.head == '<') {
        dirs.push_back('^');
        dirs.push_back('v');
        if (sp.n < 3) {
            dirs.push_back('<');
        }
    } else if (sp.head == 'v') {
        dirs.push_back('<');
        dirs.push_back('>');
        if (sp.n < 3) {
            dirs.push_back('v');
        }
    } else if (sp.head == '^') {
        dirs.push_back('<');
        dirs.push_back('>');
        if (sp.n < 3) {
            dirs.push_back('^');
        }
    }
    assert(!dirs.empty());
    return dirs;
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

    vector<string> board;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            board.push_back(line);
        }
    }

    int M = board.size();
    int N = board[0].size();
    Point start_pos(0, 0);
    Point end_pos(M - 1, N - 1);

    // put the small value at the top
    auto rule = [](const pair_t & p1, const pair_t & p2) {
        return p1.first > p2.first;
    };
    priority_queue<pair_t, vector<pair_t>, decltype(rule)> pq(rule);
    SuperPoint sp;
    sp.pos = start_pos;
    sp.head = '>';
    sp.n = 1;
    pq.push({0, sp});

    unordered_set<string> seen;
    int sum = 0;
    while (!pq.empty()) {
        auto kv = pq.top();
        pq.pop();

        auto heat = kv.first;
        auto sp = kv.second;
        if (seen.find(sp.to_string()) != seen.end()) continue;

        if (sp.pos == end_pos) {
            sum = heat;
            break;
        }

        auto dirs = compute_dirs(sp);
        for (const auto dir : dirs) {
            const auto & diff = g_go.at(dir);
            SuperPoint np;
            np.pos = sp.pos + diff;
            int x = np.pos.x;
            int y = np.pos.y;
            if (x < 0 || x >= M || y < 0 || y >= N) continue;

            np.head = dir;
            np.n = sp.n;
            if (sp.head != dir) {
                np.n = 1;
            } else {
                np.n += 1;
            }
            if (seen.find(np.to_string()) != seen.end()) continue;

            int h = heat + (board[x][y] - '0');
            pq.push({h, np});
        }
        seen.insert(sp.to_string());
    }

    cout << "ans:" << sum << endl;

    return 0;
}
