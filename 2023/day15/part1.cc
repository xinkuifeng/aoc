#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

int compute_hash(const string & str) {
    int current = 0;
    for (const auto & c : str) {
        current += (int)c;
        current *= 17;
        current %= 256;
    }
    return current;
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
    vector<string> steps;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            steps = split(line, ',');
        }
    }

    for (const auto & str : steps) {
        sum += compute_hash(str);
    }
    cout << "ans:" << sum << endl;

    return 0;
}
