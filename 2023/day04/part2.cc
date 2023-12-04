#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

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
    int row = 0;
    map<int, int> cards;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;
            ++row;
            ++cards[row];


            auto start_pos = line.find(":");
            auto mid_pos = line.find("|");
            auto s1 = line.substr(start_pos, mid_pos - start_pos);
            auto s2 = line.substr(mid_pos);

            auto w_numbers = parse_int(s1);
            auto numbers = parse_int(s2);
            auto w_numbers_set = unordered_set<int>(w_numbers.begin(), w_numbers.end());
            int cnt = 0;
            for (auto n : numbers) {
                if (w_numbers_set.find(n) != w_numbers_set.end()) {
                    ++cnt;
                }
            }
            int copies = cards[row];
            for (int i = 1; i <= cnt; ++i) {
                cards[row + i] += copies;
            }
        }
    }

    for (const auto & p : cards) {
        sum += p.second;
    }

    cout << "ans:" << sum << endl;

    return 0;
}
