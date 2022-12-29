#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AocUtils.h"
#include "Point.h"

using namespace fxk;
using namespace std;

unordered_map<string, Point> g_dirs = {
    {"R", Point(1, 0)},
    {"L", Point(-1, 0)},
    {"U", Point(0, 1)},
    {"D", Point(0, -1)},
    {"RU", Point(1, 1)},
    {"RD", Point(1, -1)},
    {"LU", Point(-1, 1)},
    {"LD", Point(-1, -1)},
};

string calc_dir(const Point & src, const Point & dst) {
    string ans;

    // X
    if (src.x < dst.x) {
        ans += 'R';
    } else if (src.x > dst.x) {
        ans += 'L';
    }

    // Y
    if (src.y < dst.y) {
        ans += 'U';
    } else if (src.y > dst.y) {
        ans += 'D';
    }
    return ans;
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

    vector<Point> rope(10, Point(0, 0));
    unordered_set<Point> visited;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            vector<string> strs = split(line, ' ');
            int move = stoi(strs[1]);
            Point unit = g_dirs.at(strs[0]);
            while (move--) {
                rope[0] += unit;
                for (int i = 1; i < rope.size(); ++i) {
                    if (is_adjacent_8(rope[i], rope[i - 1])) continue;

                    string dir = calc_dir(rope[i], rope[i - 1]);
                    rope[i] += g_dirs.at(dir);
                }
                visited.insert(rope[9]);
            }
        }
    }

    cout << "ans: " << visited.size() << endl;

    return 0;
}
