#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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

    int M = board.size();
    int N = board[0].size();
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            dfs(board, i, j, 'N');
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
