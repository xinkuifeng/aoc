#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Point.h"

using namespace std;
using namespace fxk;

const vector<Point> dirs = vector<Point> {
    Point(-1, -1),
    Point(-1, 0),
    Point(-1, 1),
    Point(0, -1),
    Point(0, 1),
    Point(1, -1),
    Point(1, 0),
    Point(1, 1),
};

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

    vector<int> numbers;
    unordered_map<Point, int> point_to_number_idx;
    vector<Point> symbols;
    int row = 0;
    int sum = 0;
    int cnt = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            string str;
            for (int col = 0; col < line.size(); ++col) {
                char c = line[col];
                auto p = Point(row, col);
                if (isdigit(c)) {
                    str.push_back(c);
                    point_to_number_idx[p] = cnt;
                } else {
                    if (c != '.') {
                        symbols.push_back(p);
                    }
                    if (!str.empty()) {
                        int n = stoi(str);
                        numbers.push_back(n);
                        str.clear();
                        ++cnt;
                    }
                }
            }
            if (!str.empty()) {
                int n = stoi(str);
                numbers.push_back(n);
                ++cnt;
            }
            ++row;
        }
    }

    unordered_set<int> number_idx;
    for (const auto & s : symbols) {
        for (const auto & delta : dirs) {
            auto p = s + delta;
            if (point_to_number_idx.find(p) != point_to_number_idx.end()) {
                number_idx.insert(point_to_number_idx[p]);
            }
        }
    }

    for (const auto & idx : number_idx) {
        sum += numbers[idx];
    }

    cout << "ans:" << sum << endl;

    return 0;
}
