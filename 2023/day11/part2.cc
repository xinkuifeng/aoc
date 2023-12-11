#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Point.h"

using namespace std;
using namespace fxk;

unordered_map<Point, Point> g_map;

void debug_print_map(const unordered_map<Point, Point> & mg) {
    for (const auto & p : mg) {
        cout << p.first << " -> " << p.second << endl;
    }
}

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

    static int expand = 1000000 - 1;
    vector<string> init_board;
    int row = 0;
    vector<vector<Point>> galaxies_per_row;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            init_board.push_back(line);
            vector<Point> vg;
            for (int col = 0; col < line.size(); ++col) {
                if (line[col] == '#') {
                    auto p = Point(row, col);
                    vg.push_back(p);
                    g_map[p] = p;
                }
            }
            galaxies_per_row.push_back(vg);
            ++row;
        }
    }
    // expand rows
    for (int i = 0; i < galaxies_per_row.size(); ++i) {
        auto & vg = galaxies_per_row[i];
        if (vg.empty()) {
            for (auto & p : g_map) {
                if (p.first.x > i) {
                    p.second.x += expand;
                }
            }
        }
    }

    auto transposed_board = transpose(init_board);
    int col = 0;
    vector<vector<Point>> galaxies_per_col;
    for (const auto & line : transposed_board) {
        vector<Point> vg;
        for (int row = 0; row < line.size(); ++row) {
            if (line[row] == '#') {
                vg.push_back(Point(row, col));
            }
        }
        galaxies_per_col.push_back(vg);
        ++col;
    }
    // expand cols
    for (int j = 0; j < galaxies_per_col.size(); ++j) {
        auto & vg = galaxies_per_col[j];
        if (vg.empty()) {
            for (auto & p : g_map) {
                if (p.first.y > j) {
                    p.second.y += expand;
                }
            }
        }
    }

    vector<Point> galaxies;
    for (const auto & p : g_map) {
        galaxies.push_back(p.second);
    }
    sort(galaxies.begin(), galaxies.end(), [](const auto & p1, const auto & p2){
        if (p1.x != p2.x) {
            return p1.x < p2.x;
        } else {
            return p1.y < p2.y;
        }
    });
    debug_print_galaxies(galaxies);

    long sum = 0;
    for (int i = 0; i < galaxies.size(); ++i) {
        for (int j = i + 1; j < galaxies.size(); ++j) {
            auto g1 = galaxies[i];
            auto g2 = galaxies[j];
            long diff_x = (long)g2.x - (long)g1.x;
            long diff_y = (long)g2.y - (long)g1.y;
            long dist = abs(diff_x) + abs(diff_y);
            sum += dist;
        }
    }
    cout << "ans:" << sum << endl;

    return 0;
}
