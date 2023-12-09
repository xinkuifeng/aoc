#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

bool should_stop(const vector<int> & v) {
    for (auto n : v) {
        if (n != 0) return false;
    }
    return true;
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
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto curr_v = parse_int(line, true);
            vector<vector<int>> vv;
            vv.push_back(curr_v);
            while (!should_stop(curr_v)) {
                vector<int> tmp;
                for (int i = 1; i < curr_v.size(); ++i) {
                    tmp.push_back(curr_v[i] - curr_v[i-1]);
                }
                vv.push_back(tmp);
                swap(tmp, curr_v);
            }

            int val = 0;
            for (int i = vv.size() - 2; i >= 0; --i) {
                auto & v = vv[i];
                val = v.front() - val;
            }
            sum += val;
        }
    }

    cout << "ans:" << sum << endl;

    return 0;
}
