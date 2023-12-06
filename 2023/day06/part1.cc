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
    getline(file, line);
    auto dist = parse_int(line);
    for (int i = 0; i < times.size(); ++i) {
        auto t = times[i];
        auto r = dist[i];
        int v = 0;
        int win = 0;
        while (t) {
            int d = v * t;
            if (d > r) {
                ++win;
            }
            ++v;
            --t;
        }
        ans *= win;
    }

    cout << "ans:" << ans << endl;

    return 0;
}
