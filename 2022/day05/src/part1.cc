#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "AocUtils.h"

using namespace fxk;
using namespace std;

vector<stack<char>> init(const vector<string> & lines) {
    int size = lines[0].size();
    int n = (size + 1) / 4;
    vector<stack<char>> tmp(n);

    for (int i = 0; i < lines.size() - 1; ++i) {
        const auto & line = lines[i];
        int j = 0, idx = 0;
        while (idx < line.size()) {
            idx = j * 4 + 1;

            if (isalpha(line[idx])) {
                tmp[j].push(line[idx]);
            }
            ++j;
        }
    }

    vector<stack<char>> res(n);
    for (int i = 0; i < tmp.size(); ++i) {
        while (!tmp[i].empty()) {
            auto c = tmp[i].top();
            tmp[i].pop();

            res[i].push(c);
        }
    }
    return res;
}

void solve(vector<stack<char>> & stacks, string line) {
    vector<int> cmd = parse_int(line);

    int cnt = cmd[0];
    auto & src = stacks[cmd[1] - 1];
    auto & dst = stacks[cmd[2] - 1];

    while (cnt--) {
        auto c = src.top();
        src.pop();

        dst.push(c);
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

    vector<string> setup;
    vector<stack<char>> stacks;
    bool first = true;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            if (first) {
                setup.push_back(line);
            } else {
                solve(stacks, line);
            }
        }
        if (first) {
            first = false;
            stacks = init(setup);
        }
    }

    string ans;
    for (const auto & s : stacks) {
        ans += s.top();
    }

    cout << "ans: " << ans << endl;

    return 0;
}
