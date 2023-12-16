#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

void print_vi(const vector<int> & vi) {
    for (int i = 0; i < vi.size(); ++i) {
        cout << vi[i];
        if (i != vi.size() - 1) cout << ",";
    }
    cout << endl;
}

int dfs(string spring, const vector<int> & nums) {
    if (spring.empty()) {
        if (nums.empty()) return 1;
        return 0;
    }

    if (nums.empty()) {
        auto pos = spring.find('#');
        if (pos != string::npos) return 0;
        // convert all '?' to '.'
        return 1;
    }

    int res = 0;
    if (spring[0] == '.' || spring[0] == '?') {
        // treat '?' as '.'
        res += dfs(spring.substr(1), nums);
    }
    if (spring[0] == '#' || spring[0] == '?') {
        // treat '?' as '#'
        if (nums[0] <= spring.size()) {
            auto str = spring.substr(0, nums[0]);
            auto pos = str.find('.');
            if (pos == string::npos) {
                if (nums[0] == spring.size() || spring[nums[0]] != '#') {
                    // separate by a '.'
                    int next = nums[0] + 1;
                    if (next > spring.size()) next = spring.size();
                    res += dfs(spring.substr(next), vector<int>(nums.begin() + 1, nums.end()));
                }
            }
        }
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

    int sum = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto vi = parse_int(line);
            auto vs = split(line, ' ');
            auto spring = vs[0];
            cout << spring << endl;
            print_vi(vi);
            sum += dfs(spring, vi);
        }
    }

    cout << "ans:" << sum << endl;

    return 0;
}
