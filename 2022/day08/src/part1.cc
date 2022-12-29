#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> parse(const vector<string> & lines) {
    int m = lines.size();
    int n = lines[0].size();

    vector<vector<int>> board = vector<vector<int>>(m,  vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = lines[i][j] - '0';
        }
    }
    return board;
}

bool visible(const vector<vector<int>> & board, int x, int y) {
    int m = board.size();
    int n = board[0].size();

    bool north = true;
    for (int i = x - 1; i >= 0; --i) {
        if (board[i][y] >= board[x][y]) {
            north = false;
            break;
        }
    }
    if (north) return true;

    bool south = true;
    for (int i = x + 1; i < m; ++i) {
        if (board[i][y] >= board[x][y]) {
            south = false;
            break;
        }
    }
    if (south) return true;

    bool west = true;
    for (int i = y - 1; i >= 0; --i) {
        if (board[x][i] >= board[x][y]) {
            west = false;
            break;
        }
    }
    if (west) return true;

    bool east = true;
    for (int i = y + 1; i < n; ++i) {
        if (board[x][i] >= board[x][y]) {
            east = false;
            break;
        }
    }
    if (east) return true;

    return false;
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

    vector<string> lines;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            lines.push_back(line);
        }
    }

    auto board = parse(lines);
    int cnt = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (visible(board, i, j)) ++cnt;
        }
    }

    cout << "ans: " << cnt << endl;

    return 0;
}
