#include <fstream>
#include <iostream>
#include <string>

#include "AocUtils.h"
#include "Segment.h"

using namespace fxk;
using namespace std;

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

    int cnt = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto vec = parse_int(line);
            Segment s1(vec[0], vec[1]);
            Segment s2(vec[2], vec[3]);
            if (s1.overlap(s2)) ++cnt;
        }
    }

    cout << "ans: " << cnt << endl;

    return 0;
}
