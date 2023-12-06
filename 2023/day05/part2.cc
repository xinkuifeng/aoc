#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <queue>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

struct Segment {
    long start;
    long end; // exclusive

    Segment(long s, long e) : start(s), end(e) {}

    void display(std::ostream & os) const {
        os << "[" << start << "," << end << ")";
    }
};

std::ostream & operator<<(std::ostream & os, const Segment & s) {
    s.display(os);
    return os;
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

    string line;
    getline(file, line);
    auto raw = parse_long(line);
    queue<Segment> current;
    for (int i = 0; i < raw.size(); i += 2) {
        current.push(Segment(raw[i], raw[i] + raw[i+1]));
    }
    getline(file, line);

    while (!file.eof()) {
        string line;
        queue<Segment> next;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto vec = parse_long(line);
            if (!vec.empty()) {
                auto src = Segment(vec[1], vec[1] + vec[2]);
                auto dst = Segment(vec[0], vec[0] + vec[2]);
                auto offset = vec[0] - vec[1];

                auto size = current.size();
                while (size--) {
                    auto seg = current.front();
                    current.pop();
                    auto os = max(seg.start, src.start);
                    auto oe = min(seg.end, src.end);
                    if (os < oe) {
                        // can be moved
                        next.push(Segment(os + offset, oe + offset));
                        if (seg.start < os) {
                            current.push(Segment(seg.start, os));
                        }
                        if (oe < seg.end) {
                            current.push(Segment(oe, seg.end));
                        }
                    } else {
                        // cannot be moved. put it back.
                        current.push(seg);
                    }
                }
            }
        }
        while (!next.empty()) {
            auto s = next.front();
            next.pop();
            current.push(s);
        }
    }

    long min = LONG_MAX;
    while (!current.empty()) {
        auto s = current.front();
        current.pop();
        if (s.start < min) {
            min = s.start;
        }
    }

    cout << "ans:" << min << endl;

    return 0;
}
