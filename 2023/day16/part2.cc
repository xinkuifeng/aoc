#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_board(const vector<string> & board) {
    for (const auto & s : board) {
        cout << s << endl;
    }
}

void dfs(
    vector<string> & board,
    vector<string> & seen,
    int x,
    int y,
    char beam
)
{
    const static int M = board.size();
    const static int N = board[0].size();
    if (x < 0 || x >= M || y < 0 || y >= N || seen[x][y] == beam) return;

    char ch = board[x][y];
    seen[x][y] = beam;
    if (beam == '>') {
        if (ch == '|') {
            dfs(board, seen, x - 1, y, '^');
            dfs(board, seen, x + 1, y, 'v');
        } else if (ch == '-') {
            dfs(board, seen, x, y + 1, '>');
        } else if (ch == '\\') {
            dfs(board, seen, x + 1, y, 'v');
        } else if (ch == '/') {
            dfs(board, seen, x - 1, y, '^');
        } else {
            dfs(board, seen, x, y + 1, '>');
        }
    } else if (beam == '^') {
        if (ch == '|') {
            dfs(board, seen, x - 1, y, '^');
        } else if (ch == '-') {
            dfs(board, seen, x, y + 1, '>');
            dfs(board, seen, x, y - 1, '<');
        } else if (ch == '\\') {
            dfs(board, seen, x, y - 1, '<');
        } else if (ch == '/') {
            dfs(board, seen, x, y + 1, '>');
        } else {
            dfs(board, seen, x - 1, y, '^');
        }
    } else if (beam == 'v') {
        if (ch == '|') {
            dfs(board, seen, x + 1, y, 'v');
        } else if (ch == '-') {
            dfs(board, seen, x, y + 1, '>');
            dfs(board, seen, x, y - 1, '<');
        } else if (ch == '\\') {
            dfs(board, seen, x, y + 1, '>');
        } else if (ch == '/') {
            dfs(board, seen, x, y - 1, '<');
        } else {
            dfs(board, seen, x + 1, y, 'v');
        }
    } else if (beam == '<') {
        if (ch == '|') {
            dfs(board, seen, x - 1, y, '^');
            dfs(board, seen, x + 1, y, 'v');
        } else if (ch == '-') {
            dfs(board, seen, x, y - 1, '<');
        } else if (ch == '\\') {
            dfs(board, seen, x - 1, y, '^');
        } else if (ch == '/') {
            dfs(board, seen, x + 1, y, 'v');
        } else {
            dfs(board, seen, x, y - 1, '<');
        }
    } else {
        cout << "beam: " << beam << endl;
        assert(false);
    }
}

int count(const vector<string> & board) {
    int M = board.size();
    int N = board[0].size();

    int sum = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] != '.') ++sum;
        }
    }
    return sum;
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

    int sum = 0;
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

    int max_heat = 0;
    // first row
    for (int j = 0; j < N; ++j) {
        vector<string> tmp = board;
        vector<string> seen(M, string(N, '.'));
        dfs(tmp, seen, 0, j, 'v');
        int heat = count(seen);
        if (heat > max_heat) max_heat = heat;
    }
    // first col
    for (int i = 0; i < M; ++i) {
        vector<string> tmp = board;
        vector<string> seen(M, string(N, '.'));
        dfs(tmp, seen, i, 0, '>');
        int heat = count(seen);
        if (heat > max_heat) max_heat = heat;
    }
    // last row
    for (int j = 0; j < N; ++j) {
        vector<string> tmp = board;
        vector<string> seen(M, string(N, '.'));
        dfs(tmp, seen, M - 1, j, '^');
        int heat = count(seen);
        if (heat > max_heat) max_heat = heat;
    }
    // last col
    for (int i = 0; i < M; ++i) {
        vector<string> tmp = board;
        vector<string> seen(M, string(N, '.'));
        dfs(tmp, seen, i, N - 1, '<');
        int heat = count(seen);
        if (heat > max_heat) max_heat = heat;
    }

    cout << "ans:" << max_heat << endl;

    return 0;
}
