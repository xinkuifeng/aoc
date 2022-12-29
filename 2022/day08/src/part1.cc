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

bool on_boarder(const vector<vector<int>> & board, int x, int y) {
    int m = board.size();
    int n = board[0].size();

    return x <= 0 || x >= m - 1 || y <= 0 || y >= n - 1;
}

bool visible(const vector<vector<int>> & board, int x, int y) {
    static const vector<vector<int>> dirs{{0,1}, {0,-1}, {1,0}, {-1,0}};
    for (const auto & dir : dirs) {
        int i = x, j = y;
        bool can_see = true;
        while (!on_boarder(board, i, j)) {
            i += dir[0];
            j += dir[1];
            if (board[i][j] >= board[x][y]) {
                can_see = false;
                break;
            }
        }
        if (can_see) return true;
    }
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
