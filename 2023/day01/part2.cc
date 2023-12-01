#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> words = {
    "one", "two", "three",
    "four", "five", "six",
    "seven", "eight", "nine"
};

const vector<string> digits = {
    "1", "2", "3",
    "4", "5", "6",
    "7", "8", "9"
};

string reverse(string s) {
    std::reverse(s.begin(), s.end());
    return s;
}

int find_pos(const string & str, const string & substr) {
    auto pos = str.find(substr);
    if (pos == string::npos) {
        return INT_MAX;
    }
    return pos;
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

    vector<string> rws;
    for (auto w : words) {
        auto rw = reverse(w);
        rws.push_back(rw);
    }

    int sum = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;
            auto rl = reverse(line);

            vector<int> first_pos(9, INT_MAX);
            vector<int> last_pos(9, INT_MAX);
            for (int idx = 0; idx < 9; ++idx) {
                auto pos = find_pos(line, words[idx]);
                if (pos < first_pos[idx]) {
                    first_pos[idx] = pos;
                }
                pos = find_pos(line, digits[idx]);
                if (pos < first_pos[idx]) {
                    first_pos[idx] = pos;
                }

                pos = find_pos(rl, rws[idx]);
                if (pos < last_pos[idx]) {
                    last_pos[idx] = pos;
                }
                pos = find_pos(rl, digits[idx]);
                if (pos < last_pos[idx]) {
                    last_pos[idx] = pos;
                }
            }

            int min = INT_MAX;
            int first = 0;
            for (int idx = 0; idx < 9; ++idx) {
                if (first_pos[idx] < min) {
                    min = first_pos[idx];
                    first = idx + 1;
                }
            }
            min = INT_MAX;
            int last = 0;
            for (int idx = 0; idx < 9; ++idx) {
                if (last_pos[idx] < min) {
                    min = last_pos[idx];
                    last = idx + 1;
                }
            }
            int num = first * 10 + last;
            sum += num;
        }
    }

    cout << "ans:" << sum << endl;

    return 0;
}
