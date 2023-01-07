#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "AocUtils.h"

using namespace fxk;
using namespace std;

bool should_compute(int cycle) {
    if (cycle < 20) return false;

    return (cycle - 20) % 40 == 0;
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
    int total = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto strs = split(line, ' ');

            bool add = strs.size() == 2;
            int cnt = add ? 2 : 1;

            while (cnt--) {
                cout << "Start of cycle " << cycle << ": " << curr << endl;
                if (should_compute(cycle)) {
                    total += cycle * curr;
                }
                ++cycle;
            }

            if (add) {
                curr += stoi(strs[1]);
            }
        }
    }

    cout << "ans: " << total << endl;

    return 0;
}
