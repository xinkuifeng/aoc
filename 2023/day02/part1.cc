#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

const unordered_map<char, int> cubes = unordered_map<char, int> {
    {'r', 12},
    {'g', 13},
    {'b', 14},
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

    int sum = 0;
    int game = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;
            ++game;
            bool possible = true;

            regex r(R"(\d+\s[rbg])");
            smatch sm;
            while (regex_search(line, sm, r))
            {
                string res = sm.str();
                auto ints = parse_int(res);
                int d = ints[0];
                char c = res[res.size() - 1];
                if (d > cubes.at(c)) {
                    possible = false;
                    break;
                }
                line = sm.suffix();
            }

            if (possible) sum += game;
        }
    }

    cout << "ans:" << sum << endl;

    return 0;
}
