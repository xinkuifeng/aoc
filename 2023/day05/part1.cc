#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
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

    string line;
    getline(file, line);
    auto numbers = parse_long(line);
    getline(file, line);

    int sum = 0;
    while (!file.eof()) {
        string line;
        auto tmp = vector<long>(numbers.size(), -1);
        while (getline(file, line)) {
            if (line.empty()) break;

            auto vec = parse_long(line);
            if (!vec.empty()) {
                auto dst = vec[0];
                auto src = vec[1];
                auto size = vec[2];
                for (int i = 0; i < numbers.size(); ++i) {
                    if (numbers[i] >= src && numbers[i] < src + size) {
                        auto diff = numbers[i] - src;
                        tmp[i] = dst + diff;
                    }
                }
            }
        }
        for (int i = 0; i < tmp.size(); ++i) {
            if (tmp[i] < 0) {
                tmp[i] = numbers[i];
            }
        }
        swap(tmp, numbers);
    }

    auto res = min_element(numbers.begin(), numbers.end());
    cout << "ans:" << *res << endl;

    return 0;
}
