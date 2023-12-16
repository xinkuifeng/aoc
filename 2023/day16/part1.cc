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

void print_heat_map(const vector<vector<int>> & cnt) {
    int M = cnt.size();
    int N = cnt[0].size();

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int n = cnt[i][j];
            if (n == 0) {
                cout << '.';
            } else {
                cout << '#';
            }
        }
        cout << endl;
    }
}

void dfs(vector<string> & board, vector<vector<int>> & cnt, int x, int y, char beam) {
    const static int M = board.size();
    const static int N = board[0].size();
    static vector<string> seen(M, string(N, '.'));
    if (x < 0 || x >= M || y < 0 || y >= N || seen[x][y] == beam) return;

    char ch = board[x][y];
    cnt[x][y] += 1;
    seen[x][y] = beam;
    if (beam == '>') {
        if (ch == '|') {
            dfs(board, cnt, x - 1, y, '^');
            dfs(board, cnt, x + 1, y, 'v');
        } else if (ch == '-') {
            dfs(board, cnt, x, y + 1, '>');
        } else if (ch == '\\') {
            dfs(board, cnt, x + 1, y, 'v');
        } else if (ch == '/') {
            dfs(board, cnt, x - 1, y, '^');
        } else {
            dfs(board, cnt, x, y + 1, '>');
        }
    } else if (beam == '^') {
        if (ch == '|') {
            dfs(board, cnt, x - 1, y, '^');
        } else if (ch == '-') {
            dfs(board, cnt, x, y + 1, '>');
            dfs(board, cnt, x, y - 1, '<');
        } else if (ch == '\\') {
            dfs(board, cnt, x, y - 1, '<');
        } else if (ch == '/') {
            dfs(board, cnt, x, y + 1, '>');
        } else {
            dfs(board, cnt, x - 1, y, '^');
        }
    } else if (beam == 'v') {
        if (ch == '|') {
            dfs(board, cnt, x + 1, y, 'v');
        } else if (ch == '-') {
            dfs(board, cnt, x, y + 1, '>');
            dfs(board, cnt, x, y - 1, '<');
        } else if (ch == '\\') {
            dfs(board, cnt, x, y + 1, '>');
        } else if (ch == '/') {
            dfs(board, cnt, x, y - 1, '<');
        } else {
            dfs(board, cnt, x + 1, y, 'v');
        }
    } else if (beam == '<') {
        if (ch == '|') {
            dfs(board, cnt, x - 1, y, '^');
            dfs(board, cnt, x + 1, y, 'v');
        } else if (ch == '-') {
            dfs(board, cnt, x, y - 1, '<');
        } else if (ch == '\\') {
            dfs(board, cnt, x - 1, y, '^');
        } else if (ch == '/') {
            dfs(board, cnt, x + 1, y, 'v');
        } else {
            dfs(board, cnt, x, y - 1, '<');
        }
    } else {
        cout << "beam: " << beam << endl;
        assert(false);
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
    vector<vector<int>> cnt(M, vector<int>(N, 0));
    dfs(board, cnt, 0, 0, '>');

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (cnt[i][j]) sum += 1;
        }
    }
    cout << "ans:" << sum << endl;

    return 0;
}
