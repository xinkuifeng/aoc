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

    long ans = 1;
    string line;
    getline(file, line);
    auto times = parse_int(line);
    stringstream ss;
    for (auto n : times) {
        ss << n;
    }
    unsigned long long big_time = stoll(ss.str());
    getline(file, line);
    ss.str("");
    auto dist = parse_int(line);
    for (auto n : dist) {
        ss << n;
    }
    unsigned long long big_dist = stoll(ss.str());

    unsigned long long v = 0;
    unsigned long long win = 0;
    while (big_time) {
        unsigned long long d = v * big_time;
        if (d > big_dist) {
            ++win;
        }
        ++v;
        --big_time;
    }

    cout << "ans:" << win << endl;

    return 0;
}
