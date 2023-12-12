#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

void debug_vvi(const vector<vector<int>> & vvi) {
    for (const auto & vi : vvi) {
        for (auto n : vi) {
            cout << n << " ";
        }
        cout << endl;
    }
}

void debug_vs(const vector<string> & vs) {
    for (const auto & str : vs) {
        cout << str << endl;
    }
}

void debug_bt(const vector<string> & vs) {
    for (int i = 0; i < vs.size(); ++i) {
        cout << i << ": " << vs[i] << endl;
    }
}


bool compare(const vector<int> & lhs, const vector<int> & rhs) {
    if (lhs.size() != rhs.size()) return false;

    for (int j = 0; j < lhs.size(); ++j) {
        if (lhs[j] != rhs[j]) return false;
    }
    return true;
}

vector<int> count(const string & str) {
    vector<int> res;

    int cnt = 0;
    for (const auto & c : str) {
        if (c == '.') {
            if (cnt != 0) {
                res.push_back(cnt);
                cnt = 0;
            }
        } else if (c == '#') {
            ++cnt;
        } else {
            cout << c << " is not allowed." << endl;
            assert(false);
        }
    }
    if (cnt > 0) res.push_back(cnt);
    return res;
}

class Backtracking {
public:
    vector<string> solve(string str) {
        m_set.clear();
        bt(str, 0);
        return vector<string>(m_set.begin(), m_set.end());
    }

private:
    void bt(string str, int pos) {
        if (pos >= str.size()) {
            m_set.insert(str);
            return;
        }

        for (int i = pos; i < str.size(); ++i) {
            if (str[i] == '?') {
                str[i] = '#';
                bt(str, i + 1);
                str[i] = '.';
                bt(str, i + 1);
            } else {
                bt(str, i + 1);
            }
        }
    }

    unordered_set<string> m_set;
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

    vector<vector<int>> numbers;
    vector<string> springs;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto vi = parse_int(line);
            numbers.push_back(vi);
            auto vs = split(line, ' ');
            springs.push_back(vs[0]);
        }
    }

    int sum = 0;
    for (int i = 0; i < springs.size(); ++i) {
        const auto & input = springs[i];
        cout << "row " << i << ": " << input << endl;
        Backtracking bt;
        auto vs = bt.solve(input);
        int cnt = 0;
        for (const auto & output : vs) {
            auto vi = count(output);
            if (compare(numbers[i], vi)) ++cnt;
        }
        cout << cnt << " valid choices" << endl;
        sum += cnt;
    }

    cout << "ans:" << sum << endl;

    return 0;
}
