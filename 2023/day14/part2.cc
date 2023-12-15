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

const unordered_map<char, vector<int>> g_go = {
    {'N', {-1, 0}},
    {'S', {1, 0}},
    {'E', {0, 1}},
    {'W', {0, -1}},
};

void print_board(const vector<string> & board) {
    for (const auto & s : board) {
        cout << s << endl;
    }
}

void print_rocks(const unordered_map<Point, Point> & rocks) {
    int i = 0;
    for (const auto & p : rocks) {
        cout << i++ << ":" << p.second << endl;
    }
}

void dfs(vector<string> & board, int x, int y, char dir) {
    const static int M = board.size();
    const static int N = board[0].size();

    if (x < 0 || x >= M || y < 0 || y >= N || board[x][y] != 'O') return;

    const auto & v = g_go.at(dir);
    int i = x + v[0];
    int j = y + v[1];
    if (i >= 0 && i < M && j >= 0 && j < N && board[i][j] == '.') {
        board[x][y] = '.';
        board[i][j] = 'O';
        dfs(board, i, j, dir);
    }
}

string to_string(const vector<string> & board) {
    stringstream ss;
    for (const auto & s : board) {
        ss << s;
    }
    return ss.str();
}

bool find_cycle(
    unordered_map<string, long> & snapshots,
    const vector<string> & board,
    long step,
    char dir,
    long & cycle
)
{
    auto idx = to_string(board) + to_string(dir);
    if (snapshots.find(idx) != snapshots.end()) {
        cycle = step - snapshots[idx];
        return true;
    } else {
        snapshots[idx] = step;
    }
    return false;
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
    int sum = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            board.push_back(line);
        }
    }
    cout << "before: " << endl;
    print_board(board);

    unordered_map<string, long> snapshots;
    int M = board.size();
    int N = board[0].size();
    long step = 0;
    long offset = 0;
    long cycle = 0;
    long target = 1000000000l * 4;
    bool found = false;
    while (step < target) {
        // North
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                dfs(board, i, j, 'N');
            }
        }
        ++step;
        if (!found && find_cycle(snapshots, board, step, 'N', cycle)) {
            cout << "offset: " << offset << "; cycle: " << cycle << endl;
            target = (target - step) % cycle;
            cout << "reduce target to: " << target << endl;
            step = 0;
            found = true;
        }
        // West
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < M; ++i) {
                dfs(board, i, j, 'W');
            }
        }
        ++step;
        if (!found && find_cycle(snapshots, board, step, 'W', cycle)) {
            cout << "offset: " << offset << "; cycle: " << cycle << endl;
            target = (target - step) % cycle;
            cout << "reduce target to: " << target << endl;
            step = 0;
            found = true;
        }
        // South
        for (int i = M - 1; i >= 0; --i) {
            for (int j = 0; j < N; ++j) {
                dfs(board, i, j, 'S');
            }
        }
        ++step;
        if (!found && find_cycle(snapshots, board, step, 'S', cycle)) {
            cout << "offset: " << offset << "; cycle: " << cycle << endl;
            target = (target - step) % cycle;
            cout << "reduce target to: " << target << endl;
            step = 0;
            found = true;
        }
        // East
        for (int j = N - 1; j >= 0; --j) {
            for (int i = 0; i < M; ++i) {
                dfs(board, i, j, 'E');
            }
        }
        ++step;
        if (!found && find_cycle(snapshots, board, step, 'E', cycle)) {
            cout << "offset: " << offset << "; cycle: " << cycle << endl;
            target = (target - step) % cycle;
            cout << "reduce target to: " << target << endl;
            step = 0;
            found = true;
        }
    }

    cout << "after: " << endl;
    print_board(board);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 'O') {
                sum += (M - i);
            }
        }
    }
    cout << "ans:" << sum << endl;

    return 0;
}
