#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Point.h"

using namespace std;
using namespace fxk;

void debug_print_galaxies(const vector<Point> & vg) {
    for (int i = 0; i < vg.size(); ++i) {
        cout << i << ": " << vg[i] << endl;
    }
}

vector<string> transpose(const vector<string> & board) {
    int M = board.size();
    int N = board[0].size();

    vector<string> res;
    stringstream ss;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < M; ++i) {
            ss << board[i][j];
        }
        res.push_back(ss.str());
        ss.str("");
    }
    return res;
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

    vector<string> expand_row_board;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto pos = line.find("#");
            if (pos != string::npos) {
                expand_row_board.push_back(line);
            } else {
                expand_row_board.push_back(line);
                expand_row_board.push_back(line);
            }
        }
    }

    auto tmp_board = transpose(expand_row_board);
    vector<string> expand_col_board;
    for (const auto & line : tmp_board) {
        auto pos = line.find("#");
        if (pos != string::npos) {
            expand_col_board.push_back(line);
        } else {
            expand_col_board.push_back(line);
            expand_col_board.push_back(line);
        }
    }
    auto final_board = transpose(expand_col_board);

    int M = final_board.size();
    int N = final_board[0].size();
    vector<Point> galaxies;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (final_board[i][j] == '#') {
                galaxies.push_back(Point(i, j));
            }
        }
    }
    debug_print_galaxies(galaxies);

    int sum = 0;
    for (int i = 0; i < galaxies.size(); ++i) {
        for (int j = i + 1; j < galaxies.size(); ++j) {
            auto g1 = galaxies[i];
            auto g2 = galaxies[j];
            auto dist = abs(g2.x - g1.x) + abs(g2.y - g1.y);
            sum += dist;
        }
    }
    cout << "ans:" << sum << endl;

    return 0;
}
