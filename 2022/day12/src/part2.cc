#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "Point.h"

using namespace fxk;
using namespace std;

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

    vector<string> board;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            board.push_back(line);
        }
    }

    Point start;
    int M = board.size();
    int N = board[0].size();
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 'S') {
                board[i][j] = 'a';
            } else if (board[i][j] == 'E') {
                start = Point(i, j);
                board[i][j] = 'z';
            }
        }
    }

    int level = 0;
    bool stop = false;
    queue<Point> q;
    unordered_set<Point> visited;
    q.push(start);
    visited.insert(start);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto p = q.front();
            q.pop();

            if (board[p.x][p.y] == 'a') {
                stop = true;
                break;
            }
            static vector<Point> dirs = {Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1)};
            for (const auto & d : dirs) {
                Point next = p + d;
                if (next.x < 0 || next.x >= M || next.y < 0 || next.y >= N) continue;
                if (board[next.x][next.y] - board[p.x][p.y] < -1) continue;
                if (visited.find(next) != visited.end()) continue;

                visited.insert(next);
                q.push(next);
            }
        }
        if (stop) break;
        ++level;
    }

    cout << "ans: " << level << endl;

    return 0;
}
