#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "AocUtils.h"

using namespace fxk;
using namespace std;

void draw(vector<vector<char>> & board, int X, int cycle) {
    int row = (cycle - 1) / 40;
    int col = (cycle - 1) % 40;

    int low = X - 1;
    int high = X + 1;
    if (col >= low && col <= high) {
        board[row][col] = '#';
    }
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

    int cycle = 1;
    int curr = 1;
    vector<vector<char>> board = vector<vector<char>>(6, vector<char>(40, '.'));
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto strs = split(line, ' ');

            bool add = strs.size() == 2;
            int cnt = add ? 2 : 1;

            while (cnt--) {
                cout << "Start of cycle " << cycle << ": " << curr << endl;
                draw(board, curr, cycle);
                ++cycle;
            }

            if (add) {
                curr += stoi(strs[1]);
            }
        }
    }

    for (const auto & vec : board) {
        for (const auto & c : vec) {
            cout << c;
        }
        cout << endl;
    }

    return 0;
}
