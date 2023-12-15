#include <fstream>
#include <iostream>
#include <list>
#include <ranges>
#include <string>
#include <vector>

#include "AocUtils.h"

using namespace std;
using namespace fxk;

struct Lense {
    string label;
    int power;

    Lense(string s, int n) : label(s), power(n) {}

    void display(std::ostream & os) const {
        os << "[" << label << " " << power << "]";
    }
};

std::ostream & operator<<(std::ostream & os, const Lense & l) {
    l.display(os);
    return os;
}

int compute_hash(const string & str) {
    int current = 0;
    for (const auto & c : str) {
        current += (int)c;
        current *= 17;
        current %= 256;
    }
    return current;
}

void print_boxes(const vector<list<Lense>> & boxes) {
    for (int i = 0; i < boxes.size(); ++i) {
        const auto & box = boxes[i];
        if (box.empty()) continue;

        cout << "Box " << i << ": ";
        for (const auto & l : box) {
            cout << l << " ";
        }
        cout << endl;
    }
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
    vector<list<Lense>> boxes(256);
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto steps = split(line, ',');
            for (const auto & step : steps) {
                auto pos = step.find("=");
                string label;
                int power = 0;
                if (pos != string::npos) {
                    auto vs = split(step, '=');
                    label = vs[0];
                    power = stoi(vs[1]);
                } else {
                    label = step.substr(0, step.size() - 1);
                }
                int idx = compute_hash(label);
                auto & box = boxes[idx];
                if (power == 0) {
                    box.remove_if([&label](const auto & l) { return l.label == label; });
                } else {
                    bool replaced = false;
                    ranges::transform(box, box.begin(), [&](const auto & l){
                        if (l.label == label) {
                            replaced = true;
                            return Lense(label, power);
                        } else {
                            return l;
                        }
                    });
                    if (!replaced) box.push_back(Lense(label, power));
                }
            }
        }
    }

    for (int i = 0; i < boxes.size(); ++i) {
        const auto & box = boxes[i];
        if (box.empty()) continue;

        int j = 0;
        for (const auto & l : box) {
            sum = sum + (i + 1) * (j + 1) * l.power;
            ++j;
        }
    }
    cout << "ans:" << sum << endl;

    return 0;
}
